// database.prepare(...) -> Statement

NAN_METHOD(Statement::New) {
	if (!CONSTRUCTING_PRIVILEGES) {
		return Nan::ThrowTypeError("Statements can only be constructed by the db.prepare() method");
	}
	Statement* stmt = new Statement();
	stmt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}
