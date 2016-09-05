#include <sqlite3.h>
#include <nan.h>
#include "get.h"
#include "../query-worker.h"
#include "../../objects/statement/statement.h"
#include "../../util/macros.h"
#include "../../util/data.h"

GetWorker::GetWorker(Statement* stmt, Nan::Callback* cb)
	: QueryWorker<Statement, Nan::AsyncWorker>(stmt, cb) {}
void GetWorker::Execute() {
	LOCK_DB(obj->db_handle);
	int status = sqlite3_step(obj->st_handle);
	int column_count;
	
	GET_COLUMN_COUNT(column_count);
	
	if (status == SQLITE_ROW) {
		row.Fill(obj->st_handle, column_count);
	} else if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(obj->db_handle));
	}
	
	sqlite3_reset(obj->st_handle);
	UNLOCK_DB(obj->db_handle);
}
void GetWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	// No error, but no result found.
	if (!row.column_count) {
		return Resolve(Nan::Undefined());
	}
	
	// Resolve with the plucked column.
	if (obj->pluck_column) {
		return Resolve(row.values[0]->ToJS());
	}
	
	// Resolve with every column.
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	for (int i=0; i<row.column_count; ++i) {
		Nan::ForceSet(object,
			Nan::New(sqlite3_column_name(obj->st_handle, i)).ToLocalChecked(),
			row.values[i]->ToJS());
	}
	
	Resolve(object);
}
