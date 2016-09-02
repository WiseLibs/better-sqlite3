// .each(Function callbackForEach, Function callback) -> this

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_LAST_TWO_ARGUMENTS_FUNCTIONS(func_index, func1, func2)
	STATEMENT_START(stmt);
	STATEMENT_BIND(stmt, func_index);
	EachWorker* worker = new EachWorker(stmt, _handle, _i, new Nan::Callback(func2), new Nan::Callback(func1));
	STATEMENT_READER_END(stmt, worker);
}
