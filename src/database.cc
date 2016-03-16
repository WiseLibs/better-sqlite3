#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "util/frozen-buffer.h"
#include "util/handle-manager.h"
#include "workers/open.h"
#include "workers/close.h"
#include "statement.h"
#include "transaction.h"
#include "database.h"

const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;

#include "database/new.cc"
#include "database/open.cc"
#include "database/close.cc"
#include "database/prepare.cc"
#include "database/begin.cc"

Database::Database() : Nan::ObjectWrap(),
	read_handle(NULL),
	write_handle(NULL),
	state(DB_CONNECTING),
	requests(0),
	workers(0),
	stmts(false) {}
Database::~Database() {
	state = DB_DONE;
	
	// Assures that any not-closed, not-garbage-collected statements, are closed and freed.
	// When a statement is closed somehwere else, or garbage collected, they won't be in this list.
	stmts.Flush([] (Statement* stmt) {
		stmt->handles.Close();
	});
	
	// These handles must be set to NULL if they are closed somewhere else.
	sqlite3_close_v2(read_handle);
	sqlite3_close_v2(write_handle);
}
NAN_MODULE_INIT(Database::Init) {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Database").ToLocalChecked());
	
	Nan::SetPrototypeMethod(t, "close", Close);
	Nan::SetPrototypeMethod(t, "prepare", Prepare);
	Nan::SetPrototypeMethod(t, "begin", Begin);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("open").ToLocalChecked(), Open);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
	Nan::Set(target, Nan::New("Database").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Database::constructor);
