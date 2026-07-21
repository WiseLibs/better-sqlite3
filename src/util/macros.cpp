#define NODE_ARGUMENTS const Napi::CallbackInfo&
#define NODE_ARGUMENTS_POINTER const Napi::CallbackInfo*
#define NODE_METHOD(name) Napi::Value name(const Napi::CallbackInfo& info)
#define NODE_GETTER(name) Napi::Value name(const Napi::CallbackInfo& info)
#define INIT(name) Napi::Function name(Napi::Env env, Addon* addon)

#define OnlyAddon (static_cast<Addon*>(info.Data()))
#define UseIsolate Napi::Env env = info.Env()
#define UseAddon Addon* addon = static_cast<Addon*>(info.Data())

#define REQUIRE_ARGUMENT_ANY(at, var)                                          \
	if (info.Length() <= (at()))                                               \
		return ThrowTypeError(info.Env(), "Expected a "#at" argument");        \
	var = info[at()]

#define _REQUIRE_ARGUMENT(at, var, Type, message, ...)                         \
	if (info.Length() <= (at()) || !info[at()].Is##Type())                     \
		return ThrowTypeError(info.Env(), "Expected "#at" argument to be "#message); \
	var = (info[at()].As<Napi::Type>())__VA_ARGS__

#define REQUIRE_ARGUMENT_INT32(at, var)                                        \
	if (info.Length() <= (at()) || !IsInt32(info[at()]))                       \
		return ThrowTypeError(info.Env(), "Expected "#at" argument to be a 32-bit signed integer"); \
	var = info[at()].As<Napi::Number>().Int32Value()
#define REQUIRE_ARGUMENT_BOOLEAN(at, var)                                      \
	_REQUIRE_ARGUMENT(at, var, Boolean, a boolean, .Value())
#define REQUIRE_ARGUMENT_STRING(at, var)                                       \
	_REQUIRE_ARGUMENT(at, var, String, a string)
#define REQUIRE_ARGUMENT_OBJECT(at, var)                                       \
	_REQUIRE_ARGUMENT(at, var, Object, an object)
#define REQUIRE_ARGUMENT_FUNCTION(at, var)                                     \
	_REQUIRE_ARGUMENT(at, var, Function, a function)

#define REQUIRE_DATABASE_OPEN(db)                                              \
	if (!db->open)                                                             \
		return ThrowTypeError(info.Env(), "The database connection is not open")
#define REQUIRE_DATABASE_NOT_BUSY(db)                                          \
	if (db->busy)                                                              \
		return ThrowTypeError(info.Env(), "This database connection is busy executing a query")
#define REQUIRE_DATABASE_NO_ITERATORS(db)                                      \
	if (db->iterators)                                                         \
		return ThrowTypeError(info.Env(), "This database connection is busy executing a query")
#define REQUIRE_DATABASE_NO_ITERATORS_UNLESS_UNSAFE(db)                        \
	if (!db->unsafe_mode) {                                                    \
		REQUIRE_DATABASE_NO_ITERATORS(db);                                     \
	} ((void)0)
#define REQUIRE_STATEMENT_NOT_LOCKED(stmt)                                     \
	if (stmt->locked)                                                          \
		return ThrowTypeError(info.Env(), "This statement is busy executing a query")

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
