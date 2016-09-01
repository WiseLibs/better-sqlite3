#ifndef NODE_SQLITE3_PLUS_DATA_H
#define NODE_SQLITE3_PLUS_DATA_H

#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "strlcpy.h"

namespace Data {

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
	Integer(v8::Local<v8::Number> n) : value((sqlite3_int64)n->Value()) {}
	v8::Local<v8::Value> ToJS() {return Nan::New<v8::Number>((double)value);}
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
	Text(const unsigned char* str, int len) : length(len) {
		value = new char[length + 1];
		strlcpy(value, (const char*)str, length + 1);
	}
	Text(v8::Local<v8::String> str) {
		Nan::Utf8String utf8(str);
		length = utf8.length();
		value = new char[length + 1];
		strlcpy(value, *utf8, length + 1);
	}
	~Text() {delete[] value;}
	v8::Local<v8::Value> ToJS() {return Nan::New<v8::String>(value, length).ToLocalChecked();}
	char* value; // Is NUL-terminated.
	int length; // Does not include the NUL terminator.
};

// An SQLite3 blob value.
// The given constructor argument (const void*) is a pointer to the raw bytes to
// include. The len argument is the number of bytes. Invoking ToJS() multiple
// times returns Buffers that all point to the same underlying memory.
class Blob : public Data::Value { public:
	Blob(const void* data, int len) : length(len), transferred(false) {
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
						values[i] = new Data::Text(sqlite3_column_text(handle, i), sqlite3_column_bytes(handle, i));
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