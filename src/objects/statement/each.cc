// .each(...any boundValues, Function callback) -> undefined

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("This statement does not return data. Use run() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, callback);
	QUERY_START(stmt, statement, STATEMENT_BIND, SQLITE_TRANSIENT, info, func_index);
	stmt->db->in_each = true;
	
	// Retrieve and feed rows.
	while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
		v8::MaybeLocal<v8::Value> callback_return_value;
		
		// The pluck setting must be within the loop, because it could change in a callback.
		v8::Local<v8::Value> callbackValue = stmt->state & PLUCK_COLUMN
			? Data::GetValueJS(stmt->st_handle, 0)
			: Data::GetRowJS(stmt->st_handle, stmt->column_count);
		v8::Local<v8::Value> args[1] = {callbackValue};
		callback_return_value = callback->Call(Nan::Null(), 1, args);
		
		// If an exception was thrown in the callback, clean up and stop.
		if (callback_return_value.IsEmpty()) {
			sqlite3_reset(stmt->st_handle);
			stmt->db->in_each = false;
			QUERY_CLEANUP(stmt, STATEMENT_CLEAR_BINDINGS);
			return;
		}
		
		// Refresh SAFE_INTEGERS, since anything could have happened during the callback.
		SAFE_INTEGERS = stmt->state & SAFE_INTS ? true : false;
	}
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		stmt->db->in_each = false;
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, Nan::Undefined());
	}
	
	stmt->db->in_each = false;
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS, sqlite3_errmsg(stmt->db->db_handle));
}
