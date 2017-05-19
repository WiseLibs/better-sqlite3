// .pragma(string sql, [boolean simpleResult]) -> array

typedef struct PragmaInfo {
	v8::Local<v8::Value> rows;
	v8::Isolate* isolate;
	bool simple;
	bool after_first;
} PragmaInfo;

int PragmaCallback(void* x, int column_count, char** results, char** column_names) {
	PragmaInfo* pragma_info = static_cast<PragmaInfo*>(x);
	v8::Isolate* isolate = pragma_info->isolate;
	
	if (pragma_info->simple) {
		if (!pragma_info->after_first) {
			pragma_info->after_first = true;
			pragma_info->rows = StringFromUtf8(isolate, results[0], -1);
		}
	} else {
		v8::Local<v8::Object> row = Nan::New<v8::Object>();
		for (int i=0; i<column_count; ++i) {
			Nan::Set(row, StringFromUtf8(isolate, column_names[i], -1), StringFromUtf8(isolate, results[i], -1));
		}
		v8::Local<v8::Array> rows = v8::Local<v8::Array>::Cast(pragma_info->rows);
		Nan::Set(rows, rows->Length(), row);
	}
	
	return 0;
}

NAN_METHOD(Database::Pragma) {
	GET_ISOLATE();
	REQUIRE_ARGUMENT_STRING(0, source);
	TRUTHINESS_OF_ARGUMENT(1, simple_result);
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (!db->open) {
		return Nan::ThrowTypeError("The database connection is not open");
	}
	if (db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query");
	}
	
	// Prepares the SQL string.
	v8::Local<v8::String> sql = v8::String::Concat(StringFromLatin1(isolate, "PRAGMA ", -1), source);
	v8::String::Utf8Value utf8(sql);
	char* err;
	
	// Executes the SQL on the database handle.
	PragmaInfo pragma_info = {Nan::New<v8::Array>(), isolate, simple_result, false};
	sqlite3_exec(db->db_handle, *utf8, PragmaCallback, &pragma_info, &err);
	if (err != NULL) {
		db->ThrowDatabaseError(err);
		return sqlite3_free(err);
	}
	
	if (simple_result && !pragma_info.after_first) {
		info.GetReturnValue().Set(Nan::Undefined());
	} else {
		info.GetReturnValue().Set(pragma_info.rows);
	}
}
