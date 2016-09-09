#include <sqlite3.h>
#include <nan.h>
#include "open.h"
#include "../../objects/database/database.h"
#include "../../util/macros.h"
#include "../../util/transaction-handles.h"

const int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_SHAREDCACHE;
const int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_SHAREDCACHE;

OpenWorker::OpenWorker(Database* db, char* filename) : Nan::AsyncWorker(NULL),
	db(db),
	filename(filename) {}
OpenWorker::~OpenWorker() {
	delete[] filename;
}
void OpenWorker::Execute() {
	int status;
	
	status = sqlite3_open_v2(filename, &db->write_handle, WRITE_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->write_handle));
		db->CloseHandles();
		return;
	}
	
	status = sqlite3_open_v2(filename, &db->read_handle, READ_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->read_handle));
		db->CloseHandles();
		return;
	}
	
	sqlite3_busy_timeout(db->write_handle, 5000);
	sqlite3_busy_timeout(db->read_handle, 5000);
	
	db->t_handles = new TransactionHandles(db->write_handle, &status);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->write_handle));
		db->CloseHandles();
		return;
	}
}
void OpenWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
	if (db->state == DB_DONE) {
		db->CloseHandles();
	} else {
		db->state = DB_READY;
		v8::Local<v8::Value> args[1] = {NEW_INTERNAL_STRING_FAST("open")};
		EMIT_EVENT(database, 1, args);
	}
}
void OpenWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
	if (db->state != DB_DONE) {
		db->state = DB_DONE;
		
		CONCAT2(message, "SQLite: ", ErrorMessage());
		v8::Local<v8::Value> args[2] = {
			NEW_INTERNAL_STRING_FAST("close"),
			Nan::Error(message)
		};
		
		EMIT_EVENT(database, 2, args);
	}
}
