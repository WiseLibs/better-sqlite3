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
	
	int status;
	LOCK_DB(db_handle);
	int total_changes_before = sqlite3_total_changes(db_handle);
	
	// Begin Transaction
	status = sqlite3_step(t_handles->begin);
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
		sqlite3_reset(t_handles->begin);
		UNLOCK_DB(db_handle);
		return;
	}
	sqlite3_reset(t_handles->begin);
	
	// Execute statements
	for (unsigned int i=0; i<obj->handle_count; ++i) {
		status = sqlite3_step(obj->handles[i]);
		if (status != SQLITE_DONE) {
			if (status != SQLITE_ROW) {
				SetErrorMessage(sqlite3_errmsg(db_handle));
			} else {
				SetErrorMessage("Unexpected data returned by a write transaction.");
			}
			sqlite3_reset(obj->handles[i]);
			sqlite3_step(t_handles->rollback);
			sqlite3_reset(t_handles->rollback);
			UNLOCK_DB(db_handle);
			return;
		}
		sqlite3_reset(obj->handles[i]);
	}
	
	// Commit Transaction
	status = sqlite3_step(t_handles->commit);
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
		sqlite3_reset(t_handles->commit);
		sqlite3_step(t_handles->rollback);
		sqlite3_reset(t_handles->rollback);
		UNLOCK_DB(db_handle);
		return;
	}
	sqlite3_reset(t_handles->commit);
	
	changes = sqlite3_total_changes(db_handle) - total_changes_before;
	id = sqlite3_last_insert_rowid(db_handle);
	
	UNLOCK_DB(db_handle);
}
void TransactionWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	Nan::ForceSet(object, Nan::New("changes").ToLocalChecked(), Nan::New<v8::Number>((double)changes));
	Nan::ForceSet(object, Nan::New("id").ToLocalChecked(), Nan::New<v8::Number>((double)id));
	
	Resolve(object);
}
