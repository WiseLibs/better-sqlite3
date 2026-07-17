#define STATEMENT_BIND(handle)                                                 \
	Binder binder(handle);                                                     \
	if (!binder.Bind(info, info.Length(), stmt)) {                             \
		sqlite3_clear_bindings(handle);                                        \
		return info.Env().Undefined();                                         \
	} ((void)0)

#define STATEMENT_THROW_LOGIC()                                                \
	db->ThrowDatabaseError(env);                                               \
	if (!bound) { sqlite3_clear_bindings(handle); }                            \
	return env.Undefined()

#define STATEMENT_RETURN_LOGIC(return_value)                                   \
	Napi::Value _return_value = (return_value);                                \
	if (!bound) { sqlite3_clear_bindings(handle); }                            \
	return _return_value

#define STATEMENT_START_LOGIC(RETURNS_DATA_CHECK, MUTATE_CHECK)                \
	Statement* stmt = ::Unwrap<Statement>(info.This());                        \
	RETURNS_DATA_CHECK();                                                      \
	sqlite3_stmt* handle = stmt->handle;                                       \
	Database* db = stmt->db;                                                   \
	REQUIRE_DATABASE_OPEN(db->GetState());                                     \
	REQUIRE_DATABASE_NOT_BUSY(db->GetState());                                 \
	MUTATE_CHECK();                                                            \
	const bool bound = stmt->bound;                                            \
	if (!bound) {                                                              \
		STATEMENT_BIND(handle);                                                \
	} else if (info.Length() > 0) {                                            \
		return ThrowTypeError(info.Env(), "This statement already has bound parameters"); \
	} ((void)0)


#define STATEMENT_THROW() db->GetState()->busy = false; STATEMENT_THROW_LOGIC()
#define STATEMENT_RETURN(x) db->GetState()->busy = false; STATEMENT_RETURN_LOGIC(x)
#define STATEMENT_START(x, y)                                                  \
	STATEMENT_START_LOGIC(x, y);                                               \
	db->GetState()->busy = true;                                               \
	UseIsolate;                                                                \
	if (db->Log(env, handle)) {                                                \
		STATEMENT_THROW();                                                     \
	} ((void)0)


#define DOES_NOT_MUTATE() REQUIRE_STATEMENT_NOT_LOCKED(stmt)
#define DOES_MUTATE()                                                          \
	REQUIRE_STATEMENT_NOT_LOCKED(stmt);                                        \
	REQUIRE_DATABASE_NO_ITERATORS_UNLESS_UNSAFE(db->GetState())
#define DOES_ADD_ITERATOR()                                                    \
	DOES_NOT_MUTATE();                                                         \
	if (db->GetState()->iterators == USHRT_MAX)                                \
		return ThrowRangeError(info.Env(), "Too many active database iterators")
#define REQUIRE_STATEMENT_RETURNS_DATA()                                       \
	if (!stmt->returns_data)                                                   \
		return ThrowTypeError(info.Env(), "This statement does not return data. Use run() instead")
#define ALLOW_ANY_STATEMENT()                                                  \
	((void)0)


#define _FUNCTION_START(type)                                                  \
	type* self = static_cast<type*>(sqlite3_user_data(invocation));            \
	Napi::Env env = self->env;                                                 \
	Napi::HandleScope scope(env)

#define FUNCTION_START()                                                       \
	_FUNCTION_START(CustomFunction)

#define AGGREGATE_START()                                                      \
	_FUNCTION_START(CustomAggregate);                                          \
	Accumulator* acc = self->GetAccumulator(invocation);                       \
	if (acc->value.IsEmpty()) return
