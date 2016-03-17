#include <sqlite3.h>
#include <nan.h>
#include "close.h"
#include "../objects/statement/statement.h"
#include "../util/macros.h"

CloseWorker::CloseWorker(Database* db, bool still_connecting) : Nan::AsyncWorker(NULL),
	db(db),
	still_connecting(still_connecting) {}
void CloseWorker::Execute() {
	if (!still_connecting) {
		// Close and free any associated statements.
		db->stmts.Flush([] (Statement* stmt) {
			delete stmt->handles;
			stmt->handles = NULL;
		});
		
		int status1 = sqlite3_close(db->writeHandle);
		int status2 = sqlite3_close(db->readHandle);
		db->writeHandle = NULL;
		db->readHandle = NULL;
		
		if (status1 != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db->writeHandle));
		} else if (status2 != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db->readHandle));
		}
	}
}
void CloseWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
	EMIT_EVENT_ASYNC(database, 2, {
		Nan::New("close").ToLocalChecked(),
		Nan::Null()
	});
}
void CloseWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
    CONCAT2(message, "SQLite: ", ErrorMessage());
	EMIT_EVENT_ASYNC(database, 2, {
		Nan::New("close").ToLocalChecked(),
		Nan::Error(message)
	});
}
