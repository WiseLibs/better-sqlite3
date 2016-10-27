// new Database(string filename, [object options]) -> Database

NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENT_STRING(0, filename);
	REQUIRE_ARGUMENT_STRING(1, filenameGiven);
	REQUIRE_ARGUMENT_BOOLEAN(2, inMemory);
	
	Database* db = new Database();
	db->Wrap(info.This());
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("memory"), inMemory ? Nan::True() : Nan::False(), FROZEN);
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("name"), filenameGiven, FROZEN);
	
	Nan::Utf8String utf8(filename);
	if (db->OpenHandles(*utf8) != SQLITE_OK) {
		CONCAT2(message, "SQLite: ", sqlite3_errmsg(db->db_handle));
		db->CloseHandles();
		Nan::ThrowError(message.c_str());
		return;
	}
	
	info.GetReturnValue().Set(info.This());
}
