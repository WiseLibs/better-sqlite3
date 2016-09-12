// .bind(...any boundValues) -> this

NAN_METHOD(Transaction::Bind) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	if (trans->state & CONFIG_LOCKED) {
		return Nan::ThrowTypeError("Cannot bind parameters after the transaction has been executed.");
	}
	if (trans->state & BOUND) {
		return Nan::ThrowTypeError("The bind() method can only be invoked once per transaction object.");
	}
	if (trans->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	TRANSACTION_BIND(trans, info, info.Length(), SQLITE_TRANSIENT);
	
	trans->state |= BOUND;
	info.GetReturnValue().Set(info.This());
}
