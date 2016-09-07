// new Database(string filename)

NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENT_STRING(0, filename);
	REQUIRE_ARGUMENT_BOOLEAN(1, wal);
	REQUIRE_ARGUMENT_FUNCTION(2, nullFactory);
	Database* db = new Database();
	db->Wrap(info.This());
	info.This()->SetHiddenValue(NEW_INTERNAL_STRING_FAST("NullFactory"), nullFactory);
	
	db->Ref();
	db->workers += 1;
	Nan::AsyncQueueWorker(new OpenWorker(db, C_STRING(filename), wal));
	
	info.GetReturnValue().Set(info.This());
}
