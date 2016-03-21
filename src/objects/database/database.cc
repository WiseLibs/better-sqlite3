#include <sqlite3.h>
#include <nan.h>
#include "database.h"
#include "../statement/statement.h"
#include "../transaction/transaction.h"
#include "../../workers/open.h"
#include "../../workers/close.h"
#include "../../util/macros.h"
#include "../../util/handle-manager.h"
#include "../../util/frozen-buffer.h"

const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;

#include "new.cc"
#include "open.cc"
#include "close.cc"
#include "prepare.cc"
#include "begin.cc"

Database::Database() : Nan::ObjectWrap(),
	read_handle(NULL),
	write_handle(NULL),
	state(DB_CONNECTING),
	requests(0),
	workers(0),
	stmts(false) {}
Database::~Database() {
	state = DB_DONE;
	
	// This is necessary in the case that a database and its statements are
	// garbage collected at the same time. The database might be destroyed
	// first, so it needs to tell all of its statements "hey, I don't exist
	// anymore". By the same nature, statements must remove themselves from a
	// database's list when they are garbage collected first.
	stmts.Flush(Statement::DeleteHandles());
	
	CloseHandles(this);
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
	
	Nan::Set(target, Nan::New("Database").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}

// These handles must be set to NULL if they are closed somewhere else.
void Database::CloseHandles(Database* db) {
	sqlite3_close(db->read_handle);
	sqlite3_close(db->write_handle);
	db->read_handle = NULL;
	db->write_handle = NULL;
}
