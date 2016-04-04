// .cache(number cacheSize) -> this

NAN_METHOD(Statement::Cache) {
	REQUIRE_ARGUMENT_NUMBER(0, number);
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->config_locked) {
		return Nan::ThrowError("A statement's cache cannot be altered after it has been executed.");
	}
	if (stmt->bound) {
		return Nan::ThrowError("A statement's cache cannot be altered after parameters have been bound.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	double numberValue = number->Value();
	if (!IS_POSITIVE_INTEGER(numberValue)) {
		return Nan::ThrowRangeError("Argument 0 must be a positive, finite integer.");
	}
	if (numberValue < 1) {
		numberValue = 1;
	}
	
	HandleManager* handles = new HandleManager(stmt, (int)numberValue);
	
	if (handles->Fill([&stmt] {return stmt->NewHandle();})) {
		delete handles;
		return Nan::ThrowError("SQLite failed to create a prepared statement.");
	}
	
	delete stmt->handles;
	stmt->handles = handles;
	
	info.GetReturnValue().Set(info.This());
}
