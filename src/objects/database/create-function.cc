// .register([object options], function implementation) -> this

class FunctionInfo { public:
	explicit FunctionInfo(Database* db, bool safe_integers, bool varargs,
		const char* func_name, v8::Local<v8::Function> func
	)
	: db(db), handle(func) {
		state = (safe_integers ? SAFE_INTS : 0) | (varargs ? VARARGS : 0);
		size_t bytes = strlen(func_name) + 1;
		name = new char[bytes];
		strlcpy(const_cast<char*>(name), func_name, bytes);
	}
	~FunctionInfo() {
		delete[] name;
		handle.Reset();
	}
	static void DestroyFunction(void* x) {
		Nan::HandleScope scope;
		delete static_cast<FunctionInfo*>(x);
	}
	Database* db;
	uint8_t state;
	char* name;
	Nan::Persistent<v8::Function> handle;
};

void ExecuteFunction(sqlite3_context* ctx, int length, sqlite3_value** values) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	v8::Local<v8::Function> func = Nan::New(function_info->handle);
	Database* db = function_info->db;
	
	bool was_busy = db->busy;
	v8::Local<v8::Value>* args = Data::GetArgumentsJS(values, length, (function_info->state & SAFE_INTS) != 0);
	
	db->busy = true;
	v8::MaybeLocal<v8::Value> maybe_return_value = func->Call(Nan::Null(), length, args);
	db->busy = was_busy;
	delete[] args;
	
	if (maybe_return_value.IsEmpty()) {
		db->was_js_error = true;
		return sqlite3_result_error(ctx, "", 0);
	}
	Data::ResultValueFromJS(ctx, maybe_return_value.ToLocalChecked(), function_info->name);
}

#define GENERATOR_SUCCESS 0
#define GENERATOR_YIELD 1
#define GENERATOR_JS_ERROR 2
#define GENERATOR_DIDNT_YIELD_FUNCTION_ERROR 3
#define GENERATOR_WRONG_ARG_COUNT_ERROR 4

class AggregateInfo { public:
	Nan::Persistent<v8::Object> generator;
	Nan::Persistent<v8::Function> next;
	Nan::Persistent<v8::Function> callback;
	sqlite3_context* ctx;
	int init(v8::Local<v8::Function> genFunc, int argc) {
		v8::MaybeLocal<v8::Value> maybe_gen_object = genFunc->Call(Nan::Null(), 0, NULL);
		v8::Local<v8::Object> generatorObject = v8::Local<v8::Object>::Cast(maybe_gen_object.ToLocalChecked());
		v8::Local<v8::Function> nextFunction = v8::Local<v8::Function>::Cast(Nan::Get(generatorObject, NEW_INTERNAL_STRING_FAST("next")).ToLocalChecked());
		generator.Reset(generatorObject);
		next.Reset(nextFunction);
		
		v8::Local<v8::Value> yieldedValue;
		int status = getNextValue(&yieldedValue);
		if (status == GENERATOR_JS_ERROR) {
			release();
			return status;
		}
		if (status != GENERATOR_YIELD || !yieldedValue->IsFunction()) {
			release();
			return GENERATOR_DIDNT_YIELD_FUNCTION_ERROR;
		}
		v8::Local<v8::Function> callbackFunction = v8::Local<v8::Function>::Cast(yieldedValue);
		
		if (argc != -1) {
			Nan::MaybeLocal<v8::Value> maybe_length = Nan::Get(callbackFunction, NEW_INTERNAL_STRING_FAST("length"));
			if (maybe_length.IsEmpty()) {
				release();
				return GENERATOR_JS_ERROR;
			}
			v8::Local<v8::Value> localLength = maybe_length.ToLocalChecked();
			if (!localLength->IsInt32()) {
				release();
				return GENERATOR_DIDNT_YIELD_FUNCTION_ERROR;
			}
			if (argc != v8::Local<v8::Int32>::Cast(localLength)->Value()) {
				release();
				return GENERATOR_WRONG_ARG_COUNT_ERROR;
			}
		}
		callback.Reset(callbackFunction);
		return GENERATOR_SUCCESS;
	}
	void release() {
		generator.Reset();
		next.Reset();
		callback.Reset();
	}
	int getNextValue(v8::Local<v8::Value>* valueOut) {
		v8::MaybeLocal<v8::Value> maybe_entry = Nan::New(next)->Call(Nan::New(generator), 0, NULL);
		if (maybe_entry.IsEmpty()) {
			return GENERATOR_JS_ERROR;
		}
		v8::Local<v8::Object> entry = v8::Local<v8::Object>::Cast(maybe_entry.ToLocalChecked());
		*valueOut = Nan::Get(entry, NEW_INTERNAL_STRING_FAST("value")).ToLocalChecked();
		return Nan::Get(entry, NEW_INTERNAL_STRING_FAST("done")).ToLocalChecked()->BooleanValue()
			? GENERATOR_SUCCESS : GENERATOR_YIELD;
	}
};

