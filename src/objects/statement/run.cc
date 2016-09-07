// .run(Function callback) -> this

NAN_METHOD(Statement::Run) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count != 0) {
		return Nan::ThrowTypeError("This statement is read-only. Use get(), all(), or each() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, func);
	WORKER_START(stmt, statement);
	RunWorker* worker = new RunWorker(stmt, new Nan::Callback(func));
	WORKER_BIND(stmt, worker, info, func_index, STATEMENT_BIND, statement);
	WORKER_END(stmt, worker);
}
