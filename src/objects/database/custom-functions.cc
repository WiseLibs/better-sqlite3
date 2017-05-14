class FunctionInfo : public Functor { public:
	explicit FunctionInfo(Database* db, v8::Local<v8::Function> func,
		const char* name, int argc, bool safe_integers
	) : handle(func), db(db), name(COPY(name)), argc(argc), safe_integers(safe_integers) {}
	~FunctionInfo() {
		handle.Reset();
		delete[] name;
	}
	void Invoke(void* ctx) {
		CONCAT3(message, "Custom function \"", name, "\" returned an invalid value.");
		Nan::ThrowTypeError(message.c_str());
		db->was_js_error = true;
		sqlite3_result_error(static_cast<sqlite3_context*>(ctx), "", 0);
	}
	static void DestroyFunction(void* x) {
		Nan::HandleScope scope;
		delete static_cast<FunctionInfo*>(x);
	}
	Nan::Persistent<v8::Function> handle;
	Database* db;
	const char* name;
	int argc;
	bool safe_integers;
};

#define EXECUTE_FUNCTION(var, function_info, func, errorAction)                \
	Database* db = function_info->db;                                          \
	v8::Local<v8::Value>* args = Data::GetArgumentsJS(                         \
		values, length, function_info->safe_integers);                         \
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
	Data::ResultValueFromJS(ctx, maybe_return_value.ToLocalChecked(), function_info);
}
