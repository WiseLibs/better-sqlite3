class AggregateInfo {
private:
	enum class State { uninitialized = 0, active = 1, released = 2 };
	Nan::Persistent<v8::Object> generator;
	Nan::Persistent<v8::Function> next;
	Nan::Persistent<v8::Function> callback;
	State state;
public:
	// Attempts to initialize the handles, switching to an active state.
	// If something goes wrong, Release() is invoked and an sqlite3 error is
	// thrown.
	void Init(sqlite3_context* ctx, FunctionInfo* function_info) {
		v8HandleScope;
		v8::Local<v8::Function> genFunc = Nan::New(function_info->handle);
		v8::Local<v8::Object> generatorObject = v8::Local<v8::Object>::Cast(genFunc->Call(Nan::GetCurrentContext(), Nan::Null(), 0, NULL).ToLocalChecked());
		v8::Local<v8::Function> nextFunction = v8::Local<v8::Function>::Cast(Nan::Get(generatorObject, NEW_INTERNAL_STRING_FAST("next")).ToLocalChecked());
		generator.Reset(generatorObject);
		next.Reset(nextFunction);
		
		Nan::MaybeLocal<v8::Value> maybe_yielded_value = GetNextValue();
		if (maybe_yielded_value.IsEmpty()) {
			return ThrowJSError(ctx, function_info);
		}
		v8::Local<v8::Value> yieldedValue = maybe_yielded_value.ToLocalChecked();
		if (state == State::released || !yieldedValue->IsFunction()) {
			return ThrowTypeError(ctx, function_info, "Custom aggregate \"", function_info->name, "\" did not yield a function");
		}
		v8::Local<v8::Function> callbackFunction = v8::Local<v8::Function>::Cast(yieldedValue);
		
		int argc = function_info->argc;
		if (argc != -1) {
			Nan::MaybeLocal<v8::Value> maybe_length = Nan::Get(callbackFunction, NEW_INTERNAL_STRING_FAST("length"));
			if (maybe_length.IsEmpty()) {
				return ThrowJSError(ctx, function_info);
			}
			v8::Local<v8::Value> localLength = maybe_length.ToLocalChecked();
			if (!localLength->IsInt32() || argc != v8::Local<v8::Int32>::Cast(localLength)->Value()) {
				return ThrowTypeError(ctx, function_info, "Custom aggregate \"", function_info->name, "\" has an inconsistent function.length");
			}
		}
		
		callback.Reset(callbackFunction);
		state = State::active;
	}
	
	// Throws an sqlite3 error and invokes Release().
	inline void ThrowTypeError(sqlite3_context* ctx, FunctionInfo* function_info, const char* a, const char* b, const char* c) {
		CONCAT3(message, a, b, c);
		Nan::ThrowTypeError(message.c_str());
		ThrowJSError(ctx, function_info);
	}
	inline void ThrowJSError(sqlite3_context* ctx, FunctionInfo* function_info) {
		Release();
		function_info->db->was_js_error = true;
		sqlite3_result_error(ctx, "", 0);
	}
	
	// Releases handles and switches to an inactive state.
	inline void Release() {
		generator.Reset();
		next.Reset();
		callback.Reset();
		state = State::released;
	}
	
	// Returns the state of the object.
	inline bool IsUninitialized() {
		return state == State::uninitialized;
	}
	inline bool IsActive() {
		return state == State::active;
	}
	
	// Returns the callback function stored by the persistent handle.
	// This method should not be invoked if IsActive() != true.
	inline v8::Local<v8::Function> Callback() {
		return Nan::New(callback);
	}
	
	// Gets the next yield/return value from the generator and returns it
	// as a Nan::MaybeLocal<v8::Value>.
	// Additionally, if the generater returned, Release() is invoked.
	// This method should not be invoked if IsActive() != true.
	Nan::MaybeLocal<v8::Value> GetNextValue() {
		Nan::MaybeLocal<v8::Value> maybe_entry = Nan::Call(Nan::New(next), Nan::New(generator), 0, NULL);
		if (maybe_entry.IsEmpty()) {return maybe_entry;}
		v8::Local<v8::Object> entry = v8::Local<v8::Object>::Cast(maybe_entry.ToLocalChecked());
		if (Nan::Get(entry, NEW_INTERNAL_STRING_FAST("done")).ToLocalChecked()->BooleanValue()) {
			Release();
		}
		return Nan::Get(entry, NEW_INTERNAL_STRING_FAST("value")).ToLocalChecked();
	}
};

#define GET_INFO_OBJECTS()                                                     \
	v8HandleScope;                                                             \
	FunctionInfo* function_info = static_cast<FunctionInfo*>(                  \
		sqlite3_user_data(ctx)                                                 \
	);                                                                         \
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(                     \
		sqlite3_aggregate_context(ctx, sizeof(AggregateInfo))                  \
	);                                                                         \
	if (agg_info == NULL) {                                                    \
		Nan::ThrowError("Out of memory");                                      \
		function_info->db->was_js_error = true;                                \
		return sqlite3_result_error(ctx, "", 0);                               \
	}

void Database::StepAggregate(sqlite3_context* ctx, int length, sqlite3_value** values) {
	GET_INFO_OBJECTS();
	if (agg_info->IsUninitialized()) {
		agg_info->Init(ctx, function_info);
		if (!agg_info->IsActive()) {
			return; // Initialization failed and an sqlite3 error was thrown, so abort.
		}
	}
	EXECUTE_FUNCTION(_v, function_info, agg_info->Callback(), agg_info->Release());
}

void Database::FinishAggregate(sqlite3_context* ctx) {
	GET_INFO_OBJECTS();
	if (agg_info->IsUninitialized()) {
		agg_info->Init(ctx, function_info);
	}
	if (!agg_info->IsActive()) {
		return; // An sqlite3 error was thrown either in StepAggregate or just now.
	}
	
	// Get the result value and handle errors appropriately.
	Nan::MaybeLocal<v8::Value> maybe_result = agg_info->GetNextValue();
	if (maybe_result.IsEmpty()) {
		agg_info->ThrowJSError(ctx, function_info);
		return;
	}
	if (agg_info->IsActive()) {
		agg_info->ThrowTypeError(ctx, function_info, "Custom aggregate \"", function_info->name, "\" should only yield once");
		return;
	}
	
	Data::ResultValueFromJS(ctx, maybe_result.ToLocalChecked(), function_info);
}
