class CustomAggregate : public CustomFunction {
public:

	explicit CustomAggregate(
		Napi::Env env,
		Database* db,
		const char* name,
		Napi::Value start,
		Napi::Function step,
		Napi::Value inverse,
		Napi::Value result,
		bool safe_ints
	) :
		CustomFunction(env, db, name, step, safe_ints),
		invoke_result(result.IsFunction()),
		invoke_start(start.IsFunction()),
		inverse(inverse.IsFunction() ? Napi::Persistent(inverse.As<Napi::Function>()) : Napi::FunctionReference()),
		result(result.IsFunction() ? Napi::Persistent(result.As<Napi::Function>()) : Napi::FunctionReference()),
		start(Napi::Persistent(start)) {}

	static void xStep(sqlite3_context* invocation, int argc, sqlite3_value** argv) {
		xStepBase(invocation, argc, argv, &CustomAggregate::fn);
	}

	static void xInverse(sqlite3_context* invocation, int argc, sqlite3_value** argv) {
		xStepBase(invocation, argc, argv, &CustomAggregate::inverse);
	}

	static void xValue(sqlite3_context* invocation) {
		xValueBase(invocation, false);
	}

	static void xFinal(sqlite3_context* invocation) {
		xValueBase(invocation, true);
	}

private:

	static inline void xStepBase(sqlite3_context* invocation, int argc, sqlite3_value** argv, const Napi::FunctionReference CustomAggregate::*ptrtm) {
		AGGREGATE_START();

		napi_value args_fast[5];
		napi_value* args = argc <= 4 ? args_fast : ALLOC_ARRAY<napi_value>(argc + 1);
		args[0] = acc->value.Value();
		if (argc != 0) Data::GetArgumentsJS(env, args + 1, argv, argc, self->safe_ints);

		Napi::Value returnValue = SafeCall(env, (self->*ptrtm).Value(), env.Undefined(), argc + 1, args);
		if (args != args_fast) delete[] args;

		if (env.IsExceptionPending()) {
			self->PropagateJSError(invocation);
		} else {
			if (!returnValue.IsUndefined()) acc->value.Reset(returnValue, 1);
		}
	}

	static inline void xValueBase(sqlite3_context* invocation, bool is_final) {
		AGGREGATE_START();

		if (!is_final) {
			acc->is_window = true;
		} else if (acc->is_window) {
			DestroyAccumulator(invocation);
			return;
		}

		Napi::Value result = acc->value.Value();
		if (self->invoke_result) {
			napi_value arg = result;
			Napi::Value maybeResult = SafeCall(env, self->result.Value(), env.Undefined(), 1, &arg);
			if (env.IsExceptionPending()) {
				self->PropagateJSError(invocation);
				return;
			}
			result = maybeResult;
		}

		Data::ResultValueFromJS(env, invocation, result, self);
		if (is_final) DestroyAccumulator(invocation);
	}

	struct Accumulator { public:
		Napi::Reference<Napi::Value> value;
		bool initialized;
		bool is_window;
	};

	Accumulator* GetAccumulator(sqlite3_context* invocation) {
		Accumulator* acc = static_cast<Accumulator*>(sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
		if (!acc->initialized) {
			assert(acc->value.IsEmpty());
			acc->initialized = true;
			if (invoke_start) {
				Napi::Value maybeSeed = SafeCall(env, start.Value().As<Napi::Function>(), env.Undefined(), 0, NULL);
				if (env.IsExceptionPending()) PropagateJSError(invocation);
				else acc->value.Reset(maybeSeed, 1);
			} else {
				assert(!start.IsEmpty());
				acc->value.Reset(start.Value(), 1);
			}
		}
		return acc;
	}

	static void DestroyAccumulator(sqlite3_context* invocation) {
		Accumulator* acc = static_cast<Accumulator*>(sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
		assert(acc->initialized);
		acc->value.Reset();
	}

	void PropagateJSError(sqlite3_context* invocation) {
		DestroyAccumulator(invocation);
		CustomFunction::PropagateJSError(invocation);
	}

	const bool invoke_result;
	const bool invoke_start;
	const Napi::FunctionReference inverse;
	const Napi::FunctionReference result;
	const Napi::Reference<Napi::Value> start;
};
