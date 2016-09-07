#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "database.h"
#include "../statement/statement.h"
#include "../transaction/transaction.h"
#include "../../workers/database-workers/open.h"
#include "../../workers/database-workers/close.h"
#include "../../util/macros.h"
#include "../../util/transaction-handles.h"

const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;
sqlite3_uint64 NEXT_STATEMENT_ID = 0;
sqlite3_uint64 NEXT_TRANSACTION_ID = 0;

#include "new.cc"
#include "open.cc"
#include "close.cc"
#include "prepare.cc"
#include "create-transaction.cc"

Database::Database() : Nan::ObjectWrap(),
	read_handle(NULL),
	write_handle(NULL),
	t_handles(NULL),
	state(DB_CONNECTING),
	workers(0) {}
Database::~Database() {
	state = DB_DONE;
	
	// This is necessary in the case that a database and its statements are
	// garbage collected at the same time. The database might be destroyed
	// first, so it needs to tell all of its statements "hey, I don't exist
	// anymore". By the same nature, statements must remove themselves from a
	// database's sets when they are garbage collected first.
	for (Statement* stmt : stmts) {stmt->CloseHandles();}
	for (Transaction* trans : transs) {trans->CloseHandles();}
	stmts.clear();
	transs.clear();
	
	CloseHandles();
}
NAN_MODULE_INIT(Database::Init) {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Database").ToLocalChecked());
	
	Nan::SetPrototypeMethod(t, "close", Close);
	Nan::SetPrototypeMethod(t, "prepare", Prepare);
	Nan::SetPrototypeMethod(t, "transaction", CreateTransaction);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("open").ToLocalChecked(), Open);
	
	Nan::Set(target, Nan::New("Database").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}

// Returns an SQLite3 result code.
int Database::CloseHandles() {
	delete t_handles;
	int status1 = sqlite3_close(read_handle);
	int status2 = sqlite3_close(write_handle);
	
	t_handles = NULL;
	read_handle = NULL;
	write_handle = NULL;
	
	return status1 != SQLITE_OK ? status1 : status2;
}
