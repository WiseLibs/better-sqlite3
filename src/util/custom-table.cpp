class CustomTable {
public:

	explicit CustomTable(
		Napi::Env env,
		Database* db,
		const char* name,
		Napi::Function factory
	) :
		addon(db->GetAddon()),
		env(env),
		db(db),
		name(name),
		factory(Napi::Persistent(factory)) {}

	static void Destructor(void* self) {
		delete static_cast<CustomTable*>(self);
	}

	static sqlite3_module MODULE;
	static sqlite3_module EPONYMOUS_MODULE;

private:

	// This nested class is instantiated on each CREATE VIRTUAL TABLE statement.
	class VTab { friend class CustomTable;
		explicit VTab(
			CustomTable* parent,
			Napi::Function generator,
			std::vector<std::string> parameter_names,
			bool safe_ints
		) :
			parent(parent),
			parameter_count(parameter_names.size()),
			safe_ints(safe_ints),
			generator(Napi::Persistent(generator)),
			parameter_names(parameter_names) {
			((void)base);
		}

		static inline CustomTable::VTab* Upcast(sqlite3_vtab* vtab) {
			return reinterpret_cast<VTab*>(vtab);
		}

		inline sqlite3_vtab* Downcast() {
			return reinterpret_cast<sqlite3_vtab*>(this);
		}

		sqlite3_vtab base;
		CustomTable * const parent;
		const int parameter_count;
		const bool safe_ints;
		const Napi::FunctionReference generator;
		const std::vector<std::string> parameter_names;
	};

	// This nested class is instantiated each time a virtual table is scanned.
	class Cursor { friend class CustomTable;
		static inline CustomTable::Cursor* Upcast(sqlite3_vtab_cursor* cursor) {
			return reinterpret_cast<Cursor*>(cursor);
		}

		inline sqlite3_vtab_cursor* Downcast() {
			return reinterpret_cast<sqlite3_vtab_cursor*>(this);
		}

		inline CustomTable::VTab* GetVTab() {
			return VTab::Upcast(base.pVtab);
		}

		sqlite3_vtab_cursor base;
		Napi::ObjectReference iterator;
		Napi::FunctionReference next;
		Napi::Reference<Napi::Array> row;
		bool done;
		sqlite_int64 rowid;
	};

	// This nested class is used by Data::ResultValueFromJS to report errors.
	class TempDataConverter : DataConverter { friend class CustomTable;
		explicit TempDataConverter(CustomTable* parent) :
			parent(parent),
			status(SQLITE_OK) {}

		void PropagateJSError(sqlite3_context* invocation) {
			status = SQLITE_ERROR;
			parent->PropagateJSError();
		}

		std::string GetDataErrorPrefix() {
			return std::string("Virtual table module \"") + parent->name + "\" yielded";
		}

		CustomTable * const parent;
		int status;
	};

	// Although this function does nothing, we cannot use xConnect directly,
	// because that would cause SQLite to register an eponymous virtual table.
	static int xCreate(sqlite3* db_handle, void* _self, int argc, const char* const * argv, sqlite3_vtab** output, char** errOutput) {
		return xConnect(db_handle, _self, argc, argv, output, errOutput);
	}

	// This method uses the factory function to instantiate a new virtual table.
	static int xConnect(sqlite3* db_handle, void* _self, int argc, const char* const * argv, sqlite3_vtab** output, char** errOutput) {
		CustomTable* self = static_cast<CustomTable*>(_self);
		Napi::Env env = self->env;
		Napi::HandleScope scope(env);

		napi_value* args = ALLOC_ARRAY<napi_value>(argc);
		for (int i = 0; i < argc; ++i) {
			args[i] = StringFromUtf8(env, argv[i], -1);
		}

		// Run the factory function to receive a new virtual table definition.
		Napi::Value returnValue = SafeCall(env, self->factory.Value(), env.Undefined(), argc, args);
		delete[] args;

		if (env.IsExceptionPending()) {
			self->PropagateJSError();
			return SQLITE_ERROR;
		}

		// Extract each part of the virtual table definition.
		Napi::Array array = returnValue.As<Napi::Array>();
		Napi::String sqlString = array.Get((uint32_t)0).As<Napi::String>();
		Napi::Function generator = array.Get((uint32_t)1).As<Napi::Function>();
		Napi::Array parameterNames = array.Get((uint32_t)2).As<Napi::Array>();
		int safe_ints = array.Get((uint32_t)3).As<Napi::Number>().Int32Value();
		bool direct_only = array.Get((uint32_t)4).As<Napi::Boolean>().Value();

		std::string sql = sqlString.Utf8Value();
		safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(self->db->GetState()->safe_ints);

		// Copy the parameter names into a std::vector.
		std::vector<std::string> parameter_names;
		for (int i = 0, len = parameterNames.Length(); i < len; ++i) {
			Napi::String parameterName = parameterNames.Get((uint32_t)i).As<Napi::String>();
			parameter_names.emplace_back(parameterName.Utf8Value());
		}

		// Pass our SQL table definition to SQLite (this should never fail).
		if (sqlite3_declare_vtab(db_handle, sql.c_str()) != SQLITE_OK) {
			*errOutput = sqlite3_mprintf("failed to declare virtual table \"%s\"", argv[2]);
			return SQLITE_ERROR;
		}
		if (direct_only && sqlite3_vtab_config(db_handle, SQLITE_VTAB_DIRECTONLY) != SQLITE_OK) {
			*errOutput = sqlite3_mprintf("failed to configure virtual table \"%s\"", argv[2]);
			return SQLITE_ERROR;
		}

		// Return the successfully created virtual table.
		*output = (new VTab(self, generator, parameter_names, safe_ints))->Downcast();
		return SQLITE_OK;
	}

	static int xDisconnect(sqlite3_vtab* vtab) {
		delete VTab::Upcast(vtab);
		return SQLITE_OK;
	}

	static int xOpen(sqlite3_vtab* vtab, sqlite3_vtab_cursor** output) {
		*output = (new Cursor())->Downcast();
		return SQLITE_OK;
	}

	static int xClose(sqlite3_vtab_cursor* cursor) {
		delete Cursor::Upcast(cursor);
		return SQLITE_OK;
	}

	// This method uses a fresh cursor to start a new scan of a virtual table.
	// The args and idxNum are provided by xBestIndex (idxStr is unused).
	// idxNum is a bitmap that provides the proper indices of the received args.
	static int xFilter(sqlite3_vtab_cursor* _cursor, int idxNum, const char* idxStr, int argc, sqlite3_value** argv) {
		Cursor* cursor = Cursor::Upcast(_cursor);
		VTab* vtab = cursor->GetVTab();
		CustomTable* self = vtab->parent;
		Addon* addon = self->addon;
		Napi::Env env = self->env;
		Napi::HandleScope scope(env);

		// Convert the SQLite arguments into JavaScript arguments. Note that
		// the values in argv may be in the wrong order, so we fix that here.
		napi_value args_fast[4];
		napi_value* args = NULL;
		int parameter_count = vtab->parameter_count;
		if (parameter_count != 0) {
			args = parameter_count <= 4 ? args_fast : ALLOC_ARRAY<napi_value>(parameter_count);
			int argn = 0;
			bool safe_ints = vtab->safe_ints;
			for (int i = 0; i < parameter_count; ++i) {
				if (idxNum & 1 << i) {
					Napi::Value arg = Data::GetValueJS(env, argv[argn++], safe_ints);
					args[i] = arg;
					// If any arguments are NULL, the result set is necessarily
					// empty, so don't bother to run the generator function.
					if (arg.IsNull()) {
						if (args != args_fast) delete[] args;
						cursor->done = true;
						return SQLITE_OK;
					}
				} else {
					args[i] = env.Undefined();
				}
			}
		}

		// Invoke the generator function to create a new iterator.
		Napi::Value maybeIterator = SafeCall(env, vtab->generator.Value(), env.Undefined(), parameter_count, args);
		if (args != args_fast) delete[] args;

		if (env.IsExceptionPending()) {
			self->PropagateJSError();
			return SQLITE_ERROR;
		}

		// Store the iterator and its next() method; we'll be using it a lot.
		Napi::Object iterator = maybeIterator.As<Napi::Object>();
		Napi::Function next = iterator.Get(addon->cs.next.Value()).As<Napi::Function>();
		cursor->iterator.Reset(iterator, 1);
		cursor->next.Reset(next, 1);
		cursor->rowid = 0;

		// Advance the iterator/cursor to the first row.
		return xNext(cursor->Downcast());
	}

	// This method advances a virtual table's cursor to the next row.
	// SQLite will call this method repeatedly, driving the generator function.
	static int xNext(sqlite3_vtab_cursor* _cursor) {
		Cursor* cursor = Cursor::Upcast(_cursor);
		CustomTable* self = cursor->GetVTab()->parent;
		Addon* addon = self->addon;
		Napi::Env env = self->env;
		Napi::HandleScope scope(env);

		Napi::Object iterator = cursor->iterator.Value();
		Napi::Function next = cursor->next.Value();

		Napi::Value maybeRecord = SafeCall(env, next, iterator, 0, NULL);
		if (env.IsExceptionPending()) {
			self->PropagateJSError();
			return SQLITE_ERROR;
		}

		Napi::Object record = maybeRecord.As<Napi::Object>();
		bool done = record.Get(addon->cs.done.Value()).As<Napi::Boolean>().Value();
		if (!done) {
			cursor->row.Reset(record.Get(addon->cs.value.Value()).As<Napi::Array>(), 1);
		}
		cursor->done = done;
		cursor->rowid += 1;

		return SQLITE_OK;
	}

	// If this method returns 1, SQLite will stop scanning the virtual table.
	static int xEof(sqlite3_vtab_cursor* cursor) {
		return Cursor::Upcast(cursor)->done;
	}

	// This method extracts some column from the cursor's current row.
	static int xColumn(sqlite3_vtab_cursor* _cursor, sqlite3_context* invocation, int column) {
		Cursor* cursor = Cursor::Upcast(_cursor);
		CustomTable* self = cursor->GetVTab()->parent;
		TempDataConverter temp_data_converter(self);
		Napi::Env env = self->env;
		Napi::HandleScope scope(env);

		Napi::Array row = cursor->row.Value();
		Napi::Value maybeColumnValue = SafeGetElement(env, row, (uint32_t)column);
		if (maybeColumnValue.IsEmpty()) {
			temp_data_converter.PropagateJSError(NULL);
		} else {
			Data::ResultValueFromJS(env, invocation, maybeColumnValue, &temp_data_converter);
		}
		return temp_data_converter.status;
	}

	// This method outputs the rowid of the cursor's current row.
	static int xRowid(sqlite3_vtab_cursor* cursor, sqlite_int64* output) {
		*output = Cursor::Upcast(cursor)->rowid;
		return SQLITE_OK;
	}

	// This method tells SQLite how to *plan* queries on our virtual table.
	// It gets invoked (typically multiple times) during db.prepare().
	static int xBestIndex(sqlite3_vtab* vtab, sqlite3_index_info* output) {
		int parameter_count = VTab::Upcast(vtab)->parameter_count;
		int argument_count = 0;
		std::vector<std::pair<int, int>> forwarded;

		for (int i = 0, len = output->nConstraint; i < len; ++i) {
			auto item = output->aConstraint[i];

			// The SQLITE_INDEX_CONSTRAINT_LIMIT and SQLITE_INDEX_CONSTRAINT_OFFSET
			// operators have no left-hand operand, and so for those operators the
			// corresponding item.iColumn is meaningless.
			// We don't care those constraints.
			if (item.op == SQLITE_INDEX_CONSTRAINT_LIMIT || item.op == SQLITE_INDEX_CONSTRAINT_OFFSET) {
				continue;
			}
			// We only care about constraints on parameters, not regular columns.
			if (item.iColumn >= 0 && item.iColumn < parameter_count) {
				if (item.op != SQLITE_INDEX_CONSTRAINT_EQ) {
					sqlite3_free(vtab->zErrMsg);
					vtab->zErrMsg = sqlite3_mprintf(
						"virtual table parameter \"%s\" can only be constrained by the '=' operator",
						VTab::Upcast(vtab)->parameter_names.at(item.iColumn).c_str());
					return SQLITE_ERROR;
				}
				if (!item.usable) {
					// Don't allow SQLite to make plans that ignore arguments.
					// Otherwise, a user could pass arguments, but then they
					// could appear undefined in the generator function.
					return SQLITE_CONSTRAINT;
				}
				forwarded.emplace_back(item.iColumn, i);
			}
		}

		// Tell SQLite to forward arguments to xFilter.
		std::sort(forwarded.begin(), forwarded.end());
		for (std::pair<int, int> pair : forwarded) {
			int bit = 1 << pair.first;
			if (!(output->idxNum & bit)) {
				output->idxNum |= bit;
				output->aConstraintUsage[pair.second].argvIndex = ++argument_count;
				output->aConstraintUsage[pair.second].omit = 1;
			}
		}

		// Use a very high estimated cost so SQLite is not tempted to invoke the
		// generator function within a loop, if it can be avoided.
		output->estimatedCost = output->estimatedRows = 1000000000 / (argument_count + 1);
		return SQLITE_OK;
	}

	void PropagateJSError() {
		assert(db->GetState()->was_js_error == false);
		db->GetState()->was_js_error = true;
	}

	Addon* const addon;
	const Napi::Env env;
	Database* const db;
	const std::string name;
	const Napi::FunctionReference factory;
};

