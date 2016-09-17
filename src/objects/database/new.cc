// new Database(string filename)

NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENT_STRING(0, filename);
	REQUIRE_ARGUMENT_STRING(1, filenameGiven);
	REQUIRE_ARGUMENT_BOOLEAN(2, inMemory);
	
	Database* db = new Database();
	db->Wrap(info.This());
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("memory"), inMemory ? Nan::True() : Nan::False(), FROZEN);
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("name"), filenameGiven, FROZEN);
	
	db->Ref();
	db->workers += 1;
	Nan::AsyncQueueWorker(new OpenWorker(db, C_STRING(filename)));
	
	info.GetReturnValue().Set(info.This());
}
