// .pluck(boolean pluckFirstRow) -> this

NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("The pluck() method can only be used by read-only statements.");
	}
	REQUIRE_ARGUMENT_BOOLEAN(0, value);
	if (stmt->config_locked) {
		return Nan::ThrowTypeError("A statement's pluck setting cannot be altered after execution.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	stmt->pluck_column = value;
	
	info.GetReturnValue().Set(info.This());
}
