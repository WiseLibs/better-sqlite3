// .get(Function callback) -> this

NAN_METHOD(Statement::Get) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, func);
	WORKER_START(stmt, statement);
	GetWorker* worker = new GetWorker(stmt, new Nan::Callback(func));
	WORKER_BIND(stmt, worker, info, func_index, STATEMENT_BIND, statement);
	WORKER_END(stmt, worker);
}
