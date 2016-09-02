#include <sqlite3.h>
#include <nan.h>
#include "transaction.h"
#include "../database/database.h"
#include "../../workers/transaction-worker.h"
#include "../../multi-binder/multi-binder.h"

#include "new.cc"
#include "busy.cc"
#include "bind.cc"
#include "run.cc"
#include "delete-handles.cc"

Transaction::Transaction() : Nan::ObjectWrap(),
	db(NULL),
	handles(NULL),
	config_locked(false),
	bound(false),
	busy(false) {}
Transaction::~Transaction() {
	if (handles && db) {
		db->transs.Remove(this);
	}
	DeleteHandles()(this);
}
void Transaction::Init() {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Transaction").ToLocalChecked());
	
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("busy").ToLocalChecked(), Busy);
	Nan::SetPrototypeMethod(t, "bind", Bind);
	Nan::SetPrototypeMethod(t, "run", Run);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Transaction::constructor);
