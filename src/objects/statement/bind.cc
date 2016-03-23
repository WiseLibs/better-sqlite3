// .bind(...any boundValues) -> this

NAN_METHOD(Statement::Bind) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->config_locked) {
		return Nan::ThrowError("Cannot bind parameters after the statement has been executed.");
	}
	if (stmt->bound) {
		return Nan::ThrowError("The bind() method can only be invoked once per statement object.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	int info_length = info.Length();
	int len = stmt->handles->count;
	for (int i=0; i<len; i++) {
		sqlite3_stmt* handle = stmt->handles->Get(i);
		Binder binder(handle);
		binder.Bind(info, info_length);
		const char* err = binder.GetError();
		if (err) {
			for (; i>=0; i--) {
				sqlite3_clear_bindings(stmt->handles->Get(i));
			}
			return Nan::ThrowError(err);
		}
	}
	
	stmt->bound = true;
	info.GetReturnValue().Set(info.This());
}
