// .get(...any boundValues) -> row or plucked column

NAN_METHOD(Statement::Get) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	QUERY_START(stmt, statement, STATEMENT_BIND, info, info.Length());
	
	int status = sqlite3_step(stmt->st_handle);
	if (status == SQLITE_ROW) {
		Data::Row row(stmt->st_handle, stmt->column_count);
		v8::Local<v8::Value> returned_value;
		
		// Get result row, or plucked column.
		if (stmt->state & PLUCK_COLUMN) {
			returned_value = row.values[0]->ToJS();
		} else {
			returned_value = Nan::New<v8::Object>();
			v8::Local<v8::Object> returned_object = v8::Local<v8::Object>::Cast(returned_value);
			for (int i=0; i<row.column_count; ++i) {
				Nan::Set(returned_object, NEW_INTERNAL_STRING16(sqlite3_column_name16(stmt->st_handle, i)), row.values[i]->ToJS());
			}
		}
		
		sqlite3_reset(stmt->st_handle);
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, returned_value);
	} else if (status == SQLITE_DONE) {
		sqlite3_reset(stmt->st_handle);
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, Nan::Undefined());
	}
	
	sqlite3_reset(stmt->st_handle);
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS, sqlite3_errmsg(stmt->db->db_handle));
}
