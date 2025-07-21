Statement::Statement(
	Database* db,
	sqlite3_stmt* handle,
	sqlite3_uint64 id,
	bool returns_data
) :
	node::ObjectWrap(),
	db(db),
	handle(handle),
	extras(new Extras(id)),
	alive(true),
	locked(false),
	bound(false),
	has_bind_map(false),
	safe_ints(db->GetState()->safe_ints),
	mode(Data::FLAT),
	returns_data(returns_data) {
	assert(db != NULL);
	assert(handle != NULL);
	assert(db->GetState()->open);
	assert(!db->GetState()->busy);
	db->AddStatement(this);
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
BindMap* Statement::GetBindMap(v8::Isolate* isolate) {
	if (has_bind_map) return &extras->bind_map;
	BindMap* bind_map = &extras->bind_map;
	int param_count = sqlite3_bind_parameter_count(handle);
	for (int i = 1; i <= param_count; ++i) {
		const char* name = sqlite3_bind_parameter_name(handle, i);
		if (name != NULL) bind_map->Add(isolate, name + 1, i);
	}
	has_bind_map = true;
	return bind_map;
}

Statement::Extras::Extras(sqlite3_uint64 id)
	: bind_map(0), id(id) {}

INIT(Statement::Init) {
	v8::Local<v8::FunctionTemplate> t = NewConstructorTemplate(isolate, data, JS_new, "Statement");
	SetPrototypeMethod(isolate, data, t, "run", JS_run);
	SetPrototypeMethod(isolate, data, t, "get", JS_get);
	SetPrototypeMethod(isolate, data, t, "all", JS_all);
	SetPrototypeMethod(isolate, data, t, "iterate", JS_iterate);
	SetPrototypeMethod(isolate, data, t, "bind", JS_bind);
	SetPrototypeMethod(isolate, data, t, "pluck", JS_pluck);
	SetPrototypeMethod(isolate, data, t, "expand", JS_expand);
	SetPrototypeMethod(isolate, data, t, "raw", JS_raw);
	SetPrototypeMethod(isolate, data, t, "safeIntegers", JS_safeIntegers);
	SetPrototypeMethod(isolate, data, t, "columns", JS_columns);
	SetPrototypeGetter(isolate, data, t, "busy", JS_busy);
	return t->GetFunction(OnlyContext).ToLocalChecked();
}

NODE_METHOD(Statement::JS_new) {
	UseAddon;
	if (!addon->privileged_info) {
		return ThrowTypeError("Statements can only be constructed by the db.prepare() method");
	}
	assert(info.IsConstructCall());
	Database* db = Unwrap<Database>(addon->privileged_info->This());
	REQUIRE_DATABASE_OPEN(db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(db->GetState());

	v8::Local<v8::String> source = (*addon->privileged_info)[0].As<v8::String>();
	v8::Local<v8::Object> database = (*addon->privileged_info)[1].As<v8::Object>();
	bool pragmaMode = (*addon->privileged_info)[2].As<v8::Boolean>()->Value();
	int flags = SQLITE_PREPARE_PERSISTENT;

	if (pragmaMode) {
		REQUIRE_DATABASE_NO_ITERATORS_UNLESS_UNSAFE(db->GetState());
		flags = 0;
	}

	UseIsolate;
	v8::String::Utf8Value utf8(isolate, source);
	sqlite3_stmt* handle;
	const char* tail;

	if (sqlite3_prepare_v3(db->GetHandle(), *utf8, utf8.length() + 1, flags, &handle, &tail) != SQLITE_OK) {
		return db->ThrowDatabaseError();
	}
	if (handle == NULL) {
		return ThrowRangeError("The supplied SQL string contains no statements");
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
			return ThrowRangeError("The supplied SQL string contains more than one statement");
		}
	}

	UseContext;
	bool returns_data = sqlite3_column_count(handle) >= 1 || pragmaMode;
	Statement* stmt = new Statement(db, handle, addon->NextId(), returns_data);
	stmt->Wrap(info.This());
	SetFrozen(isolate, ctx, info.This(), addon->cs.reader, v8::Boolean::New(isolate, returns_data));
	SetFrozen(isolate, ctx, info.This(), addon->cs.readonly, v8::Boolean::New(isolate, sqlite3_stmt_readonly(handle) != 0));
	SetFrozen(isolate, ctx, info.This(), addon->cs.source, source);
	SetFrozen(isolate, ctx, info.This(), addon->cs.database, database);

	info.GetReturnValue().Set(info.This());
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
		UseContext;
		v8::Local<v8::Object> result = v8::Object::New(isolate);
		result->Set(ctx, addon->cs.changes.Get(isolate), v8::Int32::New(isolate, changes)).FromJust();
		result->Set(ctx, addon->cs.lastInsertRowid.Get(isolate),
			stmt->safe_ints
				? v8::BigInt::New(isolate, id).As<v8::Value>()
				: v8::Number::New(isolate, (double)id).As<v8::Value>()
		).FromJust();
		STATEMENT_RETURN(result);
	}
	STATEMENT_THROW();
}

