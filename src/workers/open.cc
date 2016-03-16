#include <sqlite3.h>
#include <nan.h>
#include "../macros.h"
#include "open.h"

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
	
	status = sqlite3_open_v2(filename, &db->writeHandle, WRITE_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->writeHandle));
		sqlite3_close(db->writeHandle);
		db->writeHandle = NULL;
		return;
	}
	
	status = sqlite3_open_v2(filename, &db->readHandle, READ_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->readHandle));
		sqlite3_close(db->writeHandle);
		sqlite3_close(db->readHandle);
		db->writeHandle = NULL;
		db->readHandle = NULL;
		return;
	}
	
	sqlite3_busy_timeout(db->writeHandle, 30000);
	sqlite3_busy_timeout(db->readHandle, 30000);
}
void OpenWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
	if (db->state == DB_DONE) {
		sqlite3_close(db->writeHandle);
		sqlite3_close(db->readHandle);
		db->writeHandle = NULL;
		db->readHandle = NULL;
	} else {
		db->state = DB_READY;
		EMIT_EVENT(database, 1, {Nan::New("open").ToLocalChecked()});
	}
}
void OpenWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
	if (db->state != DB_DONE) {
		db->state = DB_DONE;
		CONCAT2(message, "SQLite: ", ErrorMessage());
		EMIT_EVENT(database, 2, {
			Nan::New("close").ToLocalChecked(),
			Nan::Error(message)
		});
	}
}
