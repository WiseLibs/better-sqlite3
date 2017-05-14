#include <cassert>
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "database.h"
#include "../statement/statement.h"
#include "../transaction/transaction.h"
#include "../../util/macros.h"
#include "../../util/data.h"
#include "../../util/transaction-handles.h"
#include "../../util/bind-map.h"
#include "../../util/functor.h"

const int max_buffer_size = node::Buffer::kMaxLength > 0x7fffffffU ? 0x7fffffff : static_cast<int>(node::Buffer::kMaxLength);
const int max_string_size = v8::String::kMaxLength;
const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;
sqlite3_uint64 NEXT_STATEMENT_ID = 0;
sqlite3_uint64 NEXT_TRANSACTION_ID = 0;

#include "new.cc"
#include "close.cc"
#include "create-statement.cc"
#include "create-transaction.cc"
#include "custom-functions.cc"
#include "custom-aggregates.cc"
#include "create-function.cc"
#include "exec.cc"
#include "pragma.cc"
#include "checkpoint.cc"
#include "util.cc"

Database::Database(bool readonly) : Nan::ObjectWrap(),
	t_handles(),
	stmts(),
	transs(),
	db_handle(NULL),
	open(true),
	busy(false),
	safe_ints(false),
	was_js_error(false),
	readonly(readonly) {}
Database::~Database() {
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
	Nan::SetPrototypeMethod(t, "prepare", CreateStatement);
	Nan::SetPrototypeMethod(t, "transaction", CreateTransaction);
	Nan::SetPrototypeMethod(t, "register", CreateFunction);
	Nan::SetPrototypeMethod(t, "exec", Exec);
	Nan::SetPrototypeMethod(t, "pragma", Pragma);
	Nan::SetPrototypeMethod(t, "checkpoint", Checkpoint);
	Nan::SetPrototypeMethod(t, "defaultSafeIntegers", DefaultSafeIntegers);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("open").ToLocalChecked(), Open);
	
	Nan::Set(exports, Nan::New("Database").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}

// Returns an SQLite3 result code.
int Database::CloseHandles() {
	t_handles.close();
	int status = sqlite3_close(db_handle);
	db_handle = NULL;
	return status;
}

void Database::CloseChildHandles() {
	for (Statement* stmt : stmts) {stmt->CloseHandles();}
	for (Transaction* trans : transs) {trans->CloseHandles();}
	stmts.clear();
	transs.clear();
}

int Database::OpenHandles(const char* filename) {
	int status = sqlite3_open(filename, &db_handle);
	if (status != SQLITE_OK) {
		return status;
	}
	
	assert(sqlite3_db_mutex(db_handle) == NULL);
	sqlite3_busy_timeout(db_handle, 5000);
	sqlite3_limit(db_handle, SQLITE_LIMIT_LENGTH, max_buffer_size < max_string_size ? max_buffer_size : max_string_size);
	sqlite3_limit(db_handle, SQLITE_LIMIT_SQL_LENGTH, max_string_size);
	sqlite3_limit(db_handle, SQLITE_LIMIT_COLUMN, 0x7fffffff);
	sqlite3_limit(db_handle, SQLITE_LIMIT_COMPOUND_SELECT, 0x7fffffff);
	sqlite3_limit(db_handle, SQLITE_LIMIT_VARIABLE_NUMBER, parameter_mask);
	
	return t_handles.open(db_handle);
}
