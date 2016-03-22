#ifndef NODE_SQLITE3_PLUS_WORKER_STATEMENT_WORKER_H
#define NODE_SQLITE3_PLUS_WORKER_STATEMENT_WORKER_H

#include <sqlite3.h>

class Binder {
	public:
		Binder(sqlite3_stmt*);
		
	private:
		void AdvanceAnonIndex();
		void SetBindingError(int);
		void BindNumber(v8::Local<v8::Number>, int);
		void BindString(v8::Local<v8::String>, int);
		void BindBuffer(v8::Local<v8::Object>, int);
		void BindNull(int);
		void BindValue(v8::Local<v8::Value>, int);
		
		sqlite3_stmt* const handle;
		int const param_count;
		
		int bound_args;
		int anon_index;
		const char* error;
};

#endif