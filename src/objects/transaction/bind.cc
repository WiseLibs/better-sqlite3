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
	
	TRANSACTION_BIND(trans, info, info.Length());
	
	trans->bound = true;
	info.GetReturnValue().Set(info.This());
}
