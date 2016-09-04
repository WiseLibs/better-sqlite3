#include <sqlite3.h>
#include <nan.h>
#include "database.h"
#include "../statement/statement.h"
#include "../transaction/transaction.h"
#include "../../workers/database-workers/open.h"
#include "../../workers/database-workers/close.h"
#include "../../util/macros.h"
#include "../../util/handle-manager.h"
#include "../../util/frozen-buffer.h"
#include "../../util/transaction-handles.h"

const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;

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
	requests(0),
	workers(0),
	stmts(false),
	transs(false) {}
Database::~Database() {
	state = DB_DONE;
	CloseHandles(this);
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

int Database::CloseHandles(Database* db) {
	// This is necessary in the case that a database and its statements are
	// garbage collected at the same time. The database might be destroyed
	// first, so it needs to tell all of its statements "hey, I don't exist
	// anymore". By the same nature, statements must remove themselves from a
	// database's list when they are garbage collected first.
	db->stmts.Flush(Statement::CloseHandles());
	db->transs.Flush(Transaction::CloseHandles());
	
	delete db->t_handles;
	db->t_handles = NULL;
	
	int status1 = sqlite3_close(db->read_handle);
	int status2 = sqlite3_close(db->write_handle);
	db->read_handle = NULL;
	db->write_handle = NULL;
	
	return status1 != SQLITE_OK ? status1 : status2;
}
