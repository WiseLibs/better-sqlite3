// .bind(...any boundValues) -> this

NAN_METHOD(Transaction::Bind) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	if (!trans->db->open) {
		return Nan::ThrowTypeError("The associated database connection is closed.");
	}
	if (trans->state & CONFIG_LOCKED) {
		return Nan::ThrowTypeError("Cannot bind parameters after the transaction has been executed.");
	}
	if (trans->state & BOUND) {
		return Nan::ThrowTypeError("The bind() method can only be invoked once per transaction object.");
	}
	
	TRANSACTION_BIND(trans, info, info.Length());
	
	trans->state |= BOUND;
	info.GetReturnValue().Set(info.This());
}
