// database.begin() -> Transaction

NAN_METHOD(Transaction::New) {
	if (!CONSTRUCTING_PRIVILEGES) {
		return Nan::ThrowTypeError("Transactions can only be constructed by the db.begin() method.");
	}
	Transaction* trans = new Transaction();
	trans->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}