void StepAggregate(sqlite3_context* ctx, int length, sqlite3_value** values) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(sqlite3_aggregate_context(ctx, sizeof(AggregateInfo)));
	Database* db = function_info->db;
	
	if (agg_info->ctx != ctx) {
		Nan::HandleScope scope;
		int status = agg_info->init(Nan::New(function_info->handle), function_info->state & VARARGS ? -1 : length);
		if (status != GENERATOR_SUCCESS) {
			agg_info->ctx = NULL;
			if (status == GENERATOR_JS_ERROR) {
				db->was_js_error = true;
				return sqlite3_result_error(ctx, "", 0);
			}
			if (status == GENERATOR_DIDNT_YIELD_FUNCTION_ERROR) {
				CONCAT3(message, "Custom aggregate \"", function_info->name, "\" did not yield a function.");
				return sqlite3_result_error(ctx, message.c_str(), -1);
			}
			if (status == GENERATOR_WRONG_ARG_COUNT_ERROR) {
				CONCAT3(message, "Wrong number of arguments passed to custom aggregate \"", function_info->name, "\".");
				return sqlite3_result_error(ctx, message.c_str(), -1);
			}
		}
		agg_info->ctx = ctx;
	}
	v8::Local<v8::Function> func = Nan::New(agg_info->callback);
	
	bool was_busy = db->busy;
	v8::Local<v8::Value>* args = Data::GetArgumentsJS(values, length, (function_info->state & SAFE_INTS) != 0);
	
	db->busy = true;
	v8::MaybeLocal<v8::Value> maybe_return_value = func->Call(Nan::Null(), length, args);
	db->busy = was_busy;
	delete[] args;
	
	if (maybe_return_value.IsEmpty()) {
		agg_info->ctx = NULL;
		agg_info->release();
		db->was_js_error = true;
		return sqlite3_result_error(ctx, "", 0);
	}
}

void FinishAggregate(sqlite3_context* ctx) {
	Nan::HandleScope scope;
	AggregateInfo* agg_info = static_cast<AggregateInfo*>(sqlite3_aggregate_context(ctx, 0));
	if (agg_info == NULL) {
		// TODO
		return sqlite3_result_null(ctx);
	}
	if (agg_info->ctx == NULL) {
		return;
	}
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	
	v8::Local<v8::Value> result;
	int status = agg_info->getNextValue(&result);
	agg_info->release();
	
	if (status != GENERATOR_SUCCESS) {
		if (status == GENERATOR_JS_ERROR) {
			function_info->db->was_js_error = true;
			return sqlite3_result_error(ctx, "", 0);
		}
		if (status == GENERATOR_YIELD) {
			CONCAT3(message, "Custom aggregate \"", function_info->name, "\" should only yield once.");
			return sqlite3_result_error(ctx, message.c_str(), -1);
		}
	}
	Data::ResultValueFromJS(ctx, result, function_info->name);
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