NODE_METHOD(Statement::JS_get) {
	STATEMENT_START(REQUIRE_STATEMENT_RETURNS_DATA, DOES_NOT_MUTATE);
	int status = sqlite3_step(handle);
	if (status == SQLITE_ROW) {
		v8::Local<v8::Value> result = Data::GetRowJS(isolate, OnlyContext, handle, stmt->safe_ints, stmt->mode);
		sqlite3_reset(handle);
		STATEMENT_RETURN(result);
	} else if (status == SQLITE_DONE) {
		sqlite3_reset(handle);
		STATEMENT_RETURN(v8::Undefined(isolate));
	}
	sqlite3_reset(handle);
	STATEMENT_THROW();
}

NODE_METHOD(Statement::JS_all) {
	STATEMENT_START(REQUIRE_STATEMENT_RETURNS_DATA, DOES_NOT_MUTATE);
	UseContext;
	const bool safe_ints = stmt->safe_ints;
	const char mode = stmt->mode;

#if !defined(NODE_MODULE_VERSION) || NODE_MODULE_VERSION < 127
	bool js_error = false;
	uint32_t row_count = 0;
	v8::Local<v8::Array> result = v8::Array::New(isolate, 0);

	while (sqlite3_step(handle) == SQLITE_ROW) {
		if (row_count == 0xffffffff) { ThrowRangeError("Array overflow (too many rows returned)"); js_error = true; break; }
		result->Set(ctx, row_count++, Data::GetRowJS(isolate, ctx, handle, safe_ints, mode)).FromJust();
	}

	if (sqlite3_reset(handle) == SQLITE_OK && !js_error) {
		STATEMENT_RETURN(result);
	}
	if (js_error) db->GetState()->was_js_error = true;
	STATEMENT_THROW();
#else
	v8::LocalVector<v8::Value> rows(isolate);
	rows.reserve(8);

	if (mode == Data::FLAT) {
		RowBuilder rowBuilder(isolate, handle, safe_ints);
		while (sqlite3_step(handle) == SQLITE_ROW) {
			rows.emplace_back(rowBuilder.GetRowJS());
		}
	} else {
		while (sqlite3_step(handle) == SQLITE_ROW) {
			rows.emplace_back(Data::GetRowJS(isolate, ctx, handle, safe_ints, mode));
		}
	}

	if (sqlite3_reset(handle) == SQLITE_OK) {
		if (rows.size() > 0xffffffff) {
			ThrowRangeError("Array overflow (too many rows returned)");
			db->GetState()->was_js_error = true;
		} else {
			STATEMENT_RETURN(v8::Array::New(isolate, rows.data(), rows.size()));
		}
	}
	STATEMENT_THROW();
#endif
}

NODE_METHOD(Statement::JS_iterate) {
	UseAddon;
	UseIsolate;
	v8::Local<v8::Function> c = addon->StatementIterator.Get(isolate);
	addon->privileged_info = &info;
	v8::MaybeLocal<v8::Object> maybeIterator = c->NewInstance(OnlyContext, 0, NULL);
	addon->privileged_info = NULL;
	if (!maybeIterator.IsEmpty()) info.GetReturnValue().Set(maybeIterator.ToLocalChecked());
}

