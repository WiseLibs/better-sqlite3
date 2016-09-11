#include <sys/types.h>
#include <sqlite3.h>
#include <nan.h>
#include "each.h"
#include "../query-worker.h"
#include "../../objects/statement/statement.h"
#include "../../util/macros.h"
#include "../../util/data.h"
#include "../../util/list.h"

EachWorker::EachWorker(Statement* stmt, Nan::Callback* cb, Nan::Callback* progressCb)
	: QueryWorker<Statement, Nan::AsyncProgressWorker>(stmt, cb),
	data_mutex(NULL),
	progressCallback(progressCb) {}
EachWorker::~EachWorker() {
	sqlite3_mutex_free(data_mutex);
	delete progressCallback;
}
void EachWorker::Execute(const Nan::AsyncProgressWorker::ExecutionProgress &progress) {
	// Allocate mutex.
	data_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (data_mutex == NULL) {
		return SetErrorMessage("Out of memory.");
	}
	// Retrieve and feed rows.
	while (sqlite3_step(obj->st_handle) == SQLITE_ROW) {
		sqlite3_mutex_enter(data_mutex);
		rows.Add(new Data::Row(obj->st_handle, obj->column_count));
		sqlite3_mutex_leave(data_mutex);
		progress.Signal();
	}
	int status = sqlite3_reset(obj->st_handle);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errstr(status));
	}
}
void EachWorker::HandleProgressCallback(const char* not_used1, size_t not_used2) {
	Nan::HandleScope scope;
	
	if (obj->state & PLUCK_COLUMN) {
		// Flush rows of plucked columns.
		
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this] (Data::Row* row) {
			v8::Local<v8::Value> args[1] = {row->values[0]->ToJS()};
			
			sqlite3_mutex_leave(data_mutex);
			progressCallback->Call(1, args);
			sqlite3_mutex_enter(data_mutex);
			
		});
		sqlite3_mutex_leave(data_mutex);
		
	} else {
		// Flush rows.
		
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this] (Data::Row* row) {
			
			v8::Local<v8::Object> object = Nan::New<v8::Object>();
			for (int i=0; i<row->column_count; ++i) {
				Nan::Set(object, NEW_INTERNAL_STRING16(sqlite3_column_name16(obj->st_handle, i)), row->values[i]->ToJS());
			}
			
			sqlite3_mutex_leave(data_mutex);
			v8::Local<v8::Value> args[1] = {object};
			progressCallback->Call(1, args);
			sqlite3_mutex_enter(data_mutex);
			
		});
		sqlite3_mutex_leave(data_mutex);
	}
}
void EachWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	HandleProgressCallback(NULL, 0);
	Resolve(Nan::Undefined());
}
