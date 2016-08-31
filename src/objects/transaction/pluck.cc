// .pluck(boolean pluckFirstRow) -> this

NAN_METHOD(Transaction::Pluck) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	if (!trans->returns_data) {
		return Nan::ThrowTypeError("The pluck() method can only be used by transactions that return data.");
	}
	REQUIRE_ARGUMENT_BOOLEAN(0, value);
	if (trans->config_locked) {
		return Nan::ThrowTypeError("A transaction's pluck setting cannot be altered after execution.");
	}
	if (trans->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	trans->pluck_column = value;
	
	info.GetReturnValue().Set(info.This());
}
