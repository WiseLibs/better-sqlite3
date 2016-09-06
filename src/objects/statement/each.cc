// .each(Function dataHandler, Function callback) -> this

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_LAST_TWO_ARGUMENTS_FUNCTIONS(func_index, func1, func2)
	WORKER_START(stmt, info, func_index, STATEMENT_BIND, statement);
	EachWorker* worker = new EachWorker(stmt, new Nan::Callback(func2), new Nan::Callback(func1));
	WORKER_END(stmt, worker);
}
