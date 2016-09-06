#ifndef NODE_SQLITE3_PLUS_MACROS_H
#define NODE_SQLITE3_PLUS_MACROS_H

#include <sys/types.h>
#include <cmath>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "strlcpy.h"

// Bitwise flags
#define BUSY 0x01
#define CONFIG_LOCKED 0x02
#define BOUND 0x04
#define PLUCK_COLUMN 0x08

// Given a v8::String, returns a pointer to a heap-allocated C-String clone.
inline char* C_STRING(v8::Local<v8::String> string) {
	Nan::Utf8String utf8(string);
	
	size_t len = utf8.length() + 1;
	char* str = new char[len];
	strlcpy(str, *utf8, len);
	
	return str;
}

// Given a double, returns whether the number is non-negative, finite, and
// an integer.
inline bool IS_POSITIVE_INTEGER(double num) {
	return std::isfinite(num) && num >= 0 && floor(num) == num;
}

// Creates a stack-allocated buffer of the concatenation of 2 well-formed
// C-strings.
#define CONCAT2(result, a, b)                                                  \
	char result[strlen(a) + strlen(b) + 1];                                    \
	strcpy(result, a);                                                         \
	strcat(result, b);

// Creates a stack-allocated buffer of the concatenation of 3 well-formed
// C-strings.
#define CONCAT3(result, a, b, c)                                               \
	char result[strlen(a) + strlen(b) + strlen(c) + 1];                        \
	strcpy(result, a);                                                         \
	strcat(result, b);                                                         \
	strcat(result, c);

