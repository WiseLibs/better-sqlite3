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
	while (sqlite3_step(obj->st_handle) == SQLITE_ROW) {
		++row_count;
		rows.Add(new Data::Row(obj->st_handle, obj->column_count));
	}
	int status = sqlite3_reset(obj->st_handle);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errstr(status));
	}
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
			
			// Get cached column names.
			v8::Local<v8::Array> columnNames = v8::Local<v8::Array>::Cast(obj->handle()->GetHiddenValue(NEW_INTERNAL_STRING_FAST("columnNames")));
			
			// Fill array with row objects.
			rows.Flush([&arr, &i, &columnNames] (Data::Row* row) {
				v8::Local<v8::Object> object = Nan::New<v8::Object>();
				for (int j=0; j<row->column_count; ++j) {
					Nan::Set(object, Nan::Get(columnNames, j).ToLocalChecked(), row->values[j]->ToJS());
				}
				Nan::Set(arr, i++, object);
			});
		}
	}
	
	Resolve(arr);
}
