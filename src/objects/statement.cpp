const napi_type_tag Statement::TYPE_TAG = RandomTypeTag();

Statement::Statement(const Napi::CallbackInfo& info) :
	Napi::ObjectWrap<Statement>(info),
	db(NULL),
	handle(NULL),
	extras(NULL),
	alive(false),
	locked(false),
	bound(false),
	has_bind_map(false),
	safe_ints(false),
	mode(Data::FLAT),
	returns_data(false) {
	napi_status status = napi_type_tag_object(info.Env(), info.This(), &TYPE_TAG);
	assert(status == napi_ok); ((void)status);
	JS_new(info);
}

Statement::~Statement() {
	if (alive) db->RemoveStatement(this);
	CloseHandles();
	delete extras;
}

// Whenever this is used, db->RemoveStatement must be invoked beforehand.
void Statement::CloseHandles() {
	if (alive) {
		alive = false;
		sqlite3_finalize(handle);
	}
}

// Returns the Statement's bind map (creates it upon first execution).
BindMap& Statement::GetBindMap(Napi::Env env) {
	if (has_bind_map) return extras->bind_map;
	BindMap& bind_map = extras->bind_map;
	int param_count = sqlite3_bind_parameter_count(handle);
	for (int i = 1; i <= param_count; ++i) {
		const char* name = sqlite3_bind_parameter_name(handle, i);
		if (name != NULL) bind_map.Add(env, name + 1, i);
	}
	has_bind_map = true;
	return bind_map;
}

// Returns the Statement's row builder.
RowBuilder& Statement::GetRowBuilder() {
	return extras->row_builder;
}

Statement::Extras::Extras(
	Napi::Env env,
	Napi::Function row_factory,
	Napi::Function array_factory,
	sqlite3_uint64 id
) :
	bind_map(0),
	row_builder(env, row_factory, array_factory),
	id(id) {}

INIT(Statement::Init) {
	return DefineClass(env, "Statement", {
		PrototypeMethod<Statement, &Statement::JS_run>("run", addon),
		PrototypeMethod<Statement, &Statement::JS_get>("get", addon),
		PrototypeMethod<Statement, &Statement::JS_all>("all", addon),
		PrototypeMethod<Statement, &Statement::JS_iterate>("iterate", addon),
		PrototypeMethod<Statement, &Statement::JS_bind>("bind", addon),
		PrototypeMethod<Statement, &Statement::JS_pluck>("pluck", addon),
		PrototypeMethod<Statement, &Statement::JS_expand>("expand", addon),
		PrototypeMethod<Statement, &Statement::JS_raw>("raw", addon),
		PrototypeMethod<Statement, &Statement::JS_safeIntegers>("safeIntegers", addon),
		PrototypeMethod<Statement, &Statement::JS_columns>("columns", addon),
		PrototypeMethod<Statement, &Statement::JS_toString>("toString", addon),
	}, addon);
}

