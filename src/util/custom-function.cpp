class CustomFunction : protected DataConverter {
public:

	explicit CustomFunction(
		Napi::Env env,
		Database* db,
		const char* name,
		Napi::Function fn,
		bool safe_ints
	) :
		name(name),
		db(db),
		env(env),
		fn(Napi::Persistent(fn)),
		safe_ints(safe_ints) {}

	virtual ~CustomFunction() {}

	static void xDestroy(void* self) {
		delete static_cast<CustomFunction*>(self);
	}

	static void xFunc(sqlite3_context* invocation, int argc, sqlite3_value** argv) {
		FUNCTION_START();

		napi_value args_fast[4];
		napi_value* args = NULL;
		if (argc != 0) {
			args = argc <= 4 ? args_fast : ALLOC_ARRAY<napi_value>(argc);
			Data::GetArgumentsJS(env, args, argv, argc, self->safe_ints);
		}

		Napi::Value returnValue = SafeCall(env, self->fn.Value(), env.Undefined(), argc, args);
		if (args != args_fast) delete[] args;

		if (env.IsExceptionPending()) self->PropagateJSError(invocation);
		else Data::ResultValueFromJS(env, invocation, returnValue, self);
	}

protected:

	void PropagateJSError(sqlite3_context* invocation) {
		assert(db->GetState()->was_js_error == false);
		db->GetState()->was_js_error = true;
		sqlite3_result_error(invocation, "", 0);
	}

	std::string GetDataErrorPrefix() {
		return std::string("User-defined function ") + name + "() returned";
	}

private:
	const std::string name;
	Database* const db;
protected:
	const Napi::Env env;
	const Napi::FunctionReference fn;
	const bool safe_ints;
};
