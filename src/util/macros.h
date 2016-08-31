#ifndef NODE_SQLITE3_PLUS_MACROS_H
#define NODE_SQLITE3_PLUS_MACROS_H

#include <sys/types.h>
#include <cmath>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "strlcpy.h"

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
		Nan::Get(obj, Nan::New(methodName).ToLocalChecked());                  \
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

// Invokes the `emitAsync` method on the given v8::Object, with the given args.
// If the `emitAsync` method cannot be retrieved, an error is thrown and the
// caller returns. This should ONLY be invoked in a libuv async callback.
#define EMIT_EVENT_ASYNC(obj, argc, argv)                                      \
	GET_METHOD(_method, obj, "emitAsync");                                     \
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

// The first macro-instruction for setting up an asynchronous SQLite request.
// _i is the index returned by HandleManager#Request.
// _handle if the handle set given by HandleManager#Request.
#define STATEMENT_START(stmt)                                                  \
	if (stmt->db->state != DB_READY) {                                         \
		return Nan::ThrowError(                                                \
			"The associated database connection is closed.");                  \
	}                                                                          \
	if (!stmt->config_locked) {stmt->config_locked = true;}                    \
	                                                                           \
	sqlite3_stmt* _handle;                                                     \
	int _i = stmt->handles->Request(&_handle);                                 \
	if (_handle == NULL) {                                                     \
		return Nan::ThrowError(                                                \
			"SQLite failed to create a prepared statement");                   \
	}

#define STATEMENT_BIND(stmt, info_length)                                      \
	if (!stmt->bound) {                                                        \
		Binder _binder(_handle);                                               \
		_binder.Bind(info, info_length);                                       \
		const char* err = _binder.GetError();                                  \
		if (err) {                                                             \
			stmt->handles->Release(_i, _handle);                               \
			return Nan::ThrowError(err);                                       \
		}                                                                      \
	} else if (info_length > 0) {                                              \
		stmt->handles->Release(_i, _handle);                                   \
		return Nan::ThrowTypeError(                                            \
			"This statement already has bound parameters.");                   \
	}

// The second macro-instruction for setting up an asynchronous SQLite request.
// Returns the statement object making the request.
#define STATEMENT_END(stmt, worker)                                            \
	stmt->requests += 1;                                                       \
	stmt->db->requests += 1;                                                   \
	stmt->Ref();                                                               \
	Nan::AsyncQueueWorker(worker);                                             \
	                                                                           \
	info.GetReturnValue().Set(info.This());

// Enters the mutex for the sqlite3 database handle.
#define LOCK_DB(db_handle)                                                     \
	sqlite3_mutex_enter(sqlite3_db_mutex(db_handle));

// Exits the mutex for the sqlite3 database handle.
#define UNLOCK_DB(db_handle)                                                   \
	sqlite3_mutex_leave(sqlite3_db_mutex(db_handle));

// When used in a StatementWorker, gives the number of columns that the
// statement returns, based on the sqlite3_stmt handle and pluck_column.
#define GET_COLUMN_COUNT(len)                                                  \
	len = sqlite3_column_count(handle);                                        \
	if (len < 1) {                                                             \
		UNLOCK_DB(db_handle);                                                  \
		return SetErrorMessage("This statement returns no result columns.");   \
	}                                                                          \
	if (GetPluckColumn()) {                                                    \
		len = 1;                                                               \
	}

#endif