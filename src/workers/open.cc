#include <sqlite3.h>
#include <nan.h>
#include "open.h"
#include "../objects/database/database.h"
#include "../util/macros.h"

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
		sqlite3_close(db->write_handle);
		db->write_handle = NULL;
		return;
	}
	
	status = sqlite3_open_v2(filename, &db->read_handle, READ_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->read_handle));
		sqlite3_close(db->write_handle);
		sqlite3_close(db->read_handle);
		db->write_handle = NULL;
		db->read_handle = NULL;
		return;
	}
	
	sqlite3_busy_timeout(db->write_handle, 30000);
	sqlite3_busy_timeout(db->read_handle, 30000);
}
void OpenWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    if (--db->workers == 0) {db->Unref();}
    
	if (db->state == DB_DONE) {
		sqlite3_close(db->write_handle);
		sqlite3_close(db->read_handle);
		db->write_handle = NULL;
		db->read_handle = NULL;
	} else {
		db->state = DB_READY;
		v8::Local<v8::Value> args[1] = {Nan::New("open").ToLocalChecked()};
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
			Nan::New("close").ToLocalChecked(),
			Nan::Error(message)
		};
		
		EMIT_EVENT(database, 2, args);
	}
}
