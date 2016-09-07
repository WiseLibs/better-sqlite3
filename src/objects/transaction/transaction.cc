#include <set>
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
#include "build-bind-map.cc"

Transaction::Transaction() : Nan::ObjectWrap(),
	handles(NULL),
	state(0) {}
Transaction::~Transaction() {
	if (CloseHandles()) {
		db->transs.erase(this);
	}
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

bool Transaction::Compare::operator() (const Transaction* a, const Transaction* b) {
	return a->id < b->id;
}
bool Transaction::CloseHandles() {
	if (handles) {
		for (unsigned int i=0; i<handle_count; ++i) {
			sqlite3_finalize(handles[i]);
		}
		delete[] handles;
		handles = NULL;
		return true;
	}
	return false;
}
bool Transaction::CloseIfPossible() {
	if (!(state & BUSY)) {
		CloseHandles();
		return true;
	}
	return false;
}
void Transaction::EraseFromSet() {
	db->transs.erase(this);
}
