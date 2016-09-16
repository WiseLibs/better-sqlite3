#ifndef BETTER_SQLITE3_MACROS_H
#define BETTER_SQLITE3_MACROS_H

#include <sys/types.h>
#include <cmath>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "strlcpy.h"

// Bitwise flags
#define CONFIG_LOCKED 0x01
#define BOUND 0x02
#define USED_BIND_MAP 0x4
#define HAS_BIND_MAP 0x8
#define SAFE_INTS 0x10
#define PLUCK_COLUMN 0x20

// Given a v8::String, returns a pointer to a heap-allocated C-String clone.
inline char* C_STRING(v8::Local<v8::String> string) {
	Nan::Utf8String utf8(string);
	
	size_t len = utf8.length() + 1;
	char* str = new char[len];
	strlcpy(str, *utf8, len);
	
	return str;
}

// Given a double, returns whether the number is a valid 32-bit unsigned integer.
inline bool IS_32BIT_UINT(double num) {
	return floor(num) == num && num < 4294967296 && num >= 0;
}

// Given a double, returns whether the number is a valid 32-bit signed integer.
inline bool IS_32BIT_INT(double num) {
	return floor(num) == num && num < 2147483648 && num >= -2147483648;
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
// This should not be used to retrieve arbitrary methods, because it is
// restricted by the limitations of NEW_INTERNAL_STRING_FAST().
#define GET_METHOD(result, obj, methodName)                                    \
	Nan::MaybeLocal<v8::Value> _maybeMethod =                                  \
		Nan::Get(obj, NEW_INTERNAL_STRING_FAST(methodName));                   \
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
	Nan::MakeCallback(obj, _method, argc, argv);

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

// If the argument of the given index is not an array, an error is thrown and
// the caller returns. Otherwise, it is cast to a v8::Array and made available
// at the given variable name.
#define REQUIRE_ARGUMENT_ARRAY(index, var)                                     \
	if (info.Length() <= (index) || !info[index]->IsArray()) {                 \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be an array.");                   \
	}                                                                          \
	v8::Local<v8::Array> var = v8::Local<v8::Array>::Cast(info[index]);

// Sets the given variable name to a bool, representing the truthiness of the
// argument at the given index.
#define TRUTHINESS_OF_ARGUMENT(index, var)                                     \
	bool var;                                                                  \
	if (info.Length() <= (index) || info[index]->BooleanValue() != true) {     \
		var = false;                                                           \
	} else {                                                                   \
		var = true;                                                            \
	}

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

// Defines a persistent v8::function, used for constructors.
#define CONSTRUCTOR(name)                                                      \
	Nan::Persistent<v8::Function> name;

#define STATEMENT_CLEAR_BINDINGS(stmt)                                         \
	sqlite3_clear_bindings(stmt->st_handle);

#define TRANSACTION_CLEAR_BINDINGS(trans)                                      \
	for (unsigned int i=0; i<trans->handle_count; ++i) {                       \
		sqlite3_clear_bindings(trans->handles[i]);                             \
	}

// Common bind logic for statements (must match STATEMENT_BIND_T_BUFFERS).
#define STATEMENT_BIND(stmt, info, info_length, bind_type)                     \
	if (info_length > 0) {                                                     \
		Binder _binder(stmt->st_handle, bind_type);                            \
		_binder.Bind(info, info_length, stmt);                                 \
		const char* _err = _binder.GetError();                                 \
		if (_err) {                                                            \
			STATEMENT_CLEAR_BINDINGS(stmt);                                    \
			return Nan::ThrowError(_err);                                      \
		}                                                                      \
	}

// Should be the same as STATEMENT_BIND, but uses the transient_buffers option.
#define STATEMENT_BIND_T_BUFFERS(stmt, info, info_length, bind_type)           \
	if (info_length > 0) {                                                     \
		Binder _binder(stmt->st_handle, bind_type, true);                      \
		_binder.Bind(info, info_length, stmt);                                 \
		const char* _err = _binder.GetError();                                 \
		if (_err) {                                                            \
			STATEMENT_CLEAR_BINDINGS(stmt);                                    \
			return Nan::ThrowError(_err);                                      \
		}                                                                      \
	}

// Common bind logic for transactions.
#define TRANSACTION_BIND(trans, info, info_length, bind_type)                  \
	if (info_length > 0) {                                                     \
		MultiBinder _binder(trans->handles, trans->handle_count, bind_type);   \
		_binder.Bind(info, info_length, trans);                                \
		const char* _err = _binder.GetError();                                 \
		if (_err) {                                                            \
			TRANSACTION_CLEAR_BINDINGS(trans);                                 \
			return Nan::ThrowError(_err);                                      \
		}                                                                      \
	}

// The macro-instruction that runs before an SQLite request.
#define QUERY_START(obj, object_name, BIND_MACRO, info, info_length)           \
	if (obj->db->in_each) {                                                    \
		return Nan::ThrowTypeError(                                            \
			"This database connection is busy executing a query.");            \
	}                                                                          \
	if (obj->db->state != DB_READY) {                                          \
		return Nan::ThrowError(                                                \
			"The associated database connection is closed.");                  \
	}                                                                          \
	if (!(obj->state & CONFIG_LOCKED)) {obj->state |= CONFIG_LOCKED;}          \
	if (!(obj->state & BOUND)) {                                               \
		BIND_MACRO(obj, info, info_length, SQLITE_STATIC);                     \
	} else if (info_length > 0) {                                              \
		return Nan::ThrowTypeError(                                            \
			"This " #object_name " already has bound parameters.");            \
	}                                                                          \
	SAFE_INTEGERS = obj->state & SAFE_INTS ? true : false;

// The macro-instruction that MUST be run before returning from a query.
#define QUERY_CLEANUP(obj, UNBIND_MACRO)                                       \
	if (!(obj->state & BOUND)) {UNBIND_MACRO(obj);}

// Like QUERY_THROW, but does not return from the caller function.
#define QUERY_THROW_STAY(obj, UNBIND_MACRO, error_out)                         \
	CONCAT2(_error_message, "SQLite: ", error_out);                            \
	QUERY_CLEANUP(obj, UNBIND_MACRO);                                          \
	Nan::ThrowError(_error_message);

// The macro-instruction that runs after a failed SQLite request.
#define QUERY_THROW(obj, UNBIND_MACRO, error_out)                              \
	QUERY_THROW_STAY(obj, UNBIND_MACRO, error_out);                            \
	return;

// The macro-instruction that runs after a successful SQLite request.
#define QUERY_RETURN(obj, UNBIND_MACRO, return_value)                          \
	QUERY_CLEANUP(obj, UNBIND_MACRO);                                          \
	info.GetReturnValue().Set(return_value);                                   \
	return;

// Creates a new internalized string from UTF-8 data.
#define NEW_INTERNAL_STRING8(string)                                           \
	v8::String::NewFromUtf8(                                                   \
		v8::Isolate::GetCurrent(),                                             \
		string,                                                                \
		v8::NewStringType::kInternalized                                       \
	).ToLocalChecked()

// Creates a new internalized string from UTF-16 data.
#define NEW_INTERNAL_STRING16(string)                                          \
	v8::String::NewFromTwoByte(                                                \
		v8::Isolate::GetCurrent(),                                             \
		static_cast<const uint16_t*>(string),                                  \
		v8::NewStringType::kInternalized                                       \
	).ToLocalChecked()

// Creates a new internalized string, but only works with Latin-1 characters.
#define NEW_INTERNAL_STRING_FAST(string)                                       \
	v8::String::NewFromOneByte(                                                \
		v8::Isolate::GetCurrent(),                                             \
		(const uint8_t*)string,                                                \
		v8::NewStringType::kInternalized                                       \
	).ToLocalChecked()

#endif