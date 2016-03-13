#ifndef NODE_SQLITE3_PLUS_DATA_H
#define NODE_SQLITE3_PLUS_DATA_H
#include <sqlite3.h>
#include <nan.h>

namespace Data {

class Value { public:
	Value() {}
	virtual ~Value() {}
	virtual v8::Local<v8::Value> ToJS() {return Nan::Undefined();}
};

class Row {
	public:
		Row() {
			init = false;
			column_count = 0;
		}
		~Row() {
			if (init) {
				for (int i=0; i<column_count; i++) {delete values[i];}
				delete[] values;
			}
		}
		inline void Init(int max_columns) {
			init = true;
			values = max_columns > 0 ? new Value* [max_columns] : NULL;
		}
		inline void Add(Value* value) {
			values[column_count++] = value;
		}
		int column_count;
		Value** values;
	private:
		bool init;
};

class Integer : public Value { public:
	Integer(sqlite3_int64 n) : value(n) {}
	Integer(v8::Local<v8::Number> n) : value((sqlite3_int64)n->Value()) {}
	v8::Local<v8::Value> ToJS() {return Nan::New<v8::Number>((double)value);}
	sqlite3_int64 value;
};

class Float : public Value { public:
	Float(double n) : value(n) {}
	Float(v8::Local<v8::Number> n) : value(n->Value()) {}
	v8::Local<v8::Value> ToJS() {return Nan::New<v8::Number>(value);}
	double value;
};

class Text : public Value { public:
	Text(const unsigned char* str, int len) {
		length = len;
		value = (char*) malloc(len + 1);
		strncpy(value, (const char*)str, len + 1);
	}
	Text(v8::Local<v8::String> str) {
		Nan::Utf8String utf8(str);
		length = utf8.length();
		value = (char*) malloc(length + 1);
		strncpy(value, *utf8, length + 1);
	}
	~Text() {free(value);}
	v8::Local<v8::Value> ToJS() {return Nan::New<v8::String>(value, length).ToLocalChecked();}
	char* value;
	int length;
};

class Blob : public Value { public:
	Blob(const void* data, int len) {
		transferred = false;
		length = len;
		value = malloc(len);
		memcpy(value, data, len);
	}
	Blob(v8::Local<v8::Object> buffer) {
		transferred = false;
		length = node::Buffer::Length(buffer);
		value = malloc(length);
		memcpy(value, node::Buffer::Data(buffer), length);
	}
	~Blob() {if (!transferred) {free(value);}}
	v8::Local<v8::Value> ToJS() {
		transferred = true;
		return Nan::NewBuffer((char*)value, length).ToLocalChecked();
	}
	void* value;
	int length;
	bool transferred;
};

class Null : public Value { public:
	Null() {}
	v8::Local<v8::Value> ToJS() {return Nan::Null();}
};

}
#endif