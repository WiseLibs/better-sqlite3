#ifndef BETTER_SQLITE3_QUERY_H
#define BETTER_SQLITE3_QUERY_H

#include <nan.h>

class Query { public:
	virtual v8::Local<v8::Object> GetBindMap() {
		return Nan::New<v8::Object>();
	}
};

#endif