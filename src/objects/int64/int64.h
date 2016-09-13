#ifndef BETTER_SQLITE3_INT64_H
#define BETTER_SQLITE3_INT64_H

#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../../util/macros.h"

class Int64 : public Nan::ObjectWrap {
	public:
		Int64(uint32_t, uint32_t);
		Int64(sqlite3_int64);
		static void Init(v8::Local<v8::Object>, v8::Local<v8::Object>);
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_METHOD(ToString);
		static NAN_METHOD(ValueOf);
		static NAN_GETTER(High);
		static NAN_GETTER(Low);
		inline sqlite3_int64 GetValue() {
			return full;
		}
		
		uint32_t low;
		uint32_t high;
		sqlite3_int64 full;
};

#endif