// .close() -> this

NAN_METHOD(Database::Close) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	if (db->state != DB_DONE) {
		if (db->in_each) {
			return Nan::ThrowTypeError("You cannot close a database while it is executing a query.");
		}
		
		if (db->workers++ == 0) {db->Ref();}
		Nan::AsyncQueueWorker(new CloseWorker(db, db->state == DB_CONNECTING));
		
		// This must be after the CloseWorker is created, so the CloseWorker
		// can detect if the database is still connecting.
		db->state = DB_DONE;
	}
	
	info.GetReturnValue().Set(info.This());
}