NODE_METHOD(Statement::JS_bind) {
	Statement* stmt = Unwrap<Statement>(info.This());
	if (stmt->bound) return ThrowTypeError("The bind() method can only be invoked once per statement object");
	REQUIRE_DATABASE_OPEN(stmt->db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	STATEMENT_BIND(stmt->handle);
	stmt->bound = true;
	info.GetReturnValue().Set(info.This());
}

NODE_METHOD(Statement::JS_pluck) {
	Statement* stmt = Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError("The pluck() method is only for statements that return data");
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	bool use = true;
	if (info.Length() != 0) { REQUIRE_ARGUMENT_BOOLEAN(first, use); }
	stmt->mode = use ? Data::PLUCK : stmt->mode == Data::PLUCK ? Data::FLAT : stmt->mode;
	info.GetReturnValue().Set(info.This());
}

NODE_METHOD(Statement::JS_expand) {
	Statement* stmt = Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError("The expand() method is only for statements that return data");
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	bool use = true;
	if (info.Length() != 0) { REQUIRE_ARGUMENT_BOOLEAN(first, use); }
	stmt->mode = use ? Data::EXPAND : stmt->mode == Data::EXPAND ? Data::FLAT : stmt->mode;
	info.GetReturnValue().Set(info.This());
}

NODE_METHOD(Statement::JS_raw) {
	Statement* stmt = Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError("The raw() method is only for statements that return data");
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	bool use = true;
	if (info.Length() != 0) { REQUIRE_ARGUMENT_BOOLEAN(first, use); }
	stmt->mode = use ? Data::RAW : stmt->mode == Data::RAW ? Data::FLAT : stmt->mode;
	info.GetReturnValue().Set(info.This());
}

NODE_METHOD(Statement::JS_safeIntegers) {
	Statement* stmt = Unwrap<Statement>(info.This());
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);
	if (info.Length() == 0) stmt->safe_ints = true;
	else { REQUIRE_ARGUMENT_BOOLEAN(first, stmt->safe_ints); }
	info.GetReturnValue().Set(info.This());
}

NODE_METHOD(Statement::JS_columns) {
	Statement* stmt = Unwrap<Statement>(info.This());
	if (!stmt->returns_data) return ThrowTypeError("The columns() method is only for statements that return data");
	REQUIRE_DATABASE_OPEN(stmt->db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(stmt->db->GetState());
	Addon* addon = stmt->db->GetAddon();
	UseIsolate;

#if !defined(NODE_MODULE_VERSION) || NODE_MODULE_VERSION < 127
	UseContext;
	int column_count = sqlite3_column_count(stmt->handle);
	v8::Local<v8::Array> columns = v8::Array::New(isolate);

	v8::Local<v8::String> name = addon->cs.name.Get(isolate);
	v8::Local<v8::String> columnName = addon->cs.column.Get(isolate);
	v8::Local<v8::String> tableName = addon->cs.table.Get(isolate);
	v8::Local<v8::String> databaseName = addon->cs.database.Get(isolate);
	v8::Local<v8::String> typeName = addon->cs.type.Get(isolate);

	for (int i = 0; i < column_count; ++i) {
		v8::Local<v8::Object> column = v8::Object::New(isolate);

		column->Set(ctx, name,
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_name(stmt->handle, i), -1)
		).FromJust();
		column->Set(ctx, columnName,
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_origin_name(stmt->handle, i), -1)
		).FromJust();
		column->Set(ctx, tableName,
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_table_name(stmt->handle, i), -1)
		).FromJust();
		column->Set(ctx, databaseName,
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_database_name(stmt->handle, i), -1)
		).FromJust();
		column->Set(ctx, typeName,
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_decltype(stmt->handle, i), -1)
		).FromJust();

		columns->Set(ctx, i, column).FromJust();
	}

	info.GetReturnValue().Set(columns);
#else
	v8::LocalVector<v8::Name> keys(isolate);
	keys.reserve(5);
	keys.emplace_back(addon->cs.name.Get(isolate).As<v8::Name>());
	keys.emplace_back(addon->cs.column.Get(isolate).As<v8::Name>());
	keys.emplace_back(addon->cs.table.Get(isolate).As<v8::Name>());
	keys.emplace_back(addon->cs.database.Get(isolate).As<v8::Name>());
	keys.emplace_back(addon->cs.type.Get(isolate).As<v8::Name>());

	int column_count = sqlite3_column_count(stmt->handle);
	v8::LocalVector<v8::Value> columns(isolate);
	columns.reserve(column_count);

	for (int i = 0; i < column_count; ++i) {
		v8::LocalVector<v8::Value> values(isolate);
		keys.reserve(5);
		values.emplace_back(
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_name(stmt->handle, i), -1)
		);
		values.emplace_back(
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_origin_name(stmt->handle, i), -1)
		);
		values.emplace_back(
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_table_name(stmt->handle, i), -1)
		);
		values.emplace_back(
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_database_name(stmt->handle, i), -1)
		);
		values.emplace_back(
			InternalizedFromUtf8OrNull(isolate, sqlite3_column_decltype(stmt->handle, i), -1)
		);
		columns.emplace_back(
			v8::Object::New(isolate,
				v8::Object::New(isolate)->GetPrototype(),
				keys.data(),
				values.data(),
				keys.size()
			)
		);
	}

	info.GetReturnValue().Set(
		v8::Array::New(isolate, columns.data(), columns.size())
	);
#endif
}

NODE_GETTER(Statement::JS_busy) {
	Statement* stmt = Unwrap<Statement>(info.This());
	info.GetReturnValue().Set(stmt->alive && stmt->locked);
}
