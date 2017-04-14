// .each(...any boundValues, function callback) -> undefined

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("This statement does not return data. Use run() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, callback);
	QUERY_START(stmt, statement, STATEMENT_BIND, info, func_index);
	const bool safe_integers = (stmt->state & SAFE_INTS) != 0;
	const bool pluck = (stmt->state & PLUCK_COLUMN) != 0;
	
	stmt->db->busy = true;
	
	// Retrieve and feed rows.
	while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
		Nan::HandleScope scope;
		
		v8::Local<v8::Value> args[1];
		args[0] = pluck ? Data::GetValueJS(stmt->st_handle, 0, safe_integers)
		                : Data::GetRowJS(stmt->st_handle, safe_integers);
		v8::MaybeLocal<v8::Value> = callback_return_value = callback->Call(Nan::Null(), 1, args);
		
		// If an exception was thrown in the callback, clean up and stop.
		if (callback_return_value.IsEmpty()) {
			sqlite3_reset(stmt->st_handle);
			stmt->db->busy = false;
			stmt->db->was_js_error = true;
			QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS);
			return;
		}
	}
	
	stmt->db->busy = false;
	
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, Nan::Undefined());
	}
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS);
}
