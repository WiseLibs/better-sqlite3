// .run() -> Promise

NAN_METHOD(Statement::Run) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->readonly) {
		return Nan::ThrowTypeError("This statement is read-only. Use get(), all(), or each() instead.");
	}
	STATEMENT_START(stmt);
	STATEMENT_BIND(info.Length());
	RunWorker* worker = new RunWorker(stmt, _handle, _i);
	STATEMENT_END(stmt, worker);
}
