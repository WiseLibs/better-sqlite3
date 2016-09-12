#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "transaction-worker.h"
#include "query-worker.h"
#include "../objects/database/database.h"
#include "../objects/transaction/transaction.h"
#include "../util/macros.h"

TransactionWorker::TransactionWorker(Transaction* trans, Nan::Callback* cb)
	: QueryWorker<Transaction, Nan::AsyncWorker>(trans, cb) {}
void TransactionWorker::Execute() {
	sqlite3* db_handle = obj->db->write_handle;
	TransactionHandles* t_handles = obj->db->t_handles;
	
	LOCK_DB(db_handle);
	
	// Begin Transaction
	sqlite3_step(t_handles->begin);
	if (sqlite3_reset(t_handles->begin) != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
		UNLOCK_DB(db_handle);
		return;
	}
	
	changes = 0;
	
	// Execute statements
	for (unsigned int i=0; i<obj->handle_count; ++i) {
		int total_changes_before = sqlite3_total_changes(db_handle);
		
		sqlite3_step(obj->handles[i]);
		if (sqlite3_reset(obj->handles[i]) != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db_handle));
			sqlite3_step(t_handles->rollback);
			sqlite3_reset(t_handles->rollback);
			UNLOCK_DB(db_handle);
			return;
		}
		
		if (sqlite3_total_changes(db_handle) != total_changes_before) {
			changes += sqlite3_changes(db_handle);
		}
	}
	
	// Commit Transaction
	sqlite3_step(t_handles->commit);
	if (sqlite3_reset(t_handles->commit) != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
		sqlite3_step(t_handles->rollback);
		sqlite3_reset(t_handles->rollback);
		UNLOCK_DB(db_handle);
		return;
	}
	
	id = sqlite3_last_insert_rowid(db_handle);
	UNLOCK_DB(db_handle);
}
void TransactionWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	Nan::Set(object, NEW_INTERNAL_STRING_FAST("changes"), Nan::New<v8::Number>((double)changes));
	Nan::Set(object, NEW_INTERNAL_STRING_FAST("lastInsertROWID"), Nan::New<v8::Number>((double)id));
	
	Resolve(object);
}
