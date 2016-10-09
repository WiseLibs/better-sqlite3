#include <sqlite3.h>
#include <nan.h>
#include "close.h"
#include "../objects/database/database.h"

CloseWorker::CloseWorker(Database* db) : Nan::AsyncWorker(NULL),
	db(db) {}
void CloseWorker::Execute() {
	db->CloseChildHandles();
	if (db->CloseHandles() != SQLITE_OK) {
		SetErrorMessage("Failed to successfully close the database connection.");
	}
}
void CloseWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	db->Unref();
	
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(GetFromPersistent((uint32_t)0));
	resolver->Resolve(Nan::Undefined());
}
void CloseWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
	db->Unref();
	
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(GetFromPersistent((uint32_t)0));
	resolver->Reject(Nan::Error(ErrorMessage()));
}
