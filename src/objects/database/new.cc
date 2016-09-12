// new Database(string filename)

NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENT_STRING(0, filename);
	REQUIRE_ARGUMENT_STRING(1, filenameGiven);
	REQUIRE_ARGUMENT_FUNCTION(2, nullFactory);
	
	Database* db = new Database();
	db->Wrap(info.This());
	info.This()->SetHiddenValue(NEW_INTERNAL_STRING_FAST("NF"), nullFactory);
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("filename"), filenameGiven, FROZEN);
	
	db->Ref();
	db->workers += 1;
	Nan::AsyncQueueWorker(new OpenWorker(db, C_STRING(filename)));
	
	info.GetReturnValue().Set(info.This());
}