NODE_METHOD(Statement::JS_new) {
	UseAddon;
	if (!addon->privileged_info) {
		return ThrowTypeError(info.Env(), "Statements can only be constructed by the db.prepare() method");
	}
	assert(info.IsConstructCall());
	const Napi::CallbackInfo& pinfo = *addon->privileged_info;
	Database* db = ::Unwrap<Database>(pinfo.This());
	REQUIRE_DATABASE_OPEN(db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(db->GetState());

	Napi::String source = pinfo[0].As<Napi::String>();
	Napi::Object database = pinfo[1].As<Napi::Object>();
	bool pragmaMode = pinfo[2].As<Napi::Boolean>().Value();
	bool explainMode = pinfo[3].As<Napi::Boolean>().Value();
	int flags = SQLITE_PREPARE_PERSISTENT;

	if (pragmaMode) {
		REQUIRE_DATABASE_NO_ITERATORS_UNLESS_UNSAFE(db->GetState());
		flags = 0;
	}
	if (explainMode) {
		flags = 0;
	}

	UseIsolate;
	std::string utf8 = source.Utf8Value();
	sqlite3_stmt* handle;
	const char* tail;

	if (sqlite3_prepare_v3(db->GetHandle(), utf8.c_str(), utf8.length() + 1, flags, &handle, &tail) != SQLITE_OK) {
		db->ThrowDatabaseError(env);
		return env.Undefined();
	}
	if (handle == NULL) {
		return ThrowRangeError(env, "The supplied SQL string contains no statements");
	}
	// https://github.com/WiseLibs/better-sqlite3/issues/975#issuecomment-1520934678
	for (char c; (c = *tail); ) {
		if (IS_SKIPPED(c)) {
			++tail;
			continue;
		}
		if (c == '/' && tail[1] == '*') {
			tail += 2;
			for (char c; (c = *tail); ++tail) {
				if (c == '*' && tail[1] == '/') {
					tail += 2;
					break;
				}
			}
		} else if (c == '-' && tail[1] == '-') {
			tail += 2;
			for (char c; (c = *tail); ++tail) {
				if (c == '\n') {
					++tail;
					break;
				}
			}
		} else {
			sqlite3_finalize(handle);
			return ThrowRangeError(env, "The supplied SQL string contains more than one statement");
		}
	}

	bool returns_data = sqlite3_column_count(handle) >= 1 || pragmaMode;
	this->db = db;
	this->handle = handle;
	this->extras = new Extras(env, addon->RowFactory.Value(), addon->ArrayFactory.Value(), addon->NextId());
	this->bound = explainMode;
	this->safe_ints = db->GetState()->safe_ints;
	this->returns_data = returns_data;
	this->alive = true;
	assert(db->GetState()->open);
	assert(!db->GetState()->busy);
	db->AddStatement(this);

	Napi::Object _this = info.This().As<Napi::Object>();
	SetFrozen(env, _this, addon->cs.reader, Napi::Boolean::New(env, returns_data));
	SetFrozen(env, _this, addon->cs.readonly, Napi::Boolean::New(env, sqlite3_stmt_readonly(handle) != 0));
	SetFrozen(env, _this, addon->cs.source, source);
	SetFrozen(env, _this, addon->cs.database, database);
	SetInstanceGetter<Statement, &Statement::JS_busy>(_this, "busy", addon);

	return info.This();
}

NODE_METHOD(Statement::JS_run) {
	STATEMENT_START(ALLOW_ANY_STATEMENT, DOES_MUTATE);
	sqlite3* db_handle = db->GetHandle();
	int total_changes_before = sqlite3_total_changes(db_handle);

	sqlite3_step(handle);
	if (sqlite3_reset(handle) == SQLITE_OK) {
		int changes = sqlite3_total_changes(db_handle) == total_changes_before ? 0 : sqlite3_changes(db_handle);
		sqlite3_int64 id = sqlite3_last_insert_rowid(db_handle);
		Addon* addon = db->GetAddon();

		napi_property_descriptor properties[2] = {};
		properties[0].name = addon->cs.changes.Value();
		properties[0].value = Napi::Number::New(env, changes);
		properties[0].attributes = DEFAULT_ATTRIBUTES;
		properties[1].name = addon->cs.lastInsertRowid.Value();
		if (stmt->safe_ints) {
			properties[1].value = Napi::BigInt::New(env, (int64_t)id);
		} else {
			properties[1].value = Napi::Number::New(env, (double)id);
		}
		properties[1].attributes = DEFAULT_ATTRIBUTES;

		napi_value result;
		napi_status status = napi_create_object(env, &result);
		assert(status == napi_ok);
		status = napi_define_properties(env, result, 2, properties);
		assert(status == napi_ok); ((void)status);
		STATEMENT_RETURN(Napi::Object(env, result));
	}
	STATEMENT_THROW();
}

NODE_METHOD(Statement::JS_get) {
	STATEMENT_START(REQUIRE_STATEMENT_RETURNS_DATA, DOES_NOT_MUTATE);
	int status = sqlite3_step(handle);
	if (status == SQLITE_ROW) {
		Napi::Value result = Data::GetRowJS(env, stmt, handle, stmt->safe_ints, stmt->mode);
		sqlite3_reset(handle);
		STATEMENT_RETURN(result);
	} else if (status == SQLITE_DONE) {
		sqlite3_reset(handle);
		STATEMENT_RETURN(env.Undefined());
	}
	sqlite3_reset(handle);
	STATEMENT_THROW();
}

NODE_METHOD(Statement::JS_all) {
	STATEMENT_START(REQUIRE_STATEMENT_RETURNS_DATA, DOES_NOT_MUTATE);
	const bool safe_ints = stmt->safe_ints;
	const char mode = stmt->mode;

	std::vector<napi_value> rows;
	rows.reserve(8);

	while (sqlite3_step(handle) == SQLITE_ROW) {
		rows.emplace_back(Data::GetRowJS(env, stmt, handle, safe_ints, mode));
	}

	if (sqlite3_reset(handle) == SQLITE_OK) {
		if (rows.size() > 0xffffffff) {
			ThrowRangeError(env, "Array overflow (too many rows returned)");
			db->GetState()->was_js_error = true;
		} else {
			Addon* addon = db->GetAddon();
			assert(!addon->ArrayFactory.IsEmpty());
			assert(!addon->ArrayAppender.IsEmpty());
			static const size_t batch_size = 1024;
			size_t first_batch_size = std::min(rows.size(), batch_size);
			Napi::Value result = SafeCall(env, addon->ArrayFactory.Value(), env.Undefined(), first_batch_size, rows.data());
			if (!env.IsExceptionPending()) {
				napi_value args[batch_size + 1];
				args[0] = result;
				for (size_t offset = first_batch_size; offset < rows.size(); offset += batch_size) {
					size_t count = std::min(rows.size() - offset, batch_size);
					std::copy_n(rows.data() + offset, count, args + 1);
					SafeCall(env, addon->ArrayAppender.Value(), env.Undefined(), count + 1, args);
					if (env.IsExceptionPending()) break;
				}
			}
			if (env.IsExceptionPending()) {
				db->GetState()->was_js_error = true;
			} else {
				STATEMENT_RETURN(result);
			}
		}
	}
	STATEMENT_THROW();
}

NODE_METHOD(Statement::JS_iterate) {
	UseAddon;
	UseIsolate;
	Napi::Function c = addon->StatementIterator.Value();
	addon->privileged_info = &info;
	Napi::Object iterator = SafeConstruct(env, c);
	addon->privileged_info = NULL;
	if (env.IsExceptionPending()) return env.Undefined();
	return iterator;
}

NODE_METHOD(Statement::JS_bind) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	if (stmt->bound) return ThrowTypeError(info.Env(), "The bind() method can only be invoked once per statement object");
	REQUIRE_DATABASE_OPEN(stmt->db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	STATEMENT_BIND(stmt->handle);
	stmt->bound = true;
	return info.This();
}

NODE_METHOD(Statement::JS_pluck) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError(info.Env(), "The pluck() method is only for statements that return data");
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	bool use = true;
	if (info.Length() != 0) { REQUIRE_ARGUMENT_BOOLEAN(first, use); }
	stmt->mode = use ? Data::PLUCK : stmt->mode == Data::PLUCK ? Data::FLAT : stmt->mode;
	return info.This();
}

