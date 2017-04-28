#ifndef BETTER_SQLITE3_BINDER_H
#define BETTER_SQLITE3_BINDER_H

#include <sqlite3.h>
#include <nan.h>
class Query;
class BindMap;

class Binder {
	public:
		explicit Binder(sqlite3_stmt*);
		~Binder();
		virtual void Bind(Nan::NAN_METHOD_ARGS_TYPE, int, Query*);
		
		const char* error;
		
	protected:
		static bool IsPlainObject(v8::Local<v8::Object>);
		virtual int NextAnonIndex();
		
		void BindValue(v8::Local<v8::Value>, int = 0);
		int BindArray(v8::Local<v8::Array>);
		virtual int BindObject(v8::Local<v8::Object>, BindMap); // This should only be invoked once
		int BindArgs(Nan::NAN_METHOD_ARGS_TYPE, int, Query*);
		
		sqlite3_stmt* handle;
		int param_count;
		int anon_index; // This value should only be used by NextAnonIndex()
};

#endif