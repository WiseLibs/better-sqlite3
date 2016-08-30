#include <sys/types.h>
#include <sqlite3.h>
#include <nan.h>
#include "each.h"
#include "statement-worker.h"
#include "../objects/statement/statement.h"
#include "../util/macros.h"
#include "../util/data.h"
#include "../util/list.h"

EachWorker::EachWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index, Nan::Callback* cb)
	: StatementWorker<Nan::AsyncProgressWorker>(stmt, handle, handle_index),
	data_mutex(NULL), handle_mutex(NULL), cached_names(false) {
		callback = cb;
	}
EachWorker::~EachWorker() {
	sqlite3_mutex_free(data_mutex);
	sqlite3_mutex_free(handle_mutex);
}
void EachWorker::Execute(const Nan::AsyncProgressWorker::ExecutionProgress &progress) {
	// Allocated mutexes.
	data_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (data_mutex == NULL) {
		return SetErrorMessage("Out of memory.");
	}
	handle_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (handle_mutex == NULL) {
		return SetErrorMessage("Out of memory.");
	}
	
	LOCK_DB(db_handle);
	
	// Retreive first row, and validated statement result columns.
	int status = sqlite3_step(handle);
	GET_COLUMN_COUNT(column_count);
	
	// Retrieve and save rows.
	while (status == SQLITE_ROW) {
		sqlite3_mutex_enter(data_mutex);
		rows.Add(new Data::Row(handle, column_count));
		sqlite3_mutex_leave(data_mutex);
		
		progress.Signal();
		
		sqlite3_mutex_enter(handle_mutex);
		status = sqlite3_step(handle);
		sqlite3_mutex_leave(handle_mutex);
	}
	
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	
	UNLOCK_DB(db_handle);
}
void EachWorker::HandleProgressCallback(const char* not_used1, size_t not_used2) {
	Nan::HandleScope scope;
	
	if (GetPluckColumn()) {
		// Flush rows of plucked columns.
		
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this] (Data::Row* row) {
			v8::Local<v8::Value> args[1] = {row->values[0]->ToJS()};
			
			sqlite3_mutex_leave(data_mutex);
			callback->Call(1, args);
			sqlite3_mutex_enter(data_mutex);
			
		});
		sqlite3_mutex_leave(data_mutex);
		
	} else {
		
		// Cache columns names, or get the already cached column names.
		v8::Local<v8::Array> columnNames;
		if (cached_names) {
			columnNames = v8::Local<v8::Array>::Cast(GetFromPersistent((uint32_t)1));
		} else {
			columnNames = Nan::New<v8::Array>(column_count);
			
			sqlite3_mutex_enter(handle_mutex);
			for (int i=0; i<column_count; i++) {
				Nan::Set(columnNames, i, Nan::New(sqlite3_column_name(handle, i)).ToLocalChecked());
			}
			sqlite3_mutex_leave(handle_mutex);
			
			SaveToPersistent((uint32_t)1, columnNames);
			cached_names = true;
		}
		
		// Flush rows.
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this, &columnNames] (Data::Row* row) {
			
			v8::Local<v8::Object> obj = Nan::New<v8::Object>();
			for (int i=0; i<row->column_count; i++) {
				Nan::ForceSet(obj, Nan::Get(columnNames, i).ToLocalChecked(), row->values[i]->ToJS());
			}
			
			sqlite3_mutex_leave(data_mutex);
			v8::Local<v8::Value> args[1] = {obj};
			callback->Call(1, args);
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
