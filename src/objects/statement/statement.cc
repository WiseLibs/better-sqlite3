#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "statement.h"
#include "../database/database.h"
#include "../../workers/statement-workers/run.h"
#include "../../workers/statement-workers/get.h"
#include "../../workers/statement-workers/all.h"
#include "../../workers/statement-workers/each.h"
#include "../../util/macros.h"
#include "../../binder/binder.h"

#include "new.cc"
#include "busy.cc"
#include "bind.cc"
#include "pluck.cc"
#include "run.cc"
#include "get.cc"
#include "all.cc"
#include "each.cc"

Statement::Statement() : Nan::ObjectWrap(),
	st_handle(NULL),
	config_locked(false),
	bound(false),
	busy(false),
	pluck_column(false) {}
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
	
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("busy").ToLocalChecked(), Busy);
	Nan::SetPrototypeMethod(t, "bind", Bind);
	Nan::SetPrototypeMethod(t, "pluck", Pluck);
	Nan::SetPrototypeMethod(t, "run", Run);
	Nan::SetPrototypeMethod(t, "get", Get);
	Nan::SetPrototypeMethod(t, "all", All);
	Nan::SetPrototypeMethod(t, "each", Each);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Statement::constructor);

bool Statement::Compare::operator() (const Statement* a, const Statement* b) {
	return a->id < b->id;
}
bool Statement::CloseHandles() {
	if (st_handle) {
		sqlite3_finalize(st_handle);
		st_handle = NULL;
		return true;
	}
	return false;
}
bool Statement::CloseIfPossible() {
	if (!busy) {
		CloseHandles();
		return true;
	}
	return false;
}
void Statement::EraseFromSet() {
	db->stmts.erase(this);
}
