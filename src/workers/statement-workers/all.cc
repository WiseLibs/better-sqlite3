#include <sqlite3.h>
#include <nan.h>
#include "all.h"
#include "../query-worker.h"
#include "../../objects/statement/statement.h"
#include "../../util/macros.h"
#include "../../util/data.h"
#include "../../util/list.h"

AllWorker::AllWorker(Statement* stmt, Nan::Callback* cb)
	: QueryWorker<Statement, Nan::AsyncWorker>(stmt, cb),
	row_count(0) {}
void AllWorker::Execute() {
	sqlite3* db_handle = obj->db->read_handle;
	LOCK_DB(db_handle);
	
	while (sqlite3_step(obj->st_handle) == SQLITE_ROW) {
		++row_count;
		rows.Add(new Data::Row(obj->st_handle, obj->column_count));
	}
	if (sqlite3_reset(obj->st_handle) != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	
	UNLOCK_DB(db_handle);
}
void AllWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(row_count);
	
	if (row_count > 0) {
		unsigned int i = 0;
		
		if (obj->state & PLUCK_COLUMN) {
			// Fill array with plucked columns.
			rows.Flush([&arr, &i] (Data::Row* row) {
				Nan::Set(arr, i++, row->values[0]->ToJS());
			});
		} else {
			// Fill array with row objects.
			rows.Flush([this, &arr, &i] (Data::Row* row) {
				v8::Local<v8::Object> object = Nan::New<v8::Object>();
				for (int j=0; j<row->column_count; ++j) {
					Nan::Set(object, NEW_INTERNAL_STRING16(sqlite3_column_name16(obj->st_handle, j)), row->values[j]->ToJS());
				}
				Nan::Set(arr, i++, object);
			});
		}
	}
	
	Resolve(arr);
}
