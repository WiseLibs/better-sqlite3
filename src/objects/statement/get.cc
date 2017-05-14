// .get(...any boundValues) -> row or plucked column

NAN_METHOD(Statement::Get) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("This statement does not return data. Use run() instead");
	}
	QUERY_START(stmt, statement, STATEMENT_BIND, info, info.Length());
	
	int status = sqlite3_step(stmt->st_handle);
	if (status == SQLITE_ROW) {
		v8::Local<v8::Value> returnedValue = stmt->state & PLUCK_COLUMN
			? Data::GetValueJS(stmt->st_handle, 0, (stmt->state & SAFE_INTS) != 0)
			: Data::GetRowJS(stmt->st_handle, (stmt->state & SAFE_INTS) != 0);
		sqlite3_reset(stmt->st_handle);
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, returnedValue);
	} else if (status == SQLITE_DONE) {
		sqlite3_reset(stmt->st_handle);
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, Nan::Undefined());
	}
	
	sqlite3_reset(stmt->st_handle);
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS);
}
