#include <limits>
#include <string>
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "int64.h"

Int64::Int64(uint32_t low, uint32_t high) : Nan::ObjectWrap(),
	low(low),
	high(high) {
		full = (sqlite3_int64)(((sqlite3_uint64)high) << 32 | low);
	}
Int64::Int64(sqlite3_int64 full) : Nan::ObjectWrap(),
	full(full) {
		low = (uint32_t)((sqlite3_uint64)full);
		high = (uint32_t)(((sqlite3_uint64)full) >> 32);
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
	
	Nan::Set(exports, Nan::New("Int64").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Int64::constructor);

NAN_METHOD(Int64::New) {
	double low;
	double high;
	
	REQUIRE_ARGUMENT_NUMBER(0, low_number);
	if (info.Length() > 1) {
		REQUIRE_ARGUMENT_NUMBER(1, high_number);
		high = high_number->Value();
	} else {
		high = 0;
	}
	low = low_number->Value();
	
	if (!IS_POSITIVE_INTEGER(low) || !IS_POSITIVE_INTEGER(high) || low > (double)0xffffffff || high > (double)0xffffffff) {
		return Nan::ThrowTypeError("Expected both arguments to be 32 bit unsigned integers.");
	}
	
	Int64* int64 = new Int64((uint32_t)low, (uint32_t)high);
	int64->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

NAN_GETTER(Int64::Low) {
	info.GetReturnValue().Set(
		Nan::New<v8::Number>((double)(Nan::ObjectWrap::Unwrap<Int64>(info.This())->low))
	);
}
NAN_GETTER(Int64::High) {
	info.GetReturnValue().Set(
		Nan::New<v8::Number>((double)(Nan::ObjectWrap::Unwrap<Int64>(info.This())->high))
	);
}
NAN_METHOD(Int64::ToString) {
	info.GetReturnValue().Set(Nan::New(
		std::to_string((long long)(Nan::ObjectWrap::Unwrap<Int64>(info.This())->full)).c_str()
	).ToLocalChecked());
}
NAN_METHOD(Int64::ValueOf) {
	Int64* int64 = Nan::ObjectWrap::Unwrap<Int64>(info.This());
	if (int64->full <= (sqlite3_int64)9007199254740991 && int64->full >= (sqlite3_int64)-9007199254740991) {
		info.GetReturnValue().Set(Nan::New<v8::Number>((double)(int64->full)));
	} else {
		info.GetReturnValue().Set(Nan::New<v8::Number>(std::numeric_limits<double>::quiet_NaN()));
	}
}
