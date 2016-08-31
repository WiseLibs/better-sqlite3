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
	
	// int info_length = info.Length();
	// int len = trans->handles->count;
	// for (int i=0; i<len; i++) {
	// 	sqlite3_stmt* handle = trans->handles->Get(i);
	// 	Binder binder(handle);
	// 	binder.Bind(info, info_length);
	// 	const char* err = binder.GetError();
	// 	if (err) {
	// 		for (; i>=0; i--) {
	// 			sqlite3_clear_bindings(trans->handles->Get(i));
	// 		}
	// 		return Nan::ThrowError(err);
	// 	}
	// }
	
	trans->bound = true;
	info.GetReturnValue().Set(info.This());
}
