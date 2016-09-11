// .statement(string sql) -> Statement

NAN_METHOD(Database::CreateStatement) {
	REQUIRE_ARGUMENT_STRING(0, source);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	// Construct Statement object.
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Statement::constructor);
	v8::Local<v8::Object> statement = Nan::NewInstance(cons).ToLocalChecked();
	CONSTRUCTING_PRIVILEGES = false;
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(statement);
	
	// These properties should be added before others.
	stmt->db = db;
	statement->SetHiddenValue(NEW_INTERNAL_STRING_FAST("database"), info.This());
	
	// Digest the source string.
	v8::String::Value utf16(source);
	int source_bytes_plus1 = utf16.length() * sizeof (uint16_t) + 1;
	
	// Builds actual sqlite3_stmt handle.
	const void* tail;
	int status = sqlite3_prepare16(db->read_handle, *utf16, source_bytes_plus1, &stmt->st_handle, &tail);
	
	// Validates the newly created statement.
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errstr(status), ").");
		return Nan::ThrowError(message);
	}
	if (stmt->st_handle == NULL) {
		return Nan::ThrowTypeError("The supplied SQL string contains no statements.");
	}
	if (tail != (const void*)(*utf16 + utf16.length())) {
		return Nan::ThrowTypeError("The supplied SQL string contains more than one statement.");
	}
	
	// If the sqlite3_stmt is not read-only, replaces the handle with a proper one.
	if (!sqlite3_stmt_readonly(stmt->st_handle)) {
		sqlite3_finalize(stmt->st_handle);
		status = sqlite3_prepare16(db->write_handle, *utf16, source_bytes_plus1, &stmt->st_handle, NULL);
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errstr(status), ").");
			return Nan::ThrowError(message);
		}
		stmt->column_count = 0;
	} else {
		stmt->column_count = sqlite3_column_count(stmt->st_handle);
		if (stmt->column_count < 1) {
			return Nan::ThrowTypeError("This read-only SQL statement returns no result columns.");
		}
	}
	Nan::ForceSet(statement, NEW_INTERNAL_STRING_FAST("readonly"), stmt->column_count == 0 ? Nan::False() : Nan::True(), FROZEN);
	Nan::ForceSet(statement, NEW_INTERNAL_STRING_FAST("source"), source, FROZEN);
	stmt->BuildBindMap();
	
	// Pushes onto stmts set.
	stmt->id = NEXT_STATEMENT_ID++;
	db->stmts.insert(db->stmts.end(), stmt);
	
	info.GetReturnValue().Set(statement);
}
