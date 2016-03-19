// .all() -> Promise

NAN_METHOD(Statement::All) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	STATEMENT_START(stmt);
	AllWorker* worker = new AllWorker(stmt, _handle, _i, stmt->pluck_column);
	STATEMENT_END(stmt, worker);
}
