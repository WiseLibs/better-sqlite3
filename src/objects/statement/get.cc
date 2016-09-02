// .get(Function callback) -> this

NAN_METHOD(Statement::Get) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, func);
	STATEMENT_START(stmt);
	STATEMENT_BIND(stmt, func_index);
	GetWorker* worker = new GetWorker(stmt, _handle, _i, new Nan::Callback(func));
	STATEMENT_READER_END(stmt, worker);
}
