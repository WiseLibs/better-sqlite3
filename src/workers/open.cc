#include <sqlite3.h>
#include <nan.h>
#include "open.h"
#include "../objects/database/database.h"
#include "../util/macros.h"

OpenWorker::OpenWorker(Database* db, char* filename) : Nan::AsyncWorker(NULL),
	db(db),
	filename(filename) {}
OpenWorker::~OpenWorker() {
	delete[] filename;
}
void OpenWorker::Execute() {
	if (db->OpenHandles(filename) != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->db_handle));
		db->CloseHandles();
	}
}
void OpenWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	db->Unref();
	
	db->state = DB_READY;
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(GetFromPersistent((uint32_t)0));
	resolver->Resolve(db->handle());
}
void OpenWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
	db->Unref();
	
	db->state = DB_DONE;
	CONCAT2(message, "SQLite: ", ErrorMessage());
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(GetFromPersistent((uint32_t)0));
	resolver->Reject(Nan::Error(message.c_str()));
}
