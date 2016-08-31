#include <sqlite3.h>
#include <nan.h>
#include "close.h"
#include "../objects/database/database.h"
#include "../objects/statement/statement.h"
#include "../objects/transaction/transaction.h"
#include "../util/macros.h"

CloseWorker::CloseWorker(Database* db, bool still_connecting) : Nan::AsyncWorker(NULL),
	db(db),
	still_connecting(still_connecting) {}
void CloseWorker::Execute() {
	if (!still_connecting) {
		// Close and free any associated statements.
		db->stmts.Flush(Statement::DeleteHandles());
		db->transs.Flush(Transaction::DeleteHandles());
		
		int status1 = sqlite3_close(db->write_handle);
		int status2 = sqlite3_close(db->read_handle);
		db->write_handle = NULL;
		db->read_handle = NULL;
		
		if (status1 != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db->write_handle));
		} else if (status2 != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db->read_handle));
		}
	}
}
void CloseWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
    v8::Local<v8::Value> args[2] = {
    	Nan::New("close").ToLocalChecked(),
    	Nan::Null()
    };
    
	EMIT_EVENT_ASYNC(database, 2, args);
}
void CloseWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
    CONCAT2(message, "SQLite: ", ErrorMessage());
    v8::Local<v8::Value> args[2] = {
    	Nan::New("close").ToLocalChecked(),
    	Nan::Error(message)
    };
    
	EMIT_EVENT_ASYNC(database, 2, args);
}
