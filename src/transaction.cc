#include <sqlite3.h>
#include <nan.h>
#include "database.h"
#include "transaction.h"

Transaction::Transaction() : Nan::ObjectWrap(),
	closed(false) {}
Transaction::~Transaction() {
	closed = true;
}
void Transaction::Init() {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Transaction").ToLocalChecked());
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Transaction::constructor);
NAN_METHOD(Transaction::New) {
	if (!CONSTRUCTING_PRIVILEGES) {
		return Nan::ThrowTypeError("Transactions can only be constructed by the db.begin() method.");
	}
	Transaction* trans = new Transaction();
	trans->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}
