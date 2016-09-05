// .run(Function callback) -> this

NAN_METHOD(Statement::Run) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->readonly) {
		return Nan::ThrowTypeError("This statement is read-only. Use get(), all(), or each() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, func);
	WORKER_START(stmt, info, func_index, STATEMENT_BIND, statement);
	RunWorker* worker = new RunWorker(stmt, new Nan::Callback(func));
	WORKER_END(stmt, worker);
}
