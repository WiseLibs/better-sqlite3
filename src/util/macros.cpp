#define NODE_ARGUMENTS const v8::FunctionCallbackInfo<v8::Value>&
#define NODE_ARGUMENTS_POINTER const v8::FunctionCallbackInfo<v8::Value>*
#define NODE_METHOD(name) void name(NODE_ARGUMENTS info)
#define NODE_GETTER(name) void name(v8::Local<v8::Name> _, const v8::PropertyCallbackInfo<v8::Value>& info)
#define INIT(name) v8::Local<v8::Function> name(v8::Isolate* isolate, v8::Local<v8::External> data)

#define EasyIsolate v8::Isolate* isolate = v8::Isolate::GetCurrent()
#define OnlyIsolate info.GetIsolate()
#define OnlyContext isolate->GetCurrentContext()
#define OnlyAddon static_cast<Addon*>(info.Data().As<v8::External>()->Value())
#define UseIsolate v8::Isolate* isolate = OnlyIsolate
#define UseContext v8::Local<v8::Context> ctx = OnlyContext
#define UseAddon Addon* addon = OnlyAddon
#define Unwrap node::ObjectWrap::Unwrap

#define REQUIRE_ARGUMENT_ANY(at, var)                                          \
	if (info.Length() <= (at()))                                               \
		return ThrowTypeError("Expected a "#at" argument");                    \
	var = info[at()]

#define _REQUIRE_ARGUMENT(at, var, Type, message, ...)                         \
	if (info.Length() <= (at()) || !info[at()]->Is##Type())                    \
		return ThrowTypeError("Expected "#at" argument to be "#message);       \
	var = (info[at()].As<v8::Type>())__VA_ARGS__

#define REQUIRE_ARGUMENT_INT32(at, var)                                        \
	_REQUIRE_ARGUMENT(at, var, Int32, a 32-bit signed integer, ->Value())
#define REQUIRE_ARGUMENT_BOOLEAN(at, var)                                      \
	_REQUIRE_ARGUMENT(at, var, Boolean, a boolean, ->Value())
#define REQUIRE_ARGUMENT_STRING(at, var)                                       \
	_REQUIRE_ARGUMENT(at, var, String, a string)
#define REQUIRE_ARGUMENT_OBJECT(at, var)                                       \
	_REQUIRE_ARGUMENT(at, var, Object, an object)
#define REQUIRE_ARGUMENT_FUNCTION(at, var)                                     \
	_REQUIRE_ARGUMENT(at, var, Function, a function)

#define REQUIRE_DATABASE_OPEN(db)                                              \
	if (!db->open)                                                             \
		return ThrowTypeError("The database connection is not open")
#define REQUIRE_DATABASE_NOT_BUSY(db)                                          \
	if (db->busy)                                                              \
		return ThrowTypeError("This database connection is busy executing a query")
#define REQUIRE_DATABASE_NO_ITERATORS(db)                                      \
	if (db->iterators)                                                         \
		return ThrowTypeError("This database connection is busy executing a query")
#define REQUIRE_DATABASE_NO_ITERATORS_UNLESS_UNSAFE(db)                        \
	if (!db->unsafe_mode) {                                                    \
		REQUIRE_DATABASE_NO_ITERATORS(db);                                     \
	} ((void)0)
#define REQUIRE_STATEMENT_NOT_LOCKED(stmt)                                     \
	if (stmt->locked)                                                          \
		return ThrowTypeError("This statement is busy executing a query")

#define first() 0
#define second() 1
#define third() 2
#define fourth() 3
#define fifth() 4
#define sixth() 5
#define seventh() 6
#define eighth() 7
#define ninth() 8
#define tenth() 9
