// .run(Function callback) -> this

NAN_METHOD(Statement::Run) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->readonly) {
		return Nan::ThrowTypeError("This statement is read-only. Use get(), all(), or each() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, func);
	STATEMENT_START(stmt);
	STATEMENT_BIND(stmt, func_index);
	RunWorker* worker = new RunWorker(stmt, _handle, _i, new Nan::Callback(func));
	STATEMENT_END(stmt, worker);
}
