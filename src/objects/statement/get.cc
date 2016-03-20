// .get() -> Promise

NAN_METHOD(Statement::Get) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	STATEMENT_START(stmt);
	GetWorker* worker = new GetWorker(stmt, _handle, _i);
	STATEMENT_END(stmt, worker);
}
