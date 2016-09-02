#include <sqlite3.h>
#include <nan.h>
#include "transaction-worker.h"
#include "write-worker.h"
#include "../objects/database/database.h"
#include "../objects/transaction/transaction.h"
#include "../util/macros.h"

TransactionWorker::TransactionWorker(Transaction* trans, Nan::Callback* cb)
	: WriteWorker(cb, true), trans(trans) {}
void TransactionWorker::Execute() {
	// LOCK_DB(db_handle);
	// int status = sqlite3_step(handle);
	// if (status == SQLITE_DONE || status == SQLITE_ROW) {
	// 	changes = sqlite3_changes(db_handle);
	// 	id = sqlite3_last_insert_rowid(db_handle);
	// } else {
	// 	SetErrorMessage(sqlite3_errmsg(db_handle));
	// }
	// UNLOCK_DB(db_handle);
}
void TransactionWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> obj = Nan::New<v8::Object>();
	Nan::ForceSet(obj, Nan::New("changes").ToLocalChecked(), Nan::New<v8::Number>((double)changes));
	Nan::ForceSet(obj, Nan::New("id").ToLocalChecked(), Nan::New<v8::Number>((double)id));
	
	// Resolve
	FinishRequest();
	v8::Local<v8::Value> args[2] = {Nan::Null(), obj};
	Nan::AsyncWorker::callback->Call(2, args);
}
void TransactionWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
	CONCAT2(message, "SQLite: ", Nan::AsyncWorker::ErrorMessage());
	
	// Reject
	FinishRequest();
	v8::Local<v8::Value> args[1] = {Nan::Error(message)};
	Nan::AsyncWorker::callback->Call(1, args);
}
void TransactionWorker::FinishRequest() {
	trans->busy = false;
	trans->db->requests -= 1;
	trans->Unref();
	if (!trans->bound) {
		for (unsigned int i=0; i<trans->handle_count; ++i) {
			sqlite3_clear_bindings(trans->handles[i]);
		}
	}
	if (trans->db->state == DB_DONE && trans->db->requests == 0) {
		trans->db->ActuallyClose();
	} else {
		trans->db->write_lock = 0;
		if (!trans->db->write_queue.isEmpty()) {
			trans->db->write_queue.FlushSome([this] (WriteWorker* worker) -> bool {
				if (worker->is_transaction) {
					trans->db->write_lock = trans->db->pending_write_statements == 0 ? 2 : 1;
					return false;
				}
				trans->db->pending_write_statements += 1;
				Nan::AsyncQueueWorker(worker);
				return true;
			});
			if (trans->db->write_lock == 2) {
				Nan::AsyncQueueWorker(trans->db->write_queue.Shift());
			}
		}
	}
}
