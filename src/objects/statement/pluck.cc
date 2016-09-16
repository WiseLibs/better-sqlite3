// .pluck() -> this

NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("The pluck() method can only be used by read-only statements.");
	}
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		stmt->state |= PLUCK_COLUMN;
	} else {
		stmt->state &= ~PLUCK_COLUMN;
	}
	
	info.GetReturnValue().Set(info.This());
}
