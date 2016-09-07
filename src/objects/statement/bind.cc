// .bind(...any boundValues) -> this

NAN_METHOD(Statement::Bind) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->state & CONFIG_LOCKED) {
		return Nan::ThrowTypeError("Cannot bind parameters after the statement has been executed.");
	}
	if (stmt->state & BOUND) {
		return Nan::ThrowTypeError("The bind() method can only be invoked once per statement object.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	v8::Local<v8::Object> object = Nan::New<v8::Object>();
	info.This()->SetHiddenValue(Nan::New("_").ToLocalChecked(), object);
	STATEMENT_BIND(stmt, info, info.Length(), object);
	
	stmt->state |= BOUND;
	info.GetReturnValue().Set(info.This());
}
