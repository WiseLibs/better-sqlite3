class AggregateInfo { public:
	Nan::Persistent<v8::Object> generator;
	Nan::Persistent<v8::Function> next;
	Nan::Persistent<v8::Function> callback;
	bool has_handles;
	bool done;
	
	// Attempts to initialize the handles and set has_handles to true.
	// If something goes wrong, all handles are released, has_handles remains
	// false, and a proper sqlite3 error is thrown.
	void Init(sqlite3_context* ctx, FunctionInfo* function_info, v8::Local<v8::Function> genFunc, int argc) {
		v8::Local<v8::Object> generatorObject = v8::Local<v8::Object>::Cast(genFunc->Call(Nan::GetCurrentContext(), Nan::Null(), 0, NULL).ToLocalChecked());
		v8::Local<v8::Function> nextFunction = v8::Local<v8::Function>::Cast(Nan::Get(generatorObject, NEW_INTERNAL_STRING_FAST("next")).ToLocalChecked());
		generator.Reset(generatorObject);
		next.Reset(nextFunction);
		
		Nan::MaybeLocal<v8::Value> maybe_yielded_value = GetNextValue();
		if (maybe_yielded_value.IsEmpty()) {
			return ThrowJSError(ctx, function_info);
		}
		v8::Local<v8::Value> yieldedValue = maybe_yielded_value.ToLocalChecked();
		if (done || !yieldedValue->IsFunction()) {
			return ThrowError(ctx, "Custom aggregate \"", function_info->name, "\" did not yield a function.");
		}
		v8::Local<v8::Function> callbackFunction = v8::Local<v8::Function>::Cast(yieldedValue);
		
		if (argc != -1) {
			Nan::MaybeLocal<v8::Value> maybe_length = Nan::Get(callbackFunction, NEW_INTERNAL_STRING_FAST("length"));
			if (maybe_length.IsEmpty()) {
				return ThrowJSError(ctx, function_info);
			}
			v8::Local<v8::Value> localLength = maybe_length.ToLocalChecked();
			if (!localLength->IsInt32() || argc != v8::Local<v8::Int32>::Cast(localLength)->Value()) {
				return ThrowError(ctx, "Wrong number of arguments passed to custom aggregate \"", function_info->name, "\".");
			}
		}
		
		callback.Reset(callbackFunction);
		has_handles = true;
	}
	
	// Releases handles, sets has_handles to false, and throws an sqlite3 error.
	inline void ThrowError(sqlite3_context* ctx, const char* a, const char* b, const char* c) {
		Release();
		CONCAT3(message, a, b, c);
		sqlite3_result_error(ctx, message.c_str(), -1);
	}
	// Releases handles, sets has_handles to false, and throws a JS error.
	inline void ThrowJSError(sqlite3_context* ctx, FunctionInfo* function_info) {
		Release();
		function_info->db->was_js_error = true;
		sqlite3_result_error(ctx, "", 0);
	}
	
	// Releases handles and sets has_handles to false
	inline void Release() {
		generator.Reset();
		next.Reset();
		callback.Reset();
		has_handles = false;
	}
	
	// Returns true if the object has no valid handles.
	inline bool isEmpty() {
		return !has_handles;
	}
	
	// Gets the next yield/return value from the generator, and returns it
	// as a Nan::MaybeLocal<v8::Value>. Additionally, done is set appropriately.
	// This method should not be invoked if isEmpty() == true.
	Nan::MaybeLocal<v8::Value> GetNextValue() {
		Nan::MaybeLocal<v8::Value> maybe_entry = Nan::Call(Nan::New(next), Nan::New(generator), 0, NULL);
		if (maybe_entry.IsEmpty()) {return maybe_entry;}
		v8::Local<v8::Object> entry = v8::Local<v8::Object>::Cast(maybe_entry.ToLocalChecked());
		done = Nan::Get(entry, NEW_INTERNAL_STRING_FAST("done")).ToLocalChecked()->BooleanValue();
		return Nan::Get(entry, NEW_INTERNAL_STRING_FAST("value")).ToLocalChecked();
	}
};

void StepAggregate(sqlite3_context* ctx, int length, sqlite3_value** values) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(sqlite3_aggregate_context(ctx, sizeof(AggregateInfo)));
	if (agg_info->IsEmpty()) { // This will be true on the first invocation.
		Nan::HandleScope scope;
		agg_info->Init(ctx, function_info, Nan::New(function_info->handle), function_info->state & VARARGS ? -1 : length);
		if (agg_info->IsEmpty()) {return;} // An error was thrown, so abort.
	}
	// If the callback ever throws as error, we must additionally invoke
	// agg_info->Release() to release its handles so FinishAggregate can
	// determine that an error was thrown.
	EXECUTE_FUNCTION(_v, function_info, Nan::New(agg_info->callback), agg_info->Release());
}

void FinishAggregate(sqlite3_context* ctx) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(sqlite3_aggregate_context(ctx, 0));
	bool no_rows = false;
	if (agg_info == NULL) {
		agg_info = new AggregateInfo;
		if (!agg_info->Init(ctx, function_info, Nan::New(function_info->handle), -1)) {
			delete agg_info;
			return;
		}
		no_rows = true;
	} else if (agg_info->generator.IsEmpty()) {
		return;
	}
	
	Nan::MaybeLocal<v8::Value> maybe_result = agg_info->GetNextValue();
	if (maybe_result.IsEmpty()) {
		agg_info->ThrowJSError(ctx, function_info);
		if (no_rows) {delete agg_info;}
		return;
	}
	if (!agg_info->done) {
		agg_info->ThrowError(ctx, "Custom aggregate \"", function_info->name, "\" should only yield once.");
		if (no_rows) {delete agg_info;}
		return;
	}
	agg_info->Release();
	if (no_rows) {delete agg_info;}
	Data::ResultValueFromJS(ctx, maybe_result.ToLocalChecked(), function_info->name);
}
