// .each(Function callback) -> Promise

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_ARGUMENT_FUNCTION(0, func);
	STATEMENT_START(stmt);
	EachWorker* worker = new EachWorker(stmt, _handle, _i, stmt->pluck_column, new Nan::Callback(func));
	STATEMENT_END(stmt, worker);
}
