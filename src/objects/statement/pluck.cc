// .pluck() -> this

NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("The pluck() method can only be used by read-only statements.");
	}
	if (stmt->config_locked) {
		return Nan::ThrowTypeError("A statement's pluck setting cannot be altered after execution.");
	}
	
	stmt->column_count = 1;
	stmt->pluck_column = true;
	
	info.GetReturnValue().Set(info.This());
}
