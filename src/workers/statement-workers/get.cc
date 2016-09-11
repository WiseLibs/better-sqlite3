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
	if (sqlite3_step(obj->st_handle) == SQLITE_ROW) {
		row.Fill(obj->st_handle, obj->column_count);
	}
	int status = sqlite3_reset(obj->st_handle);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errstr(status));
	}
}
void GetWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	// No error, but no result found.
	if (!row.column_count) {
		return Resolve(Nan::Undefined());
	}
	
	// Resolve with the plucked column.
	if (obj->state & PLUCK_COLUMN) {
		return Resolve(row.values[0]->ToJS());
	}
	
	// Resolve with every column.
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	for (int i=0; i<row.column_count; ++i) {
		Nan::Set(object, NEW_INTERNAL_STRING16(sqlite3_column_name16(obj->st_handle, i)), row.values[i]->ToJS());
	}
	
	Resolve(object);
}
