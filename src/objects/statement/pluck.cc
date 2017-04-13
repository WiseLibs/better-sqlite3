// .pluck() -> this

NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query.");
	}
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("The pluck() method can only be used by statements that return data.");
	}
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		stmt->state |= PLUCK_COLUMN;
	} else {
		stmt->state &= ~PLUCK_COLUMN;
	}
	
	info.GetReturnValue().Set(info.This());
}
