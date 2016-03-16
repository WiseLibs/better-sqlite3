// .close() -> this

NAN_METHOD(Database::Close) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	if (db->state != DB_DONE) {
		db->Ref();
		db->workers += 1;
		
		// If there are no open requests on either database handle, close now.
		// Otherwise, the final StatementWorker will invoke ActuallyClose() when
		// it finishes executing.
		if (db->requests == 0) {
			db->ActuallyClose();
		}
		
		// This must be after the ActuallyClose() attempt, so the CloseWorker
		// can detect if the database is still connecting.
		db->state = DB_DONE;
	}
	
	info.GetReturnValue().Set(info.This());
}

void Database::ActuallyClose() {
	Nan::AsyncQueueWorker(new CloseWorker(this, state == DB_CONNECTING));
}
