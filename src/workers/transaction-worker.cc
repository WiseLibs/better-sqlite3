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
	int status;
	sqlite3* db_handle = obj->db->write_handle;
	TransactionHandles* t_handles = obj->db->t_handles;
	
	LOCK_DB(db_handle);
	int total_changes_before = sqlite3_total_changes(db_handle);
	
	// Begin Transaction
	sqlite3_step(t_handles->begin);
	status = sqlite3_reset(t_handles->begin);
	if (status != SQLITE_OK) {
		UNLOCK_DB(db_handle);
		SetErrorMessage(sqlite3_errstr(status));
		return;
	}
	
	// Execute statements
	for (unsigned int i=0; i<obj->handle_count; ++i) {
		sqlite3_step(obj->handles[i]);
		status = sqlite3_reset(obj->handles[i]);
		if (status != SQLITE_OK) {
			sqlite3_step(t_handles->rollback);
			int status2 = sqlite3_reset(t_handles->rollback);
			UNLOCK_DB(db_handle);
			if (status2 == SQLITE_OK) {
				SetErrorMessage(sqlite3_errstr(status));
			} else {
				CONCAT3(message, sqlite3_errstr(status), "\nSQLite Rollback Failed: ", sqlite3_errstr(status2))
				SetErrorMessage(message);
			}
			return;
		}
	}
	
	// Commit Transaction
	sqlite3_step(t_handles->commit);
	status = sqlite3_reset(t_handles->commit);
	if (status != SQLITE_OK) {
		sqlite3_step(t_handles->rollback);
		int status2 = sqlite3_reset(t_handles->rollback);
		UNLOCK_DB(db_handle);
		if (status2 == SQLITE_OK) {
			SetErrorMessage(sqlite3_errstr(status));
		} else {
			CONCAT3(message, sqlite3_errstr(status), "\nSQLite Rollback Failed: ", sqlite3_errstr(status2))
			SetErrorMessage(message);
		}
		return;
	}
	
	changes = sqlite3_total_changes(db_handle) - total_changes_before;
	id = sqlite3_last_insert_rowid(db_handle);
	UNLOCK_DB(db_handle);
}
void TransactionWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	Nan::ForceSet(object, NEW_INTERNAL_STRING_FAST("changes"), Nan::New<v8::Number>((double)changes));
	Nan::ForceSet(object, NEW_INTERNAL_STRING_FAST("id"), Nan::New<v8::Number>((double)id));
	
	Resolve(object);
}
