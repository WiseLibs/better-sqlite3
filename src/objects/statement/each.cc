// .each(...any boundValues, function callback) -> undefined

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("This statement does not return data. Use run() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, callback);
	QUERY_START(stmt, statement, STATEMENT_BIND, info, func_index);
	stmt->db->busy = true;
	bool safe_integers = (stmt->state & SAFE_INTS) != 0;
	
	// Retrieve and feed rows.
	while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
		Nan::HandleScope scope;
		v8::MaybeLocal<v8::Value> callback_return_value;
		
		// The pluck setting must be within the loop, because it could change in a callback.
		v8::Local<v8::Value> callbackValue = stmt->state & PLUCK_COLUMN
			? Data::GetValueJS(stmt->st_handle, 0, safe_integers)
			: Data::GetRowJS(stmt->st_handle, safe_integers);
		v8::Local<v8::Value> args[1] = {callbackValue};
		callback_return_value = callback->Call(Nan::Null(), 1, args);
		
		// If an exception was thrown in the callback, clean up and stop.
		if (callback_return_value.IsEmpty()) {
			sqlite3_reset(stmt->st_handle);
			stmt->db->busy = false;
			stmt->db->was_js_error = true;
			QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS);
			return;
		}
	}
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		stmt->db->busy = false;
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, Nan::Undefined());
	}
	
	stmt->db->busy = false;
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS);
}
