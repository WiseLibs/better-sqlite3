#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "transaction.h"
#include "../query.h"
#include "../database/database.h"
#include "../int64/int64.h"
#include "../../multi-binder/multi-binder.h"

#include "new.cc"
#include "bind.cc"
#include "run.cc"
#include "util.cc"

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
	
	Nan::SetPrototypeMethod(t, "safeIntegers", SafeIntegers);
	Nan::SetPrototypeMethod(t, "bind", Bind);
	Nan::SetPrototypeMethod(t, "run", Run);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Transaction::constructor);

// Returns true if the handles have not been previously closed.
bool Transaction::CloseHandles() {
	if (handles) {
		if (state & BOUND) {
			for (unsigned int i=0; i<handle_count; ++i) {
				sqlite3_clear_bindings(handles[i]);
				sqlite3_finalize(handles[i]);
			}
		} else {
			for (unsigned int i=0; i<handle_count; ++i) {
				sqlite3_finalize(handles[i]);
			}
		}
		delete[] handles;
		handles = NULL;
		return true;
	}
	return false;
}
