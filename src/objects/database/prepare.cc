// .prepare(string sql) -> Statement

NAN_METHOD(Database::Prepare) {
	REQUIRE_ARGUMENT_STRING(0, source);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Statement::constructor);
	v8::Local<v8::Object> statement = cons->NewInstance(0, NULL);
	CONSTRUCTING_PRIVILEGES = false;
	
	TRIM_STRING(source);
	Nan::Utf8String utf8(source);
	
	// Initializes object properties.
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(statement);
	stmt->db = db;
	stmt->source = new FrozenBuffer(*utf8, utf8.length() + 1);
	statement->SetHiddenValue(Nan::New("database").ToLocalChecked(), info.This());
	Nan::ForceSet(statement, Nan::New("source").ToLocalChecked(), source, FROZEN);
	
	// Builds actual sqlite3_stmt handle.
	const char* tail;
	sqlite3_stmt* handle;
	LOCK_DB(db->read_handle);
	int status = sqlite3_prepare_v2(db->read_handle, stmt->source->data, stmt->source->length, &handle, &tail);
	
	stmt->handles = new HandleManager(stmt, 1);
	stmt->handles->SetFirst(handle);
	
	// Validates the sqlite3_stmt.
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->read_handle), ").");
		UNLOCK_DB(db->read_handle);
		return Nan::ThrowError(message);
	}
	UNLOCK_DB(db->read_handle);
	if (handle == NULL) {
		return Nan::ThrowError("The supplied SQL query contains no statements.");
	}
	if (tail != stmt->source->data + stmt->source->length - 1) {
		return Nan::ThrowError("The db.prepare() method only accepts a single SQL statement.");
	}
	
	// If the sqlite3_stmt is not read-only, replaces the handle with a proper one.
	if (!sqlite3_stmt_readonly(handle)) {
		sqlite3_finalize(handle);
		LOCK_DB(db->write_handle);
		status = sqlite3_prepare_v2(db->write_handle, stmt->source->data, stmt->source->length, &handle, NULL);
		stmt->handles->SetFirst(handle);
		
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->write_handle), ").");
			UNLOCK_DB(db->write_handle);
			return Nan::ThrowError("Failed to construct the SQL statement.");
		}
		UNLOCK_DB(db->write_handle);
		
		stmt->db_handle = db->write_handle;
		stmt->readonly = false;
	} else {
		stmt->db_handle = db->read_handle;
		stmt->readonly = true;
		
		if (sqlite3_column_count(handle) < 1) {
			return Nan::ThrowTypeError("This read-only SQL statement returns no result columns.");
		}
	}
	
	// Pushes onto stmts list.
	db->stmts.Add(stmt);
	
	info.GetReturnValue().Set(statement);
}