sqlite3_module CustomTable::MODULE = {
	0,                            /* iVersion */
	xCreate,                      /* xCreate */
	xConnect,                     /* xConnect */
	xBestIndex,                   /* xBestIndex */
	xDisconnect,                  /* xDisconnect */
	xDisconnect,                  /* xDestroy */
	xOpen,                        /* xOpen */
	xClose,                       /* xClose */
	xFilter,                      /* xFilter */
	xNext,                        /* xNext */
	xEof,                         /* xEof */
	xColumn,                      /* xColumn */
	xRowid,                       /* xRowid */
	NULL,                         /* xUpdate */
	NULL,                         /* xBegin */
	NULL,                         /* xSync */
	NULL,                         /* xCommit */
	NULL,                         /* xRollback */
	NULL,                         /* xFindMethod */
	NULL,                         /* xRename */
	NULL,                         /* xSavepoint */
	NULL,                         /* xRelease */
	NULL,                         /* xRollbackTo */
	NULL,                         /* xShadowName */
	NULL                          /* xIntegrity */
};

sqlite3_module CustomTable::EPONYMOUS_MODULE = {
	0,                            /* iVersion */
	NULL,                         /* xCreate */
	xConnect,                     /* xConnect */
	xBestIndex,                   /* xBestIndex */
	xDisconnect,                  /* xDisconnect */
	xDisconnect,                  /* xDestroy */
	xOpen,                        /* xOpen */
	xClose,                       /* xClose */
	xFilter,                      /* xFilter */
	xNext,                        /* xNext */
	xEof,                         /* xEof */
	xColumn,                      /* xColumn */
	xRowid,                       /* xRowid */
	NULL,                         /* xUpdate */
	NULL,                         /* xBegin */
	NULL,                         /* xSync */
	NULL,                         /* xCommit */
	NULL,                         /* xRollback */
	NULL,                         /* xFindMethod */
	NULL,                         /* xRename */
	NULL,                         /* xSavepoint */
	NULL,                         /* xRelease */
	NULL,                         /* xRollbackTo */
	NULL,                         /* xShadowName */
	NULL                          /* xIntegrity */
};
