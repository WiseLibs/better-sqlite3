#ifndef BETTER_SQLITE3_INT64_H
#define BETTER_SQLITE3_INT64_H

#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../../util/macros.h"

class Int64 : public Nan::ObjectWrap {
	public:
		explicit Int64(int32_t, int32_t);
		explicit Int64(sqlite3_int64);
		static void Init(v8::Local<v8::Object>, v8::Local<v8::Object>);
		static Nan::Persistent<v8::FunctionTemplate> constructorTemplate;
		
		inline sqlite3_int64 GetValue() {
			return full;
		}
		
		// Either returns a v8::Number or an Int64 object, given an sqlite3_int64.
		static inline v8::Local<v8::Value> NewProperInteger(sqlite3_int64 value, bool safe_integers) {
			if (safe_integers) {
				FastConstructInt = &value;
				return Nan::NewInstance(Nan::New<v8::Function>(constructor)).ToLocalChecked();
			}
			return Nan::New<v8::Number>(static_cast<double>(value));
		}
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_METHOD(ToString);
		static NAN_METHOD(ValueOf);
		static NAN_GETTER(High);
		static NAN_GETTER(Low);
		static sqlite3_int64* FastConstructInt;
		
		int32_t low;
		int32_t high;
		sqlite3_int64 full;
};

#endif