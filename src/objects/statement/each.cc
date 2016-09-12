// .each(...any boundValues, Function callback) -> undefined

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, callback);
	QUERY_START(stmt, statement, STATEMENT_BIND, info, func_index);
	stmt->db->in_each = true;
	
	
	// Retrieve and feed rows.
	while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
		// Nan::HandleScope scope;
		Data::Row row(stmt->st_handle, stmt->column_count);
		v8::MaybeLocal<v8::Value> callback_return_value;
		
		// Flush row to callback.
		if (stmt->state & PLUCK_COLUMN) {
			v8::Local<v8::Value> args[1] = {row.values[0]->ToJS()};
			callback_return_value = callback->Call(Nan::Null(), 1, args);
		} else {
			v8::Local<v8::Object> object = Nan::New<v8::Object>();
			for (int i=0; i<row.column_count; ++i) {
				Nan::Set(object, NEW_INTERNAL_STRING16(sqlite3_column_name16(stmt->st_handle, i)), row.values[i]->ToJS());
			}
			v8::Local<v8::Value> args[1] = {object};
			callback_return_value = callback->Call(Nan::Null(), 1, args);
		}
		
		// If an exception was thrown in the callback, clean up and stop.
		if (callback_return_value.IsEmpty()) {
			sqlite3_reset(stmt->st_handle);
			stmt->db->in_each = false;
			QUERY_CLEANUP(stmt, STATEMENT_CLEAR_BINDINGS);
			return;
		}
		
	}
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		stmt->db->in_each = false;
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, Nan::Undefined());
	}
	
	stmt->db->in_each = false;
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS, sqlite3_errmsg(stmt->db->db_handle));
}
