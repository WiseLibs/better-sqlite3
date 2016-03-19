#include <sqlite3.h>
#include <nan.h>
#include "statement-worker.h"
#include "../objects/database/database.h"
#include "../objects/statement/statement.h"
#include "../util/macros.h"
#include "../util/handle-manager.h"

template <class T>
StatementWorker<T>::StatementWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index)
	: T(NULL), handle(handle), db_handle(stmt->db_handle), stmt(stmt), handle_index(handle_index) {}

template <class T>
void StatementWorker<T>::Resolve(v8::Local<v8::Value> value) {
	FinishRequest();
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(T::GetFromPersistent((uint32_t)0));
	resolver->Resolve(Nan::GetCurrentContext(), value);
}

template <class T>
void StatementWorker<T>::Reject(v8::Local<v8::Value> value) {
	FinishRequest();
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(T::GetFromPersistent((uint32_t)0));
	resolver->Reject(Nan::GetCurrentContext(), value);
}

template <class T>
void StatementWorker<T>::FinishRequest() {
	stmt->requests -= 1;
	stmt->db->requests -= 1;
	stmt->handles->Release(handle_index, handle);
	if (stmt->requests == 0) {
		stmt->Unref();
		if (stmt->db->state == DB_DONE && stmt->db->requests == 0) {
			stmt->db->ActuallyClose();
		}
	}
}

template <class T>
void StatementWorker<T>::HandleErrorCallback() {
	Nan::HandleScope scope;
	CONCAT2(message, "SQLite: ", T::ErrorMessage());
	Reject(Nan::Error(message));
}
