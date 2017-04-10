// .register([object options], function implementation) -> this

class FunctionInfo { public:
	explicit FunctionInfo(Database* db, bool safe_integers, const char* func_name, v8::Local<v8::Function> func)
	: db(db), safe_integers(safe_integers), handle(func) {
		size_t bytes = strlen(func_name) + 1;
		name = new char[bytes];
		strlcpy(const_cast<char*>(name), func_name, bytes);
	}
	~FunctionInfo() {
		delete[] name;
		handle.Reset();
	}
	Database* db;
	bool safe_integers;
	const char* name;
	Nan::Persistent<v8::Function> handle;
};

void DestroyFunction(void* x) {
	Nan::HandleScope scope;
	delete static_cast<FunctionInfo*>(x);
}

void ExecuteFunction(sqlite3_context* ctx, int length, sqlite3_value** values) {
	Nan::HandleScope scope;
	FunctionInfo* function_info = static_cast<FunctionInfo*>(sqlite3_user_data(ctx));
	v8::Local<v8::Function> func = Nan::New(function_info->handle);
	Database* db = function_info->db;
	
	bool was_busy = db->busy;
	v8::Local<v8::Value>* args = Data::GetArgumentsJS(values, length, function_info->safe_integers);
	
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

NAN_METHOD(Database::CreateFunction) {
	REQUIRE_ARGUMENT_FUNCTION(0, func);
	REQUIRE_ARGUMENT_STRING(1, name);
	REQUIRE_ARGUMENT_BOOLEAN(2, deterministic);
	REQUIRE_ARGUMENT_BOOLEAN(3, safe_integers);
	REQUIRE_ARGUMENT_BOOLEAN(4, variadic);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (!db->open) {
		return Nan::ThrowTypeError("The database connection is not open.");
	}
	if (db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query.");
	}
	
	Nan::Utf8String utf8(name);
	int mask = deterministic ? SQLITE_UTF8 | SQLITE_DETERMINISTIC : SQLITE_UTF8;
	int argc = -1;
	
	if (!utf8.length()) {
		return Nan::ThrowTypeError("Cannot create an SQL function without a name.");
	}
	
	if (!variadic) {
		REQUIRE_ARGUMENT_NUMBER(5, argCount);
		double arg_count = argCount->Value();
		if (floor(arg_count) != arg_count || arg_count < 0.0) {
			return Nan::ThrowTypeError("Expected function.length to be a positive integer.");
		}
		if (arg_count > 127.0) {
			return Nan::ThrowTypeError("Cannot create an SQL function with more than 127 arguments.");
		}
		argc = static_cast<int>(arg_count);
	}
	
	int status = sqlite3_create_function_v2(db->db_handle, *utf8, argc, mask, new FunctionInfo(db, safe_integers, *utf8, func), ExecuteFunction, NULL, NULL, DestroyFunction);
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to register SQL function (", sqlite3_errmsg(db->db_handle), ").");
		return Nan::ThrowError(message.c_str());
	}
	
	info.GetReturnValue().Set(info.This());
}
