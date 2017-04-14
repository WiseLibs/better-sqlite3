// .all(...any boundValues) -> array of rows or plucked columns

NAN_METHOD(Statement::All) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("This statement does not return data. Use run() instead.");
	}
	QUERY_START(stmt, statement, STATEMENT_BIND, info, info.Length());
	const bool safe_integers = (stmt->state & SAFE_INTS) != 0;
	v8::Local<v8::Array> rows = Nan::New<v8::Array>(0);
	unsigned int row_count = 0;
	
	// Get result rows or plucked columns.
	if (stmt->state & PLUCK_COLUMN) {
		while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
			Nan::Set(rows, row_count++, Data::GetValueJS(stmt->st_handle, 0, safe_integers));
		}
	} else {
		while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
			Nan::Set(rows, row_count++, Data::GetRowJS(stmt->st_handle, safe_integers));
		}
	}
	
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, rows);
	}
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS);
}
