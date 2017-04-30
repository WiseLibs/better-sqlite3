// .register([object options], function implementation) -> this

class FunctionInfo { public:
	explicit FunctionInfo(Database* db, bool safe_integers, bool varargs,
		const char* func_name, v8::Local<v8::Function> func
	) : handle(func), db(db), name(COPY(func_name)) {
		state = (safe_integers ? SAFE_INTS : 0) | (varargs ? VARARGS : 0);
	}
	~FunctionInfo() {
		handle.Reset();
		delete[] name;
	}
	static void DestroyFunction(void* x) {
		Nan::HandleScope scope;
		delete static_cast<FunctionInfo*>(x);
	}
	Nan::Persistent<v8::Function> handle;
	Database* db;
	const char* name;
	uint8_t state;
};

#define EXECUTE_FUNCTION(var, function_info, func, errorAction)                \
	Database* db = function_info->db;                                          \
	v8::Local<v8::Value>* args = Data::GetArgumentsJS(                         \
		values, length, (function_info->state & SAFE_INTS) != 0);              \
	bool was_busy = db->busy;                                                  \
	db->busy = true;                                                           \
	v8::MaybeLocal<v8::Value> var = func->Call(                                \
		Nan::GetCurrentContext(), Nan::Null(), length, args);                  \
	db->busy = was_busy;                                                       \
	delete[] args;                                                             \
	if (var.IsEmpty()) {                                                       \
		errorAction;                                                           \
		db->was_js_error = true;                                               \
		return sqlite3_result_error(ctx, "", 0);                               \
	}

void ExecuteFunction(sqlite3_context* ctx, int length, sqlite3_value** values) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	EXECUTE_FUNCTION(maybe_return_value, function_info, Nan::New(function_info->handle),);
	Data::ResultValueFromJS(ctx, maybe_return_value.ToLocalChecked(), function_info->name);
}

class AggregateInfo { public:
	Nan::Persistent<v8::Object> generator;
	Nan::Persistent<v8::Function> next;
	Nan::Persistent<v8::Function> callback;
	bool done;
	bool Init(sqlite3_context* ctx, FunctionInfo* function_info, v8::Local<v8::Function> genFunc, int argc) {
		v8::Local<v8::Object> generatorObject = v8::Local<v8::Object>::Cast(genFunc->Call(Nan::GetCurrentContext(), Nan::Null(), 0, NULL).ToLocalChecked());
		v8::Local<v8::Function> nextFunction = v8::Local<v8::Function>::Cast(Nan::Get(generatorObject, NEW_INTERNAL_STRING_FAST("next")).ToLocalChecked());
		generator.Reset(generatorObject);
		next.Reset(nextFunction);
		
		Nan::MaybeLocal<v8::Value> maybe_yielded_value = GetNextValue();
		if (maybe_yielded_value.IsEmpty()) {
			Release();
			function_info->db->was_js_error = true;
			sqlite3_result_error(ctx, "", 0);
			return false;
		}
		v8::Local<v8::Value> yieldedValue = maybe_yielded_value.ToLocalChecked();
		if (done || !yieldedValue->IsFunction()) {
			Release();
			CONCAT3(message, "Custom aggregate \"", function_info->name, "\" did not yield a function.");
			sqlite3_result_error(ctx, message.c_str(), -1);
			return false;
		}
		v8::Local<v8::Function> callbackFunction = v8::Local<v8::Function>::Cast(yieldedValue);
		
		if (argc != -1) {
			Nan::MaybeLocal<v8::Value> maybe_length = Nan::Get(callbackFunction, NEW_INTERNAL_STRING_FAST("length"));
			if (maybe_length.IsEmpty()) {
				Release();
				function_info->db->was_js_error = true;
				sqlite3_result_error(ctx, "", 0);
				return false;
			}
			v8::Local<v8::Value> localLength = maybe_length.ToLocalChecked();
			if (!localLength->IsInt32() || argc != v8::Local<v8::Int32>::Cast(localLength)->Value()) {
				Release();
				CONCAT3(message, "Wrong number of arguments passed to custom aggregate \"", function_info->name, "\".");
				sqlite3_result_error(ctx, message.c_str(), -1);
				return false;
			}
		}
		callback.Reset(callbackFunction);
		done = false;
		return true;
	}
	void Release() {
		generator.Reset();
		next.Reset();
		callback.Reset();
	}
	Nan::MaybeLocal<v8::Value> GetNextValue() {
		Nan::MaybeLocal<v8::Value> maybe_entry = Nan::Call(Nan::New(next), Nan::New(generator), 0, NULL);
		if (maybe_entry.IsEmpty()) {
			return maybe_entry;
		}
		v8::Local<v8::Object> entry = v8::Local<v8::Object>::Cast(maybe_entry.ToLocalChecked());
		done = Nan::Get(entry, NEW_INTERNAL_STRING_FAST("done")).ToLocalChecked()->BooleanValue();
		return Nan::Get(entry, NEW_INTERNAL_STRING_FAST("value")).ToLocalChecked();
	}
};

