// .all(...any boundValues) -> array of rows or plucked columns

NAN_METHOD(Statement::All) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	QUERY_START(stmt, statement, STATEMENT_BIND, info, info.Length());
	
	unsigned int row_count = 0;
	List<v8::Local<v8::Value>> rows;
	
	// Get result rows or plucked columns.
	if (stmt->state & PLUCK_COLUMN) {
		while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
			++row_count;
			rows.Add(Data::GetValueJS(stmt->st_handle, 0));
		}
	} else {
		while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
			++row_count;
			rows.Add(Data::GetRowJS(stmt->st_handle, stmt->column_count));
		}
	}
	
	// Transfer the result list into a JavaScript array.
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		v8::Local<v8::Array> returnedArray = Nan::New<v8::Array>(row_count);
		
		if (row_count > 0) {
			unsigned int i = 0;
			rows.Flush([&returnedArray, &i] (v8::Local<v8::Value> value) {
				Nan::Set(returnedArray, i++, value);
			});
		}
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, returnedArray);
	}
	
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS, sqlite3_errmsg(stmt->db->db_handle));
}
