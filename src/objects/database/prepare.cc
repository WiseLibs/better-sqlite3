// .prepare(string sql) -> Statement

NAN_METHOD(Database::Prepare) {
	REQUIRE_ARGUMENT_STRING(0, source);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Statement::constructor);
	Nan::MaybeLocal<v8::Object> maybeStatement = Nan::NewInstance(cons);
	CONSTRUCTING_PRIVILEGES = false;
	
	if (maybeStatement.IsEmpty()) {return;}
	v8::Local<v8::Object> statement = maybeStatement.ToLocalChecked();
	
	// Initializes c++ object properties.
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(statement);
	stmt->db = db;
	
	// Initializes JavaScript object properties.
	TRIM_STRING(source);
	Nan::Utf8String utf8(source);
	statement->SetHiddenValue(Nan::New("database").ToLocalChecked(), info.This());
	
	// Builds actual sqlite3_stmt handle.
	const char* tail;
	LOCK_DB(db->read_handle);
	int status = sqlite3_prepare_v2(db->read_handle, *utf8, utf8.length() + 1, &stmt->st_handle, &tail);
	
	// Validates the sqlite3_stmt.
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->read_handle), ").");
		UNLOCK_DB(db->read_handle);
		return Nan::ThrowError(message);
	}
	UNLOCK_DB(db->read_handle);
	if (stmt->st_handle == NULL) {
		return Nan::ThrowTypeError("The supplied SQL string contains no statements.");
	}
	if (tail != *utf8 + utf8.length()) {
		return Nan::ThrowTypeError("The db.prepare() method only accepts a single SQL statement.");
	}
	
	// If the sqlite3_stmt is not read-only, replaces the handle with a proper one.
	if (!sqlite3_stmt_readonly(stmt->st_handle)) {
		sqlite3_finalize(stmt->st_handle);
		LOCK_DB(db->write_handle);
		status = sqlite3_prepare_v2(db->write_handle, *utf8, utf8.length() + 1, &stmt->st_handle, NULL);
		
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->write_handle), ").");
			UNLOCK_DB(db->write_handle);
			return Nan::ThrowError(message);
		}
		UNLOCK_DB(db->write_handle);
		
		stmt->db_handle = db->write_handle;
		stmt->readonly = false;
	} else {
		stmt->db_handle = db->read_handle;
		stmt->readonly = true;
		
		if (sqlite3_column_count(stmt->st_handle) < 1) {
			return Nan::ThrowTypeError("This read-only SQL statement returns no result columns.");
		}
	}
	Nan::ForceSet(statement, Nan::New("readonly").ToLocalChecked(), stmt->readonly ? Nan::True() : Nan::False(), FROZEN);
	Nan::ForceSet(statement, Nan::New("source").ToLocalChecked(), source, FROZEN);
	
	// Pushes onto stmts set.
	stmt->id = NEXT_STATEMENT_ID++;
	db->stmts.insert(db->stmts.end(), stmt);
	
	info.GetReturnValue().Set(statement);
}
