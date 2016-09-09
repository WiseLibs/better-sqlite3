// .checkpoint([boolean force], Function callback) -> this

NAN_METHOD(Database::Checkpoint) {
	bool force;
	v8::Local<v8::Function> func;
	if (info.Length() >= 2) {
		TRUTHINESS_OF_ARGUMENT(0, a);
		REQUIRE_ARGUMENT_FUNCTION(1, b);
		force = a;
		func = b;
	} else {
		force = false;
		REQUIRE_ARGUMENT_FUNCTION(0, a);
		func = a;
	}
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	db->Ref();
	db->workers += 1;
	db->checkpoints += 1;
	Nan::AsyncQueueWorker(new CheckpointWorker(db, force, new Nan::Callback(func)));
	
	info.GetReturnValue().Set(info.This());
}
