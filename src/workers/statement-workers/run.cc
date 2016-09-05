#include <sqlite3.h>
#include <nan.h>
#include "run.h"
#include "../query-worker.h"
#include "../../objects/statement/statement.h"
#include "../../util/macros.h"

RunWorker::RunWorker(Statement* stmt, Nan::Callback* cb)
	: QueryWorker<Statement, Nan::AsyncWorker>(stmt, cb) {}
void RunWorker::Execute() {
	LOCK_DB(obj->db_handle);
	int status = sqlite3_step(obj->st_handle);
	if (status == SQLITE_DONE) {
		changes = sqlite3_changes(obj->db_handle);
		id = sqlite3_last_insert_rowid(obj->db_handle);
	} else if (status != SQLITE_ROW) {
		SetErrorMessage(sqlite3_errmsg(obj->db_handle));
	} else {
		SetErrorMessage("Unexpected data returned by a write transaction.");
	}
	sqlite3_reset(obj->st_handle);
	UNLOCK_DB(obj->db_handle);
}
void RunWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	Nan::ForceSet(object, Nan::New("changes").ToLocalChecked(), Nan::New<v8::Number>((double)changes));
	Nan::ForceSet(object, Nan::New("id").ToLocalChecked(), Nan::New<v8::Number>((double)id));
	
	Resolve(object);
}