// Given a v8::Object and a C-string method name, retrieves the v8::Function
// representing that method. If the getter throws, or if the property is not a
// function, an error is thrown and the caller returns.
#define GET_METHOD(result, obj, methodName)                                    \
	Nan::MaybeLocal<v8::Value> _maybeMethod =                                  \
		Nan::Get(obj, NEW_INTERNAL_STRING(methodName));                        \
	if (_maybeMethod.IsEmpty()) {return;}                                      \
	v8::Local<v8::Value> _localMethod = _maybeMethod.ToLocalChecked();         \
	if (!_localMethod->IsFunction()) {                                         \
		return Nan::ThrowTypeError(                                            \
			"" #obj "[" #methodName "]() is not a function");                  \
	}                                                                          \
	v8::Local<v8::Function> result =                                           \
		v8::Local<v8::Function>::Cast(_localMethod);

// Invokes the `emit` method on the given v8::Object, with the given args.
// If the `emit` method cannot be retrieved, an error is thrown and the caller
// returns. This should ONLY be invoked in a libuv async callback.
#define EMIT_EVENT(obj, argc, argv)                                            \
	GET_METHOD(_method, obj, "emit");                                          \
	Nan::MakeCallback(obj, _method, argc, argv);                               \

// If the argument of the given index is not a boolean, an error is thrown and
// the caller returns. Otherwise, it is cast to a c++ bool and made available
// at the given variable name.
#define REQUIRE_ARGUMENT_BOOLEAN(index, var)                                   \
	if (info.Length() <= (index) || !info[index]->IsBoolean()) {               \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be a boolean.");                  \
	}                                                                          \
	bool var = v8::Local<v8::Boolean>::Cast(info[index])->Value();

// If the argument of the given index is not a string, an error is thrown and
// the caller returns. Otherwise, it is cast to a v8::String and made available
// at the given variable name.
#define REQUIRE_ARGUMENT_STRING(index, var)                                    \
	if (info.Length() <= (index) || !info[index]->IsString()) {                \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be a string.");                   \
	}                                                                          \
	v8::Local<v8::String> var = v8::Local<v8::String>::Cast(info[index]);

// If the argument of the given index is not a number, an error is thrown and
// the caller returns. Otherwise, it is cast to a v8::Number and made available
// at the given variable name.
#define REQUIRE_ARGUMENT_NUMBER(index, var)                                    \
	if (info.Length() <= (index) || !info[index]->IsNumber()) {                \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be a number.");                   \
	}                                                                          \
	v8::Local<v8::Number> var = v8::Local<v8::Number>::Cast(info[index]);

// If the last argument is not a function, an error is thrown and the caller
// returns. Otherwise, it is cast to a v8::Function and made available at the
// given variable name.
#define REQUIRE_LAST_ARGUMENT_FUNCTION(indexOut, var)                          \
	int indexOut = info.Length() - 1;                                          \
	if (indexOut < 0 || !info[indexOut]->IsFunction()) {                       \
		return Nan::ThrowTypeError(                                            \
			"Expected the final argument to be a function.");                  \
	}                                                                          \
	v8::Local<v8::Function> var = v8::Local<v8::Function>::Cast(info[indexOut]);

// If the last two arguments are not both functions, an error is thrown and the
// caller returns. Otherwise, they are cast to v8::Functions and made available
// at the given variable names.
#define REQUIRE_LAST_TWO_ARGUMENTS_FUNCTIONS(indexOut, var1, var2)             \
	int indexOut = info.Length() - 2;                                          \
	if (indexOut < 0 || !info[indexOut]->IsFunction()                          \
	                 || !info[indexOut + 1]->IsFunction()) {                   \
		return Nan::ThrowTypeError(                                            \
			"Expected the final two arguments to both be functions.");         \
	}                                                                          \
	v8::Local<v8::Function> var1 =                                             \
		v8::Local<v8::Function>::Cast(info[indexOut]);                         \
	v8::Local<v8::Function> var2 =                                             \
		v8::Local<v8::Function>::Cast(info[indexOut + 1]);                     \

// If the argument of the given index is not an array, an error is thrown and
// the caller returns. Otherwise, it is cast to a v8::Array and made available
// at the given variable name.
#define REQUIRE_ARGUMENT_ARRAY(index, var)                                     \
	if (info.Length() <= (index) || !info[index]->IsArray()) {                 \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be an array.");                   \
	}                                                                          \
	v8::Local<v8::Array> var = v8::Local<v8::Array>::Cast(info[index]);

// Given a v8::Object and a C-string method name, retrieves the v8::Function
// representing that method, and invokes it with the given args. If the getter
// throws, if the property is not a function, or if the method throws, an error
// is thrown and the caller returns.
#define INVOKE_METHOD(result, obj, methodName, argc, argv)                     \
	GET_METHOD(_method, obj, methodName);                                      \
	Nan::MaybeLocal<v8::Value> _maybeValue =                                   \
		Nan::Call(_method, obj, argc, argv);                                   \
	if (_maybeValue.IsEmpty()) {return;}                                       \
	v8::Local<v8::Value> result = _maybeValue.ToLocalChecked();

// Given a v8::String, replaces it with a version that has been trimmed by
// String.prototype.trim. If any part of the process throws, or if the result
// of String.prototype.trim is not a string, an error is thrown and the caller
// returns.
#define TRIM_STRING(string)                                                    \
	v8::Local<v8::StringObject> _stringObject =                                \
		Nan::New<v8::StringObject>(string);                                    \
	INVOKE_METHOD(_trimmedString, _stringObject, "trim", 0, NULL);             \
	if (!_trimmedString->IsString()) {                                         \
		return Nan::ThrowTypeError(                                            \
			"Expected String.prototype.trim to return a string.");             \
	} else {                                                                   \
		string = v8::Local<v8::String>::Cast(_trimmedString);                  \
	}

// Defines a persistent v8::function, used for constructors.
#define CONSTRUCTOR(name)                                                      \
	Nan::Persistent<v8::Function> name;

// Common bind logic for statements.
#define STATEMENT_BIND(stmt, info, info_length)                                \
	if (info_length > 0) {                                                     \
		Binder _binder(stmt->st_handle);                                       \
		_binder.Bind(info, info_length);                                       \
		const char* _err = _binder.GetError();                                 \
		if (_err) {                                                            \
			sqlite3_clear_bindings(stmt->st_handle);                           \
			return Nan::ThrowError(_err);                                      \
		}                                                                      \
	}

// Common bind logic for transactions.
#define TRANSACTION_BIND(trans, info, info_length)                             \
	if (info_length > 0) {                                                     \
		MultiBinder _binder(trans->handles, trans->handle_count);              \
		_binder.Bind(info, info_length);                                       \
		const char* _err = _binder.GetError();                                 \
		if (_err) {                                                            \
			for (unsigned int i=0; i<trans->handle_count; ++i) {               \
				sqlite3_clear_bindings(trans->handles[i]);                     \
			}                                                                  \
			return Nan::ThrowError(_err);                                      \
		}                                                                      \
	}

// The first macro-instruction for setting up an asynchronous SQLite request.
#define WORKER_START(obj, info, info_length, BIND_MACRO, object_name)          \
	if (obj->state & BUSY) {                                                   \
		return Nan::ThrowTypeError(                                            \
	"This " #object_name " is mid-execution. You must wait for it to finish.");\
	}                                                                          \
	if (obj->db->state != DB_READY) {                                          \
		return Nan::ThrowError(                                                \
			"The associated database connection is closed.");                  \
	}                                                                          \
	if (!(obj->state & CONFIG_LOCKED)) {obj->state |= CONFIG_LOCKED;}          \
	if (!(obj->state & BOUND)) {                                               \
		BIND_MACRO(obj, info, info_length);                                    \
	} else if (info_length > 0) {                                              \
		return Nan::ThrowTypeError(                                            \
			"This " #object_name " already has bound parameters.");            \
	}

// The second macro-instruction for setting up an asynchronous SQLite request.
// Returns the statement object making the request.
#define WORKER_END(obj, worker)                                                \
	obj->state |= BUSY;                                                        \
	obj->Ref();                                                                \
	Nan::AsyncQueueWorker(worker);                                             \
	info.GetReturnValue().Set(info.This());

// Enters the mutex for the sqlite3 database handle.
#define LOCK_DB(db_handle)                                                     \
	sqlite3_mutex_enter(sqlite3_db_mutex(db_handle))

// Enters the mutex for the sqlite3 database handle if the mutex is not
// already in use by another thread.
#define TRY_TO_LOCK_DB(db_handle)                                              \
	sqlite3_mutex_enter(sqlite3_db_mutex(db_handle))

// Exits the mutex for the sqlite3 database handle.
#define UNLOCK_DB(db_handle)                                                   \
	sqlite3_mutex_leave(sqlite3_db_mutex(db_handle))

// Creates a new internalized string.
#define NEW_INTERNAL_STRING(string)                                            \
	v8::String::NewFromUtf8(                                                   \
		v8::Isolate::GetCurrent(), string, v8::NewStringType::kInternalized    \
	).ToLocalChecked()

#endif