#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../objects/int64/int64.h"
#include "../util/macros.h"

namespace Data {

v8::Local<v8::Value> GetIntegerJS(sqlite3_stmt* handle, int column) {
	return Int64::NewProperInteger(sqlite3_column_int64(handle, column));
}
v8::Local<v8::Value> GetFloatJS(sqlite3_stmt* handle, int column) {
	return Nan::New<v8::Number>(sqlite3_column_double(handle, column));
}
v8::Local<v8::Value> GetTextJS(sqlite3_stmt* handle, int column) {
	const unsigned char* value = sqlite3_column_text(handle, column);
	int byte_count = sqlite3_column_bytes(handle, column);
	return v8::String::NewFromUtf8(
		v8::Isolate::GetCurrent(),
		reinterpret_cast<const char*>(value),
		v8::NewStringType::kNormal,
		byte_count
	).ToLocalChecked();
}
v8::Local<v8::Value> GetBlobJS(sqlite3_stmt* handle, int column) {
	const void* value = sqlite3_column_blob(handle, column);
	int byte_count = sqlite3_column_bytes(handle, column);
	return Nan::CopyBuffer(
		static_cast<const char*>(value),
		byte_count
	).ToLocalChecked();
}

v8::Local<v8::Value> GetValueJS(sqlite3_stmt* handle, int column) {
	int type = sqlite3_column_type(handle, column);
	switch (type) {
		case SQLITE_INTEGER:
			return Data::GetIntegerJS(handle, column);
		case SQLITE_FLOAT:
			return Data::GetFloatJS(handle, column);
		case SQLITE_TEXT:
			return Data::GetTextJS(handle, column);
		case SQLITE_BLOB:
			return Data::GetBlobJS(handle, column);
		default: // SQLITE_NULL
			return Nan::Null();
	}
}

v8::Local<v8::Value> GetRowJS(sqlite3_stmt* handle, int column_count) {
	v8::Local<v8::Object> row = Nan::New<v8::Object>();
	for (int i=0; i<column_count; ++i) {
		Nan::Set(row, NEW_INTERNAL_STRING8(sqlite3_column_name(handle, i)), Data::GetValueJS(handle, i));
	}
	return row;
}

}
