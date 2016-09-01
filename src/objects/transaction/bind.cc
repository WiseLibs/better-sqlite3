// .bind(...any boundValues) -> this

NAN_METHOD(Transaction::Bind) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	if (trans->config_locked) {
		return Nan::ThrowTypeError("Cannot bind parameters after the transaction has been executed.");
	}
	if (trans->bound) {
		return Nan::ThrowTypeError("The bind() method can only be invoked once per transaction object.");
	}
	if (trans->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	MultiBinder binder(trans->handles, trans->handle_count);
	binder.Bind(info, info.Length());
	
	const char* err = binder.GetError();
	if (err) {
		for (unsigned int i=0; i<trans->handle_count; ++i) {
			sqlite3_clear_bindings(trans->handles[i]);
		}
		return Nan::ThrowError(err);
	}
	
	trans->bound = true;
	info.GetReturnValue().Set(info.This());
}
