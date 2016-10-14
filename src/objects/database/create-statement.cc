// .prepare(string sql) -> Statement

NAN_METHOD(Database::CreateStatement) {
	REQUIRE_ARGUMENT_STRING(0, source);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->in_each) {
		return Nan::ThrowTypeError("This database connection is busy executing a query.");
	}
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	// Construct Statement object.
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Statement::constructor);
	v8::Local<v8::Object> statement = Nan::NewInstance(cons).ToLocalChecked();
	CONSTRUCTING_PRIVILEGES = false;
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(statement);
	
	// This property should be added before others.
	stmt->db = db;
	
	// Digest the source string.
	v8::String::Value utf16(source);
	
	// Builds actual sqlite3_stmt handle.
	const void* tail;
	int status = sqlite3_prepare16_v2(db->db_handle, *utf16, utf16.length() * sizeof (uint16_t) + 1, &stmt->st_handle, &tail);
	
	// Validates the newly created statement.
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->db_handle), ").");
		return Nan::ThrowError(message.c_str());
	}
	if (stmt->st_handle == NULL) {
		return Nan::ThrowTypeError("The supplied SQL string contains no statements.");
	}
	if (tail != (const void*)(*utf16 + utf16.length())) {
		return Nan::ThrowTypeError("The supplied SQL string contains more than one statement.");
	}
	
	// Determine if the sqlite3_stmt returns data or not.
	int column_count = sqlite3_column_count(stmt->st_handle);
	if (!sqlite3_stmt_readonly(stmt->st_handle) || column_count < 1) {
		stmt->column_count = 0;
	} else {
		stmt->column_count = column_count;
		stmt->state |= RETURNS_DATA;
	}
	Nan::ForceSet(statement, NEW_INTERNAL_STRING_FAST("source"), source, FROZEN);
	Nan::ForceSet(statement, NEW_INTERNAL_STRING_FAST("database"),  info.This(), FROZEN);
	if (db->safe_ints) {stmt->state |= SAFE_INTS;}
	
	// Pushes onto stmts set.
	stmt->id = NEXT_STATEMENT_ID++;
	db->stmts.insert(db->stmts.end(), stmt);
	
	info.GetReturnValue().Set(statement);
}
