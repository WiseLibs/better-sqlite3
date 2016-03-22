#ifndef NODE_SQLITE3_PLUS_WORKER_STATEMENT_WORKER_H
#define NODE_SQLITE3_PLUS_WORKER_STATEMENT_WORKER_H

#include <sqlite3.h>
#include <nan.h>
#include "../objects/database/database.h"
#include "../objects/statement/statement.h"
#include "../util/macros.h"
#include "../util/handle-manager.h"
#include "../binder/binder.h"

template <class T>
class StatementWorker : public T {
	public:
		StatementWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index)
			: T(NULL),
			handle(handle),
			db_handle(stmt->db_handle),
			stmt(stmt),
			handle_index(handle_index) {}
			
		void HandleErrorCallback() {
			Nan::HandleScope scope;
			CONCAT2(message, "SQLite: ", T::ErrorMessage());
			Reject(Nan::Error(message));
		}
		
	protected:
		void Resolve(v8::Local<v8::Value> value) {
			FinishRequest();
			v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(T::GetFromPersistent((uint32_t)0));
			resolver->Resolve(Nan::GetCurrentContext(), value);
		}
		void Reject(v8::Local<v8::Value> value) {
			FinishRequest();
			v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(T::GetFromPersistent((uint32_t)0));
			resolver->Reject(Nan::GetCurrentContext(), value);
		}
		inline bool GetPluckColumn() {
			return stmt->pluck_column;
		}
		
		sqlite3_stmt* const handle;
		sqlite3* const db_handle;
		
	private:
		Statement* const stmt;
		int const handle_index;
		
		void FinishRequest() {
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
};

#endif