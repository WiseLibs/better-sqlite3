// .pragma(string sql, [boolean simpleResult]) -> array

Data::Row* PragmaMakeRowOfStrings(char** strings, int len) {
	Data::Row* row = new Data::Row();
	row->column_count = len;
	row->values = new Data::Value* [len];
	for (int i=0; i<len; ++i) {
		row->values[i] = new Data::Text(Nan::New(strings[i]).ToLocalChecked());
	}
	return row;
}

int PragmaCallback(void* x, int column_count, char** results, char** column_names) {
	List<Data::Row>* table = (List<Data::Row>*)x;
	table[0].Add(PragmaMakeRowOfStrings(column_names, column_count));
	table[1].Add(PragmaMakeRowOfStrings(results, column_count));
	return 0;
}

NAN_METHOD(Database::Pragma) {
	REQUIRE_ARGUMENT_STRING(0, source);
	TRUTHINESS_OF_ARGUMENT(1, simple_result);
	TRIM_STRING(source);
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	// Prepares the SQL string.
	v8::Local<v8::String> sql = v8::String::Concat(Nan::New("PRAGMA ").ToLocalChecked(), source);
	Nan::Utf8String utf8(sql);
	char* err;
	
	// Executes the SQL on the read handle.
	sqlite3_exec(db->read_handle, *utf8, NULL, NULL, &err);
	if (err != NULL) {
		Nan::ThrowError(err);
		sqlite3_free(err);
		return;
	}
	sqlite3_free(err);
	
	// Executes the SQL on the write handle.
	List<Data::Row> table[2] {};
	sqlite3_exec(db->write_handle, *utf8, PragmaCallback, table, &err);
	if (err != NULL) {
		Nan::ThrowError(err);
		sqlite3_free(err);
		return;
	}
	sqlite3_free(err);
	
	if (simple_result) {
		Data::Row* values = table[1].Shift();
		info.GetReturnValue().Set(values->values[0]->ToJS());
		delete values;
	} else {
		unsigned int i = 0;
		v8::Local<v8::Array> arr = Nan::New<v8::Array>();
		table[0].Flush([&arr, &i, &table] (Data::Row* keys) {
			Data::Row* values = table[1].Shift();
			v8::Local<v8::Object> object = Nan::New<v8::Object>();
			for (int j=0; j<keys->column_count; ++j) {
				Nan::Set(object, v8::Local<v8::String>::Cast(keys->values[j]->ToJS()), values->values[j]->ToJS());
			}
			Nan::Set(arr, i++, object);
			delete values;
		});
		info.GetReturnValue().Set(arr);
	}
}
