// .run(...any boundValues) -> info object

NAN_METHOD(Transaction::Run) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	QUERY_START(trans, transaction, TRANSACTION_BIND, info, info.Length());
	
	sqlite3* db_handle = trans->db->db_handle;
	TransactionHandles t_handles = trans->db->t_handles;
	
	// Begin Transaction
	sqlite3_step(t_handles.begin);
	if (sqlite3_reset(t_handles.begin) != SQLITE_OK) {
		QUERY_THROW(trans, TRANSACTION_CLEAR_BINDINGS, db_handle);
	}
	
	int changes = 0;
	
	// Execute statements
	for (unsigned int i=0; i<trans->handle_count; ++i) {
		int total_changes_before = sqlite3_total_changes(db_handle);
		
		sqlite3_step(trans->handles[i]);
		if (sqlite3_reset(trans->handles[i]) != SQLITE_OK) {
			QUERY_THROW_STAY(trans, TRANSACTION_CLEAR_BINDINGS, db_handle);
			sqlite3_step(t_handles.rollback);
			sqlite3_reset(t_handles.rollback);
			return;
		}
		
		if (sqlite3_total_changes(db_handle) != total_changes_before) {
			changes += sqlite3_changes(db_handle);
		}
	}
	
	// Commit Transaction
	sqlite3_step(t_handles.commit);
	if (sqlite3_reset(t_handles.commit) != SQLITE_OK) {
		QUERY_THROW_STAY(trans, TRANSACTION_CLEAR_BINDINGS, db_handle);
		sqlite3_step(t_handles.rollback);
		sqlite3_reset(t_handles.rollback);
		return;
	}
	
	// Return info object.
	sqlite3_int64 id = sqlite3_last_insert_rowid(db_handle);
	v8::Local<v8::Object> returnedObject = Nan::New<v8::Object>();
	Nan::Set(returnedObject, NEW_INTERNAL_STRING_FAST("changes"), Nan::New<v8::Number>(static_cast<double>(changes)));
	Nan::Set(returnedObject, NEW_INTERNAL_STRING_FAST("lastInsertROWID"), Int64::NewProperInteger(id));
	QUERY_RETURN(trans, TRANSACTION_CLEAR_BINDINGS, returnedObject);
}
