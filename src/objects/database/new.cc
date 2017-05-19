// new Database(string filename, [object options]) -> Database

NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENT_STRING(0, filename);
	REQUIRE_ARGUMENT_STRING(1, filenameGiven);
	REQUIRE_ARGUMENT_BOOLEAN(2, inMemory);
	REQUIRE_ARGUMENT_BOOLEAN(3, readonly);
	
	Database* db = new Database(readonly);
	db->Wrap(info.This());
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("memory"), inMemory ? Nan::True() : Nan::False(), FROZEN);
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("readonly"), readonly ? Nan::True() : Nan::False(), FROZEN);
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("name"), filenameGiven, FROZEN);
	
	v8::String::Utf8Value utf8(filename);
	if (db->OpenHandles(*utf8) != SQLITE_OK) {
		db->ThrowDatabaseError();
		db->CloseHandles();
		return;
	}
	
	info.GetReturnValue().Set(info.This());
}
