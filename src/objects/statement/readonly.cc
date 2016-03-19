// get .readonly -> boolean

NAN_GETTER(Statement::Readonly) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	info.GetReturnValue().Set(stmt->readonly == true);
}
