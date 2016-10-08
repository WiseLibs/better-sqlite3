#include <cassert>
#include <algorithm>
#include <sqlite3.h>
#include <nan.h>
#include "open.h"
#include "../objects/database/database.h"
#include "../util/macros.h"
#include "../util/transaction-handles.h"
const int max_buffer_size = node::Buffer::kMaxLength > 0x7fffffffU ? 0x7fffffff : static_cast<int>(node::Buffer::kMaxLength);
const int max_string_size = v8::String::kMaxLength;

OpenWorker::OpenWorker(Database* db, char* filename) : Nan::AsyncWorker(NULL),
	db(db),
	filename(filename) {}
OpenWorker::~OpenWorker() {
	delete[] filename;
}
void OpenWorker::Execute() {
	int status;
	
	status = sqlite3_open(filename, &db->db_handle);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->db_handle));
		db->CloseHandles();
		return;
	}
	
	assert(sqlite3_db_mutex(db->db_handle) == NULL);
	sqlite3_busy_timeout(db->db_handle, 5000);
	sqlite3_limit(db->db_handle, SQLITE_LIMIT_LENGTH, (std::min)(max_buffer_size, max_string_size));
	sqlite3_limit(db->db_handle, SQLITE_LIMIT_SQL_LENGTH, max_string_size);
	sqlite3_limit(db->db_handle, SQLITE_LIMIT_COLUMN, 0x7fffffff);
	sqlite3_limit(db->db_handle, SQLITE_LIMIT_COMPOUND_SELECT, 0x7fffffff);
	sqlite3_limit(db->db_handle, SQLITE_LIMIT_VARIABLE_NUMBER, 0x7fffffff);
	
	db->t_handles = new TransactionHandles(db->db_handle, &status);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->db_handle));
		db->CloseHandles();
		return;
	}
}
void OpenWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	v8::Local<v8::Object> database = db->handle();
	
	if (--db->workers == 0) {db->Unref();}
	
	if (db->state == DB_DONE) {
		db->CloseHandles();
	} else {
		db->state = DB_READY;
		v8::Local<v8::Value> args[1] = {NEW_INTERNAL_STRING_FAST("open")};
		EMIT_EVENT(database, 1, args);
	}
}
void OpenWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
	v8::Local<v8::Object> database = db->handle();
	
	if (--db->workers == 0) {db->Unref();}
	
	if (db->state != DB_DONE) {
		db->state = DB_DONE;
		
		CONCAT2(message, "SQLite: ", ErrorMessage());
		v8::Local<v8::Value> args[2] = {
			NEW_INTERNAL_STRING_FAST("close"),
			Nan::Error(message.c_str())
		};
		
		EMIT_EVENT(database, 2, args);
	}
}
