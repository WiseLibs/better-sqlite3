#include <limits>
#include <string>
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "int64.h"
const sqlite3_int64 MAX_SAFE = (sqlite3_int64)9007199254740991;
const sqlite3_int64 MIN_SAFE = (sqlite3_int64)-9007199254740991;
const sqlite3_uint64 U32_in_U64 = (sqlite3_uint64)0xffffffff;

Int64::Int64(int32_t low, int32_t high) : Nan::ObjectWrap(),
	low(low),
	high(high) {
		full = (sqlite3_int64)((((sqlite3_uint64)((uint32_t)high)) << 32) | (uint32_t)low);
	}
Int64::Int64(sqlite3_int64 full) : Nan::ObjectWrap(),
	full(full) {
		low = (int32_t)((uint32_t)(((sqlite3_uint64)full) & U32_in_U64));
		high = (int32_t)((uint32_t)(((sqlite3_uint64)full) >> 32));
	}
void Int64::Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Int64").ToLocalChecked());
	
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("low").ToLocalChecked(), Low);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("high").ToLocalChecked(), High);
	Nan::SetPrototypeMethod(t, "toString", ToString);
	Nan::SetPrototypeMethod(t, "valueOf", ValueOf);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
	constructorTemplate.Reset(t);
	
	Nan::Set(exports, Nan::New("Int64").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}
sqlite3_int64* Int64::FastConstructInt = NULL;
CONSTRUCTOR(Int64::constructor);
Nan::Persistent<v8::FunctionTemplate> Int64::constructorTemplate;

NAN_METHOD(Int64::New) {
	if (FastConstructInt != NULL) {
		Int64* int64 = new Int64(*FastConstructInt);
		FastConstructInt = NULL;
		int64->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
		return;
	}
	
	int32_t low;
	int32_t high;
	
	REQUIRE_ARGUMENT_INT32(0, low);
	if (info.Length() > 1) {
		REQUIRE_ARGUMENT_INT32(1, high);
	} else {
		high = 0;
	}
	
	Int64* int64 = new Int64(low, high);
	int64->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

NAN_GETTER(Int64::Low) {
	info.GetReturnValue().Set(
		Nan::New<v8::Int32>(Nan::ObjectWrap::Unwrap<Int64>(info.This())->low)
	);
}
NAN_GETTER(Int64::High) {
	info.GetReturnValue().Set(
		Nan::New<v8::Int32>(Nan::ObjectWrap::Unwrap<Int64>(info.This())->high)
	);
}
NAN_METHOD(Int64::ToString) {
	info.GetReturnValue().Set(Nan::New(
		std::to_string(static_cast<long long>(Nan::ObjectWrap::Unwrap<Int64>(info.This())->full)).c_str()
	).ToLocalChecked());
}
NAN_METHOD(Int64::ValueOf) {
	Int64* int64 = Nan::ObjectWrap::Unwrap<Int64>(info.This());
	if (int64->full <= MAX_SAFE && int64->full >= MIN_SAFE) {
		info.GetReturnValue().Set(Nan::New<v8::Number>(static_cast<double>(int64->full)));
	} else {
		info.GetReturnValue().Set(Nan::New<v8::Number>(std::numeric_limits<double>::quiet_NaN()));
	}
}
