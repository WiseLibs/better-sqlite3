#include <sqlite3.h>
#include <nan.h>
#include "run.h"
#include "../query-worker.h"
#include "../../objects/statement/statement.h"
#include "../../util/macros.h"

RunWorker::RunWorker(Statement* stmt, Nan::Callback* cb)
	: QueryWorker<Statement, Nan::AsyncWorker>(stmt, cb) {}
void RunWorker::Execute() {
	sqlite3* db_handle = obj->db->write_handle;
	LOCK_DB(db_handle);
	
	sqlite3_step(obj->st_handle);
	int status = sqlite3_reset(obj->st_handle);
	if (status != SQLITE_OK) {
		UNLOCK_DB(db_handle);
		SetErrorMessage(sqlite3_errstr(status));
		return;
	}
	
	changes = sqlite3_changes(db_handle);
	id = sqlite3_last_insert_rowid(db_handle);
	UNLOCK_DB(db_handle);
}
void RunWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	Nan::ForceSet(object, NEW_INTERNAL_STRING_FAST("changes"), Nan::New<v8::Number>((double)changes));
	Nan::ForceSet(object, NEW_INTERNAL_STRING_FAST("id"), Nan::New<v8::Number>((double)id));
	
	Resolve(object);
}
