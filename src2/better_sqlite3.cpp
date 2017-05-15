// better_sqlite3.cpp
//

#include "better_sqlite3.hpp"
#line 11 "./src2/better_sqlite3.lzz"
void RegisterModule(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
	v8::HandleScope scope(v8::Isolate::GetCurrent());
	
	Int64::Init(exports);
}
NODE_MODULE(better_sqlite3, RegisterModule);
#define LZZ_INLINE inline
#line 14 "./src2/objects/int64/int64.lzz"
sqlite3_int64 const MAX_SAFE = (sqlite3_int64)9007199254740991;
#line 15 "./src2/objects/int64/int64.lzz"
sqlite3_int64 const MIN_SAFE = (sqlite3_int64)-9007199254740991;
#line 16 "./src2/objects/int64/int64.lzz"
sqlite3_uint64 const U32_in_U64 = (sqlite3_uint64)0xffffffff;
#line 20 "./src2/objects/int64/int64.lzz"
Int64::Int64 (int32_t _low, int32_t _high)
#line 20 "./src2/objects/int64/int64.lzz"
  : Nan::ObjectWrap ()
#line 20 "./src2/objects/int64/int64.lzz"
                                                                        {
		low = _low;
		high = _high;
		full = (sqlite3_int64)((((sqlite3_uint64)((uint32_t)_high)) << 32) | (uint32_t)_low);
	}
#line 25 "./src2/objects/int64/int64.lzz"
Int64::Int64 (sqlite3_int64 _full)
#line 25 "./src2/objects/int64/int64.lzz"
  : Nan::ObjectWrap ()
#line 25 "./src2/objects/int64/int64.lzz"
                                                                {
		low = (int32_t)((uint32_t)(((sqlite3_uint64)_full) & U32_in_U64));
		high = (int32_t)((uint32_t)(((sqlite3_uint64)_full) >> 32));
		full = _full;
	}
#line 30 "./src2/objects/int64/int64.lzz"
void Int64::Init (v8::Local <v8::Object> exports)
#line 30 "./src2/objects/int64/int64.lzz"
                                                        {
		v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(JS_new);
		t->InstanceTemplate()->SetInternalFieldCount(1);
		t->SetClassName(NEW_INTERNAL_STRING_FAST("Int64"));
		
		Nan::SetAccessor(t->InstanceTemplate(), NEW_INTERNAL_STRING_FAST("low"), JS_low);
		Nan::SetAccessor(t->InstanceTemplate(), NEW_INTERNAL_STRING_FAST("high"), JS_high);
		Nan::SetPrototypeMethod(t, "toString", JS_toString);
		Nan::SetPrototypeMethod(t, "valueOf", JS_valueOf);
		
		constructor.Reset(exports->GetIsolate(), Nan::GetFunction(t).ToLocalChecked());
		constructorTemplate.Reset(exports->GetIsolate(), t);
		fast_construct_int = NULL;
		
		Nan::Set(exports, NEW_INTERNAL_STRING_FAST("Int64"), Nan::GetFunction(t).ToLocalChecked());
	}
#line 67 "./src2/objects/int64/int64.lzz"
v8::Persistent <v8::Function> Int64::constructor;
#line 68 "./src2/objects/int64/int64.lzz"
v8::Persistent <v8::FunctionTemplate> Int64::constructorTemplate;
#line 69 "./src2/objects/int64/int64.lzz"
sqlite3_int64 * Int64::fast_construct_int;
#line 75 "./src2/objects/int64/int64.lzz"
void Int64::JS_new (Nan::FunctionCallbackInfo <v8::Value> const & info)
#line 75 "./src2/objects/int64/int64.lzz"
                                                                             {
		if (fast_construct_int != NULL) {
			Int64* int64 = new Int64(*fast_construct_int);
			fast_construct_int = NULL;
			int64->Wrap(info.This());
			return info.GetReturnValue().Set(info.This());
		}
		
		int32_t low;
		int32_t high;
		
		if (info.Length() < 1 || !info[0]->IsInt32()) {
			info.GetIsolate()->ThrowException(v8::Exception::TypeError(
				StringFromUtf8(info.GetIsolate(), "Expected arguemnt 1 to be a 32-bit signed integer", -1)));
			return;
		}
		low = v8::Local<v8::Int32>::Cast(info[0])->Value();
		
		if (info.Length() > 1) {
			if (!info[1]->IsInt32()) {
				info.GetIsolate()->ThrowException(v8::Exception::TypeError(
					StringFromUtf8(info.GetIsolate(), "Expected arguemnt 2 to be a 32-bit signed integer", -1)));
				return;
			}
			high = v8::Local<v8::Int32>::Cast(info[1])->Value();
		} else {
			high = 0;
		}
		
		Int64* int64 = new Int64(low, high);
		int64->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
#line 108 "./src2/objects/int64/int64.lzz"
void Int64::JS_low (v8::Local <v8::String> _, Nan::PropertyCallbackInfo <v8::Value> const & info)
#line 108 "./src2/objects/int64/int64.lzz"
                                                                                                      {
		info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), Nan::ObjectWrap::Unwrap<Int64>(info.This())->low));
	}
#line 111 "./src2/objects/int64/int64.lzz"
void Int64::JS_high (v8::Local <v8::String> _, Nan::PropertyCallbackInfo <v8::Value> const & info)
#line 111 "./src2/objects/int64/int64.lzz"
                                                                                                       {
		info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), Nan::ObjectWrap::Unwrap<Int64>(info.This())->high));
	}
#line 114 "./src2/objects/int64/int64.lzz"
void Int64::JS_toString (Nan::FunctionCallbackInfo <v8::Value> const & info)
#line 114 "./src2/objects/int64/int64.lzz"
                                                                                  {
		v8::Isolate* const isolate = info.GetIsolate();
		std::string string = std::to_string(static_cast<long long>(Nan::ObjectWrap::Unwrap<Int64>(info.This())->full));
		info.GetReturnValue().Set(StringFromLatin1(isolate, string.c_str(), string.length()));
	}
#line 119 "./src2/objects/int64/int64.lzz"
void Int64::JS_valueOf (Nan::FunctionCallbackInfo <v8::Value> const & info)
#line 119 "./src2/objects/int64/int64.lzz"
                                                                                 {
		sqlite3_int64 full = Nan::ObjectWrap::Unwrap<Int64>(info.This())->full;
		if (full <= MAX_SAFE && full >= MIN_SAFE) {
			info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), static_cast<double>(full)));
		} else {
			info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), std::numeric_limits<double>::quiet_NaN()));
		}
	}
#undef LZZ_INLINE
