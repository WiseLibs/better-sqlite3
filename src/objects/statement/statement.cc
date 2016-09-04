#include <sqlite3.h>
#include <nan.h>
#include "statement.h"
#include "../database/database.h"
#include "../../workers/statement-workers/run.h"
#include "../../workers/statement-workers/get.h"
#include "../../workers/statement-workers/all.h"
#include "../../workers/statement-workers/each.h"
#include "../../util/macros.h"
#include "../../util/handle-manager.h"
#include "../../util/frozen-buffer.h"
#include "../../binder/binder.h"

#include "new.cc"
#include "cache.cc"
#include "bind.cc"
#include "pluck.cc"
#include "run.cc"
#include "get.cc"
#include "all.cc"
#include "each.cc"
#include "new-handle.cc"
#include "close-handles.cc"

Statement::Statement() : Nan::ObjectWrap(),
	db(NULL),
	handles(NULL),
	source(NULL),
	config_locked(false),
	bound(false),
	requests(0),
	pluck_column(false) {}
Statement::~Statement() {
	if (handles && db) {
		db->stmts.Remove(this);
	}
	delete handles;
	delete source;
}
void Statement::Init() {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Statement").ToLocalChecked());
	
	Nan::SetPrototypeMethod(t, "cache", Cache);
	Nan::SetPrototypeMethod(t, "bind", Bind);
	Nan::SetPrototypeMethod(t, "pluck", Pluck);
	Nan::SetPrototypeMethod(t, "run", Run);
	Nan::SetPrototypeMethod(t, "get", Get);
	Nan::SetPrototypeMethod(t, "all", All);
	Nan::SetPrototypeMethod(t, "each", Each);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Statement::constructor);
