// .run(...any boundValues) -> info object

NAN_METHOD(Statement::Run) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count != 0) {
		return Nan::ThrowTypeError("This statement is read-only. Use get(), all(), or each() instead.");
	}
	QUERY_START(stmt, statement, STATEMENT_BIND, info, info.Length());
	
	sqlite3* db_handle = stmt->db->db_handle;
	int total_changes_before = sqlite3_total_changes(db_handle);
	
	sqlite3_step(stmt->st_handle);
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		int changes = sqlite3_total_changes(db_handle) == total_changes_before ? 0 : sqlite3_changes(db_handle);
		sqlite3_int64 id = sqlite3_last_insert_rowid(db_handle);
		v8::Local<v8::Object> returned_object = Nan::New<v8::Object>();
		Nan::Set(returned_object, NEW_INTERNAL_STRING_FAST("changes"), Nan::New<v8::Number>(static_cast<double>(changes)));
		Nan::Set(returned_object, NEW_INTERNAL_STRING_FAST("lastInsertROWID"), Int64::NewProperInteger(id));
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, returned_object);
	}
	
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS, sqlite3_errmsg(stmt->db->db_handle));
}
