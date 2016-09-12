// get .busy -> boolean
NAN_GETTER(Statement::Busy) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Statement>(info.This())->state & BUSY ? true : false);
}

// get .readonly -> boolean
NAN_GETTER(Statement::Readonly) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Statement>(info.This())->column_count != 0);
}