NODE_METHOD(Statement::JS_expand) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError(info.Env(), "The expand() method is only for statements that return data");
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	bool use = true;
	if (info.Length() != 0) { REQUIRE_ARGUMENT_BOOLEAN(first, use); }
	stmt->mode = use ? Data::EXPAND : stmt->mode == Data::EXPAND ? Data::FLAT : stmt->mode;
	return info.This();
}

NODE_METHOD(Statement::JS_raw) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError(info.Env(), "The raw() method is only for statements that return data");
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	bool use = true;
	if (info.Length() != 0) { REQUIRE_ARGUMENT_BOOLEAN(first, use); }
	stmt->mode = use ? Data::RAW : stmt->mode == Data::RAW ? Data::FLAT : stmt->mode;
	return info.This();
}

NODE_METHOD(Statement::JS_safeIntegers) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	if (info.Length() == 0) stmt->safe_ints = true;
	else { REQUIRE_ARGUMENT_BOOLEAN(first, stmt->safe_ints); }
	return info.This();
}

NODE_METHOD(Statement::JS_columns) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError(info.Env(), "The columns() method is only for statements that return data");
	REQUIRE_DATABASE_OPEN(stmt->db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	Addon* addon = stmt->db->GetAddon();
	UseIsolate;

	int column_count = sqlite3_column_count(stmt->handle);
	Napi::Array columns = Napi::Array::New(env, column_count);

	Napi::String name = addon->cs.name.Value();
	Napi::String columnName = addon->cs.column.Value();
	Napi::String tableName = addon->cs.table.Value();
	Napi::String databaseName = addon->cs.database.Value();
	Napi::String typeName = addon->cs.type.Value();

	for (int i = 0; i < column_count; ++i) {
		Napi::Object column = Napi::Object::New(env);

		column.Set(name,
			InternalizedFromUtf8OrNull(env, sqlite3_column_name(stmt->handle, i), -1)
		);
		column.Set(columnName,
			InternalizedFromUtf8OrNull(env, sqlite3_column_origin_name(stmt->handle, i), -1)
		);
		column.Set(tableName,
			InternalizedFromUtf8OrNull(env, sqlite3_column_table_name(stmt->handle, i), -1)
		);
		column.Set(databaseName,
			InternalizedFromUtf8OrNull(env, sqlite3_column_database_name(stmt->handle, i), -1)
		);
		column.Set(typeName,
			InternalizedFromUtf8OrNull(env, sqlite3_column_decltype(stmt->handle, i), -1)
		);

		columns.Set(i, column);
	}

	return columns;
}

NODE_METHOD(Statement::JS_toString) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	Addon* addon = stmt->db->GetAddon();

	char* expanded = stmt->alive && stmt->bound ? sqlite3_expanded_sql(stmt->handle) : NULL;
	if (expanded != NULL) {
		Napi::Value ret = StringFromUtf8(info.Env(), expanded, -1);
		sqlite3_free(expanded);
		return ret;
	}

	return info.This().As<Napi::Object>()
		.Get(addon->cs.source.Value())
		.As<Napi::String>();
}

NODE_GETTER(Statement::JS_busy) {
	Statement* stmt = ::Unwrap<Statement>(info.This());
	return Napi::Boolean::New(info.Env(), stmt->alive && stmt->locked);
}
