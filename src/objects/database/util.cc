// .defaultSafeIntegers(boolean) -> this
NAN_METHOD(Database::DefaultSafeIntegers) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	REQUIRE_ARGUMENT_BOOLEAN(0, safe);
	db->safe_ints = safe;
	
	info.GetReturnValue().Set(info.This());
}

// get .open -> boolean
NAN_GETTER(Database::Open) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Database>(info.This())->open);
}
