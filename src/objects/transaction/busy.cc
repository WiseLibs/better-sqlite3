// get .busy -> boolean

NAN_GETTER(Transaction::Busy) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Transaction>(info.This())->state & BUSY ? true : false);
}
