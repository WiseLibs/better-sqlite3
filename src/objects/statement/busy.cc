// get .busy -> boolean

NAN_GETTER(Statement::Busy) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Statement>(info.This())->busy);
}
