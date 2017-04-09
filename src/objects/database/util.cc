// .defaultSafeIntegers(boolean) -> this
NAN_METHOD(Database::DefaultSafeIntegers) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		db->safe_ints = true;
	} else {
		db->safe_ints = false;
	}
	
	info.GetReturnValue().Set(info.This());
}

// get .open -> boolean
NAN_GETTER(Database::Open) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Database>(info.This())->open);
}

bool Database::HandleJavaScriptError() {
	if (was_js_error) {
		Nan::ThrowError(Nan::New(jsError));
		jsError.Reset();
		was_js_error = false;
		return true;
	}
	return false;
}
