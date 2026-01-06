class CustomAggregate : public CustomFunction {
public:

	explicit CustomAggregate(
		v8::Isolate* isolate,
		Database* db,
		const char* name,
		v8::Local<v8::Value> start,
		v8::Local<v8::Function> step,
		v8::Local<v8::Value> inverse,
		v8::Local<v8::Value> result,
		bool safe_ints
	) :
		CustomFunction(isolate, db, name, step, safe_ints),
		invoke_result(result->IsFunction()),
		invoke_start(start->IsFunction()),
		inverse(isolate, inverse->IsFunction() ? inverse.As<v8::Function>() : v8::Local<v8::Function>()),
		result(isolate, result->IsFunction() ? result.As<v8::Function>() : v8::Local<v8::Function>()),
		start(isolate, start) {}

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

	static inline void xStepBase(sqlite3_context* invocation, int argc, sqlite3_value** argv, const v8::Global<v8::Function> CustomAggregate::*ptrtm) {
		AGGREGATE_START();

		v8::Local<v8::Value> args_fast[5];
		v8::Local<v8::Value>* args = argc <= 4 ? args_fast : ALLOC_ARRAY<v8::Local<v8::Value>>(argc + 1);
		args[0] = acc->value.Get(isolate);
		if (argc != 0) Data::GetArgumentsJS(isolate, args + 1, argv, argc, self->safe_ints);

		v8::MaybeLocal<v8::Value> maybeReturnValue = (self->*ptrtm).Get(isolate)->Call(OnlyContext, v8::Undefined(isolate), argc + 1, args);
		if (args != args_fast) delete[] args;

		if (maybeReturnValue.IsEmpty()) {
			self->PropagateJSError(invocation);
		} else {
			v8::Local<v8::Value> returnValue = maybeReturnValue.ToLocalChecked();
			if (!returnValue->IsUndefined()) acc->value.Reset(isolate, returnValue);
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

		v8::Local<v8::Value> result = acc->value.Get(isolate);
		if (self->invoke_result) {
			v8::MaybeLocal<v8::Value> maybeResult = self->result.Get(isolate)->Call(OnlyContext, v8::Undefined(isolate), 1, &result);
			if (maybeResult.IsEmpty()) {
				self->PropagateJSError(invocation);
				return;
			}
			result = maybeResult.ToLocalChecked();
		}

		Data::ResultValueFromJS(isolate, invocation, result, self);
		if (is_final) DestroyAccumulator(invocation);
	}

	struct Accumulator { public:
		v8::Global<v8::Value> value;
		bool initialized;
		bool is_window;
	};

	Accumulator* GetAccumulator(sqlite3_context* invocation) {
		Accumulator* acc = static_cast<Accumulator*>(sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
		if (!acc->initialized) {
			assert(acc->value.IsEmpty());
			acc->initialized = true;
			if (invoke_start) {
				v8::MaybeLocal<v8::Value> maybeSeed = start.Get(isolate).As<v8::Function>()->Call(OnlyContext, v8::Undefined(isolate), 0, NULL);
				if (maybeSeed.IsEmpty()) PropagateJSError(invocation);
				else acc->value.Reset(isolate, maybeSeed.ToLocalChecked());
			} else {
				assert(!start.IsEmpty());
				acc->value.Reset(isolate, start);
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
	const v8::Global<v8::Function> inverse;
	const v8::Global<v8::Function> result;
	const v8::Global<v8::Value> start;
};
