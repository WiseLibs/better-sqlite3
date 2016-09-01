#ifndef NODE_SQLITE3_PLUS_BINDER_H
#define NODE_SQLITE3_PLUS_BINDER_H

#include <sqlite3.h>
#include <nan.h>

class Binder {
	public:
		Binder(sqlite3_stmt*);
		~Binder();
		virtual void Bind(Nan::NAN_METHOD_ARGS_TYPE, int);
		const char* GetError();
		
	protected:
		virtual unsigned int NextAnonIndex();
		void SetBindingError(int);
		void BindNumber(v8::Local<v8::Number>, unsigned int = 0);
		void BindString(v8::Local<v8::String>, unsigned int = 0);
		void BindBuffer(v8::Local<v8::Object>, unsigned int = 0);
		void BindNull(unsigned int = 0);
		void BindValue(v8::Local<v8::Value>, unsigned int = 0);
		
		unsigned int BindArray(v8::Local<v8::Array>);
		unsigned int BindArrayLike(v8::Local<v8::Object>, unsigned int);
		virtual unsigned int BindObject(v8::Local<v8::Object>); // This should only be invoked once
		
		unsigned int GetNamedParameterIndex(const char*, int);
		double GetArrayLikeLength(v8::Local<v8::Object>);
		static bool IsPlainObject(v8::Local<v8::Object>);
		
		sqlite3_stmt* handle;
		unsigned int param_count;
		
		unsigned int anon_index; // This value should only be used by NextAnonIndex()
		const char* error;
		char* error_extra;
		const char* error_full;
};

#endif