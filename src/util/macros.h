#ifndef BETTER_SQLITE3_MACROS_H
#define BETTER_SQLITE3_MACROS_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <sqlite3.h>
#include <nan.h>
#include "../util/strlcpy.h"

// Bitwise flags
#define CONFIG_LOCKED 0x01
#define BOUND 0x02
#define HAS_BIND_MAP 0x4
#define SAFE_INTS 0x8
#define PLUCK_COLUMN 0x10
#define RETURNS_DATA 0x20

// Given a double, returns whether the number is a positive integer.
inline bool IS_POSITIVE_INTEGER(double num) {
	return floor(num) == num && num >= 0.0;
}

// Copies a C-String into the heap and returns a pointer to it.
inline const char* COPY(const char* source) {
	size_t bytes = strlen(source) + 1;
	char* dest = new char[bytes];
	strlcpy(dest, source, bytes);
	return dest;
}

// Creates a stack-allocated std:string of the concatenation of 2 well-formed
// C-strings.
#define CONCAT2(result, a, b)                                                  \
	std::string result(a);                                                     \
	result += b;

// Creates a stack-allocated std:string of the concatenation of 3 well-formed
// C-strings.
#define CONCAT3(result, a, b, c)                                               \
	std::string result(a);                                                     \
	result += b;                                                               \
	result += c;

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

// Given a v8::Object and a C-string method name, retrieves the v8::Function
// representing that method, and invokes it with the given args. If the getter
// throws, if the property is not a function, or if the method throws, an error
// is thrown and the caller returns.
#define INVOKE_METHOD(result, obj, methodName, argc, argv)                     \
	GET_METHOD(_method, obj, methodName);                                      \
	Nan::MaybeLocal<v8::Value> _maybeValue = _method->Call(obj, argc, argv);   \
	if (_maybeValue.IsEmpty()) {return;}                                       \
	v8::Local<v8::Value> result = _maybeValue.ToLocalChecked();

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
// the caller returns. Otherwise, it is cast to a double and made available
// at the given variable name.
#define REQUIRE_ARGUMENT_NUMBER(index, var)                                    \
	if (info.Length() <= (index) || !info[index]->IsNumber()) {                \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be a number.");                   \
	}                                                                          \
	double var = v8::Local<v8::Number>::Cast(info[index])->Value();

// If the argument of the given index is not an int32, an error is thrown and
// the caller returns. Otherwise, it is cast to an int32_t and made available
// at the given variable name. Unlike other REQUIRE_ARGUMENT_ macros, the
// resulting local variable must be declared outside of the macro.
#define REQUIRE_ARGUMENT_INT32(index, var)                                     \
	if (info.Length() <= (index) || !info[index]->IsInt32()) {                 \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be a 32-bit signed integer.");    \
	}                                                                          \
	var = v8::Local<v8::Int32>::Cast(info[index])->Value();

// If the argument of the given index is not a function, an error is thrown and
// the caller returns. Otherwise, it is cast to a v8::Function and made
// available at the given variable name.
#define REQUIRE_ARGUMENT_FUNCTION(index, var)                                  \
	if (info.Length() <= (index) || !info[index]->IsFunction()) {              \
		return Nan::ThrowTypeError(                                            \
			"Expected argument " #index " to be a function.");                 \
	}                                                                          \
	v8::Local<v8::Function> var = v8::Local<v8::Function>::Cast(info[index]);

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

// Defines a persistent v8::function, used for constructors.
#define CONSTRUCTOR(name)                                                      \
	Nan::Persistent<v8::Function> name;

#define STATEMENT_CLEAR_BINDINGS(stmt)                                         \
	sqlite3_clear_bindings(stmt->st_handle);

#define TRANSACTION_CLEAR_BINDINGS(trans)                                      \
	for (unsigned int i=0; i<trans->handle_count; ++i) {                       \
		sqlite3_clear_bindings(trans->handles[i]);                             \
	}

// Common bind logic for statements.
#define STATEMENT_BIND(stmt, info, info_length)                                \
	Binder _binder(stmt->st_handle);                                           \
	QUERY_BIND(stmt, info, info_length, _binder, STATEMENT_CLEAR_BINDINGS);

// Common bind logic for transactions.
#define TRANSACTION_BIND(trans, info, info_length)                             \
	MultiBinder _binder(trans->handles, trans->handle_count);                  \
	QUERY_BIND(trans, info, info_length, _binder, TRANSACTION_CLEAR_BINDINGS);

// Common bind logic for statements and transactions.
#define QUERY_BIND(obj, info, info_length, binder, UNBIND_MACRO)               \
	binder.Bind(info, info_length, obj);                                       \
	if (binder.error) {                                                        \
		UNBIND_MACRO(obj);                                                     \
		if (binder.error[0] != 0) {                                            \
			Nan::ThrowError(binder.error);                                     \
		}                                                                      \
		return;                                                                \
	}

// The macro-instruction that runs before an SQLite request.
#define QUERY_START(obj, object_name, BIND_MACRO, info, info_length)           \
	if (!obj->db->open) {                                                      \
		return Nan::ThrowTypeError(                                            \
			"The associated database connection is closed.");                  \
	}                                                                          \
	if (obj->db->busy) {                                                       \
		return Nan::ThrowTypeError(                                            \
			"This database connection is busy executing a query.");            \
	}                                                                          \
	if (!(obj->state & CONFIG_LOCKED)) {obj->state |= CONFIG_LOCKED;}          \
	if (!(obj->state & BOUND)) {                                               \
		BIND_MACRO(obj, info, info_length);                                    \
	} else if (info_length > 0) {                                              \
		return Nan::ThrowTypeError(                                            \
			"This " #object_name " already has bound parameters.");            \
	}

// Like QUERY_THROW, but does not return from the caller function.
#define QUERY_THROW_STAY(obj, UNBIND_MACRO)                                    \
	obj->db->ThrowError();                                                     \
	if (!(obj->state & BOUND)) {UNBIND_MACRO(obj);}

// The macro-instruction that runs after a failed SQLite request.
#define QUERY_THROW(obj, UNBIND_MACRO)                                         \
	QUERY_THROW_STAY(obj, UNBIND_MACRO);                                       \
	return;

// The macro-instruction that runs after a successful SQLite request.
#define QUERY_RETURN(obj, UNBIND_MACRO, return_value)                          \
	info.GetReturnValue().Set(return_value);                                   \
	if (!(obj->state & BOUND)) {UNBIND_MACRO(obj);}                            \
	return;

// Creates a new internalized string from UTF-8 data.
#define NEW_INTERNAL_STRING8(string)                                           \
	v8::String::NewFromUtf8(                                                   \
		v8::Isolate::GetCurrent(),                                             \
		string,                                                                \
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
