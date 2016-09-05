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
	LOCK_DB(obj->db_handle);
	int status = sqlite3_step(obj->st_handle);
	
	GET_COLUMN_COUNT(column_count);
	
	while (status == SQLITE_ROW) {
		++row_count;
		rows.Add(new Data::Row(obj->st_handle, column_count));
		status = sqlite3_step(obj->st_handle);
	}
	
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(obj->db_handle));
	}
	
	sqlite3_reset(obj->st_handle);
	UNLOCK_DB(obj->db_handle);
}
void AllWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(row_count);
	
	if (row_count > 0) {
		unsigned int i = 0;
		
		if (obj->pluck_column) {
			// Fill array with plucked columns.
			rows.Flush([&arr, &i] (Data::Row* row) {
				Nan::Set(arr, i++, row->values[0]->ToJS());
			});
		} else {
			
			// Temporarily Cache column names.
			v8::Local<v8::Array> columnNames = Nan::New<v8::Array>(column_count);
			for (int j=0; j<column_count; ++j) {
				Nan::Set(columnNames, j, Nan::New(sqlite3_column_name(obj->st_handle, j)).ToLocalChecked());
			}
			
			// Fill array with row objects.
			rows.Flush([&arr, &i, &columnNames] (Data::Row* row) {
				v8::Local<v8::Object> object = Nan::New<v8::Object>();
				for (int j=0; j<row->column_count; ++j) {
					Nan::ForceSet(object, Nan::Get(columnNames, j).ToLocalChecked(), row->values[j]->ToJS());
				}
				Nan::Set(arr, i++, object);
			});
		}
	}
	
	Resolve(arr);
}
