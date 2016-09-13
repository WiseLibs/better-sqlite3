#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "database.h"
#include "../statement/statement.h"
#include "../transaction/transaction.h"
#include "../../workers/open.h"
#include "../../workers/close.h"
#include "../../util/macros.h"
#include "../../util/data.h"
#include "../../util/list.h"
#include "../../util/transaction-handles.h"

const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;
sqlite3_uint64 NEXT_STATEMENT_ID = 0;
sqlite3_uint64 NEXT_TRANSACTION_ID = 0;
Nan::Persistent<v8::Function> NullFactory;

#include "new.cc"
#include "open.cc"
#include "close.cc"
#include "create-statement.cc"
#include "create-transaction.cc"
#include "pragma.cc"
#include "checkpoint.cc"

Database::Database() : Nan::ObjectWrap(),
	db_handle(NULL),
	t_handles(NULL),
	state(DB_CONNECTING),
	workers(0),
	in_each(false) {}
Database::~Database() {
	state = DB_DONE;
	
	// This is necessary in the case that a database and its statements are
	// garbage collected at the same time. The database might be destroyed
	// first, so it needs to tell all of its statements "hey, I don't exist
	// anymore". By the same nature, statements must remove themselves from a
	// database's sets when they are garbage collected first.
	CloseChildHandles();
	
	CloseHandles();
}
void Database::Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Database").ToLocalChecked());
	
	Nan::SetPrototypeMethod(t, "close", Close);
	Nan::SetPrototypeMethod(t, "statement", CreateStatement);
	Nan::SetPrototypeMethod(t, "transaction", CreateTransaction);
	Nan::SetPrototypeMethod(t, "pragma", Pragma);
	Nan::SetPrototypeMethod(t, "checkpoint", Checkpoint);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("open").ToLocalChecked(), Open);
	
	Nan::Set(exports, Nan::New("Database").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
	
	// Save NullFactory to persistent handle.
	v8::Local<v8::Function> require = v8::Local<v8::Function>::Cast(Nan::Get(module, Nan::New("require").ToLocalChecked()).ToLocalChecked());
	v8::Local<v8::Value> args[1] = {Nan::New("../../lib/null-factory.js").ToLocalChecked()};
	NullFactory.Reset(v8::Local<v8::Function>::Cast(Nan::Call(require, module, 1, args).ToLocalChecked()));
}

// Returns an SQLite3 result code.
int Database::CloseHandles() {
	delete t_handles;
	int status = sqlite3_close(db_handle);
	t_handles = NULL;
	db_handle = NULL;
	return status;
}

void Database::CloseChildHandles() {
	for (Statement* stmt : stmts) {stmt->CloseHandles();}
	for (Transaction* trans : transs) {trans->CloseHandles();}
	stmts.clear();
	transs.clear();
}
