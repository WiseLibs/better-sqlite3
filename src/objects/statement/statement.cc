#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "statement.h"
#include "../query.h"
#include "../database/database.h"
#include "../int64/int64.h"
#include "../../util/macros.h"
#include "../../util/data.h"
#include "../../binder/binder.h"

#include "new.cc"
#include "bind.cc"
#include "pluck.cc"
#include "run.cc"
#include "get.cc"
#include "all.cc"
#include "each.cc"
#include "util.cc"

Statement::Statement() : Nan::ObjectWrap(),
	st_handle(NULL),
	state(0) {}
Statement::~Statement() {
	if (CloseHandles()) {
		db->stmts.erase(this);
	}
}
void Statement::Init() {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Statement").ToLocalChecked());
	
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("returnsData").ToLocalChecked(), ReturnsData);
	Nan::SetPrototypeMethod(t, "safeIntegers", SafeIntegers);
	Nan::SetPrototypeMethod(t, "bind", Bind);
	Nan::SetPrototypeMethod(t, "pluck", Pluck);
	Nan::SetPrototypeMethod(t, "run", Run);
	Nan::SetPrototypeMethod(t, "get", Get);
	Nan::SetPrototypeMethod(t, "all", All);
	Nan::SetPrototypeMethod(t, "each", Each);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Statement::constructor);

// Returns true if the handles have not been previously closed.
bool Statement::CloseHandles() {
	if (st_handle) {
		if (state & BOUND) {sqlite3_clear_bindings(st_handle);}
		sqlite3_finalize(st_handle);
		st_handle = NULL;
		return true;
	}
	return false;
}