void StepAggregate(sqlite3_context* ctx, int length, sqlite3_value** values) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(sqlite3_aggregate_context(ctx, sizeof(AggregateInfo)));
	if (agg_info->generator.IsEmpty()) {
		Nan::HandleScope scope;
		if (!agg_info->Init(ctx, function_info, Nan::New(function_info->handle), function_info->state & VARARGS ? -1 : length)) {
			return;
		}
	}
	EXECUTE_FUNCTION(_v, function_info, Nan::New(agg_info->callback), agg_info->Release());
}

void FinishAggregate(sqlite3_context* ctx) {
	Nan::HandleScope scope;
	FunctionInfo* function_info;
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(sqlite3_aggregate_context(ctx, 0));
	bool no_rows;
	if (agg_info == NULL) {
		function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
		agg_info = new AggregateInfo;
		if (!agg_info->Init(ctx, function_info, Nan::New(function_info->handle), -1)) {
			delete agg_info;
			return;
		}
		no_rows = true;
	} else if (agg_info->generator.IsEmpty()) {
		return;
	} else {
		function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
		no_rows = false;
	}
	
	Nan::MaybeLocal<v8::Value> maybe_result = agg_info->GetNextValue();
	bool done = agg_info->done;
	agg_info->Release();
	if (no_rows) {delete agg_info;}
	
	if (maybe_result.IsEmpty()) {
		function_info->db->was_js_error = true;
		return sqlite3_result_error(ctx, "", 0);
	}
	if (!done) {
		CONCAT3(message, "Custom aggregate \"", function_info->name, "\" should only yield once.");
		return sqlite3_result_error(ctx, message.c_str(), -1);
	}
	Data::ResultValueFromJS(ctx, maybe_result.ToLocalChecked(), function_info->name);
}

NAN_METHOD(Database::CreateFunction) {
	REQUIRE_ARGUMENT_FUNCTION(0, func);
	REQUIRE_ARGUMENT_STRING(1, name);
	REQUIRE_ARGUMENT_BOOLEAN(2, deterministic);
	REQUIRE_ARGUMENT_BOOLEAN(3, aggregate);
	REQUIRE_ARGUMENT_BOOLEAN(4, default_safe_integers);
	REQUIRE_ARGUMENT_BOOLEAN(5, varargs);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (!db->open) {
		return Nan::ThrowTypeError("The database connection is not open.");
	}
	if (db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query.");
	}
	
	Nan::Utf8String utf8(name);
	bool safe_integers = db->safe_ints;
	int mask = deterministic ? SQLITE_UTF8 | SQLITE_DETERMINISTIC : SQLITE_UTF8;
	int argc = -1;
	void (*xFunc)(sqlite3_context*, int, sqlite3_value**) = NULL;
	void (*xStep)(sqlite3_context*, int, sqlite3_value**) = NULL;
	void (*xFinal)(sqlite3_context*) = NULL;
	
	if (!utf8.length()) {
		return Nan::ThrowTypeError("Cannot create an SQL function without a name.");
	}
	if (!default_safe_integers) {
		REQUIRE_ARGUMENT_BOOLEAN(6, safe_ints);
		safe_integers = safe_ints;
	}
	if (!aggregate) {
		xFunc = ExecuteFunction;
		if (!varargs) {
			REQUIRE_ARGUMENT_NUMBER(7, arg_count);
			if (!IS_POSITIVE_INTEGER(arg_count)) {
				return Nan::ThrowTypeError("Expected function.length to be a positive integer.");
			}
			if (arg_count > 127.0) {
				return Nan::ThrowTypeError("Cannot create an SQL function with more than 127 arguments.");
			}
			argc = static_cast<int>(arg_count);
		}
	} else {
		xStep = StepAggregate;
		xFinal = FinishAggregate;
	}
	
	int status = sqlite3_create_function_v2(db->db_handle, *utf8, argc, mask, new FunctionInfo(db, safe_integers, varargs, *utf8, func), xFunc, xStep, xFinal, FunctionInfo::DestroyFunction);
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to register SQL function (", sqlite3_errmsg(db->db_handle), ").");
		return Nan::ThrowError(message.c_str());
	}
	
	info.GetReturnValue().Set(info.This());
}
