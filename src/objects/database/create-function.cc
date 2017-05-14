// .register([object options], function implementation) -> this

NAN_METHOD(Database::CreateFunction) {
	REQUIRE_ARGUMENT_FUNCTION(0, func);
	REQUIRE_ARGUMENT_STRING(1, nameString);
	REQUIRE_ARGUMENT_NUMBER(2, argCount);
	REQUIRE_ARGUMENT_BOOLEAN(3, aggregate);
	REQUIRE_ARGUMENT_BOOLEAN(4, deterministic);
	REQUIRE_ARGUMENT_BOOLEAN(5, default_safe_integers);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (!db->open) {
		return Nan::ThrowTypeError("The database connection is not open.");
	}
	if (db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query.");
	}
	
	Nan::Utf8String name(nameString);
	int argc = static_cast<int>(argCount);
	int mask = deterministic ? SQLITE_UTF8 | SQLITE_DETERMINISTIC : SQLITE_UTF8;
	bool safe_integers = db->safe_ints;
	void (*xFunc)(sqlite3_context*, int, sqlite3_value**) = NULL;
	void (*xStep)(sqlite3_context*, int, sqlite3_value**) = NULL;
	void (*xFinal)(sqlite3_context*) = NULL;
	
	if (!default_safe_integers) {
		REQUIRE_ARGUMENT_BOOLEAN(6, safe_ints);
		safe_integers = safe_ints;
	}
	if (!aggregate) {
		xFunc = Database::ExecuteFunction;
	} else {
		xStep = Database::StepAggregate;
		xFinal = Database::FinishAggregate;
	}
	
	int status = sqlite3_create_function_v2(db->db_handle, *name, argc, mask, new FunctionInfo(db, func, *name, argc, safe_integers), xFunc, xStep, xFinal, FunctionInfo::DestroyFunction);
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to register SQL function (", sqlite3_errmsg(db->db_handle), ").");
		return Nan::ThrowError(message.c_str());
	}
	
	info.GetReturnValue().Set(info.This());
}
