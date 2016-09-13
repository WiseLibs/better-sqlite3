#ifndef BETTER_SQLITE3_DATA_H
#define BETTER_SQLITE3_DATA_H

#include <sys/types.h>
#include <stdint.h>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "../objects/int64/int64.h"

namespace Data {

class SimpleExternalString : public v8::String::ExternalStringResource {
	public:
		SimpleExternalString(const uint16_t* _data, size_t _length)
		: v8::String::ExternalStringResource()
		, _data(_data)
		, _length(_length) {}
		~SimpleExternalString() {
			delete[] _data;
		}
		const uint16_t* data() const {return _data;}
		size_t length() const {return _length;}
	private:
		const uint16_t* _data;
		size_t _length; // Number of uint16_t (not number of bytes)
};

// A generic class representing an SQLite3 value.
// When a Value is created, all memory is copied, and managed internally.
// Therefore, you must still manage the memory of the originally passed value.
class Value { public:
	Value() {}
	virtual ~Value() {}
	virtual v8::Local<v8::Value> ToJS() {return Nan::Undefined();}
};

// An SQLite3 integer value.
class Integer : public Data::Value { public:
	Integer(sqlite3_int64 n) : value(n) {}
	Integer(v8::Local<v8::Object> n) : value(Nan::ObjectWrap::Unwrap<Int64>(n)->GetValue()) {}
	v8::Local<v8::Value> ToJS() {return Int64::NewProperInteger(value);}
	sqlite3_int64 value;
};

// An SQLite3 real/float value.
class Float : public Data::Value { public:
	Float(double n) : value(n) {}
	Float(v8::Local<v8::Number> n) : value(n->Value()) {}
	v8::Local<v8::Value> ToJS() {return Nan::New<v8::Number>(value);}
	double value;
};

// An SQLite3 text value.
// The given constructor argument (const unsigned char*) should be a
// NUL-terminated string, and len should be the number of bytes in the string,
// not including the NUL terminator.
class Text : public Data::Value { public:
	Text(const void* str, int byte_count) : length((size_t)(byte_count / sizeof (uint16_t))), transferred(false) {
		value = new uint16_t[length];
		memcpy(value, str, byte_count);
	}
	Text(v8::Local<v8::String> str) {
		v8::String::Value utf16(str);
		length = (size_t)utf16.length();
		value = new uint16_t[length];
		memcpy(value, *utf16, length * sizeof (uint16_t));
	}
	~Text() {if (!transferred) {delete[] value;}}
	v8::Local<v8::Value> ToJS() {
		transferred = true;
		return v8::String::NewExternalTwoByte(v8::Isolate::GetCurrent(), new SimpleExternalString(value, length)).ToLocalChecked();
	}
	uint16_t* value;
	size_t length; // Number of uint16_t (not number of bytes)
	
private:
	bool transferred;
};

// An SQLite3 blob value.
// The given constructor argument (const void*) is a pointer to the raw bytes to
// include. The len argument is the number of bytes. Invoking ToJS() multiple
// times returns Buffers that all point to the same underlying memory.
class Blob : public Data::Value { public:
	Blob(const void* data, int byte_count) : length(byte_count), transferred(false) {
		value = new char[length];
		memcpy(value, data, length);
	}
	Blob(v8::Local<v8::Object> buffer) : transferred(false) {
		length = node::Buffer::Length(buffer);
		value = new char[length];
		memcpy(value, node::Buffer::Data(buffer), length);
	}
	~Blob() {if (!transferred) {delete[] value;}}
	v8::Local<v8::Value> ToJS() {
		transferred = true;
		return Nan::NewBuffer(value, length).ToLocalChecked();
	}
	char* value;
	int length;
	
private:
	bool transferred;
};

// An SQLite3 null value.
class Null : public Data::Value { public:
	Null() {}
	v8::Local<v8::Value> ToJS() {return Nan::Null();}
};

// A list of SQLite3 values.
// Values that are added to a row are automatically destroyed when the row is
// destroyed. You should NOT manually destroy values that you add to a row.
// Values should only be added by the constructor or by Fill(). It is an error
// to invoke Fill() on a row more than once. The integer passed to Fill() or the
// constructor must never be less than 1.
class Row {
	public:
		Row() : column_count(0), values(NULL) {}
		Row(sqlite3_stmt* handle, int len) {
			this->Fill(handle, len);
		}
		~Row() {
			if (values) {
				for (int i=0; i<column_count; ++i) {delete values[i];}
				delete[] values;
			}
		}
		
		// Given an sqlite3_stmt handle and the number of columns in the
		// available result row, fills the row with the values given by the
		// sqlite3_stmt.
		// The number of columns must never be less than 1.
		// This must only be used on a row with no values in it.
		inline void Fill(sqlite3_stmt* handle, int len) {
			column_count = len;
			values = new Data::Value* [len];
			for (int i=0; i<len; ++i) {
				int type = sqlite3_column_type(handle, i);
				switch (type) {
					case SQLITE_INTEGER:
						values[i] = new Data::Integer(sqlite3_column_int64(handle, i));
						break;
					case SQLITE_FLOAT:
						values[i] = new Data::Float(sqlite3_column_double(handle, i));
						break;
					case SQLITE_TEXT:
						values[i] = new Data::Text(sqlite3_column_text16(handle, i), sqlite3_column_bytes16(handle, i));
						break;
					case SQLITE_BLOB:
						values[i] = new Data::Blob(sqlite3_column_blob(handle, i), sqlite3_column_bytes(handle, i));
						break;
					default: // SQLITE_NULL
						values[i] = new Data::Null();
				}
			}
		}
		
		int column_count;
		Data::Value** values;
};

}

#endif