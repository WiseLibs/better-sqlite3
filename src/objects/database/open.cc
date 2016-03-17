// get .open -> boolean

NAN_GETTER(Database::Open) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	info.GetReturnValue().Set(db->state == DB_READY);
}
