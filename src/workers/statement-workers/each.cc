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
	handle_mutex(NULL),
	cached_names(false),
	progressCallback(progressCb) {}
EachWorker::~EachWorker() {
	sqlite3_mutex_free(data_mutex);
	sqlite3_mutex_free(handle_mutex);
	delete progressCallback;
}
void EachWorker::Execute(const Nan::AsyncProgressWorker::ExecutionProgress &progress) {
	// Allocate mutexes.
	data_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (data_mutex == NULL) {
		return SetErrorMessage("Out of memory.");
	}
	handle_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (handle_mutex == NULL) {
		return SetErrorMessage("Out of memory.");
	}
	
	LOCK_DB(obj->db_handle);
	
	// Retreive first row, and validated statement result columns.
	int status = sqlite3_step(obj->st_handle);
	GET_COLUMN_COUNT(column_count);
	
	// Retrieve and save rows.
	while (status == SQLITE_ROW) {
		sqlite3_mutex_enter(data_mutex);
		rows.Add(new Data::Row(obj->st_handle, column_count));
		sqlite3_mutex_leave(data_mutex);
		
		progress.Signal();
		
		sqlite3_mutex_enter(handle_mutex);
		status = sqlite3_step(obj->st_handle);
		sqlite3_mutex_leave(handle_mutex);
	}
	
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(obj->db_handle));
	}
	
	sqlite3_reset(obj->st_handle);
	UNLOCK_DB(obj->db_handle);
}
void EachWorker::HandleProgressCallback(const char* not_used1, size_t not_used2) {
	Nan::HandleScope scope;
	
	if (obj->pluck_column) {
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
		
		// Cache columns names, or get the already cached column names.
		v8::Local<v8::Array> columnNames;
		if (cached_names) {
			columnNames = v8::Local<v8::Array>::Cast(GetFromPersistent((uint32_t)0));
		} else {
			columnNames = Nan::New<v8::Array>(column_count);
			
			sqlite3_mutex_enter(handle_mutex);
			for (int i=0; i<column_count; ++i) {
				Nan::Set(columnNames, i, Nan::New(sqlite3_column_name(obj->st_handle, i)).ToLocalChecked());
			}
			sqlite3_mutex_leave(handle_mutex);
			
			SaveToPersistent((uint32_t)0, columnNames);
			cached_names = true;
		}
		
		// Flush rows.
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this, &columnNames] (Data::Row* row) {
			
			v8::Local<v8::Object> object = Nan::New<v8::Object>();
			for (int i=0; i<row->column_count; ++i) {
				Nan::ForceSet(object, Nan::Get(columnNames, i).ToLocalChecked(), row->values[i]->ToJS());
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
