// .close() -> this

NAN_METHOD(Database::Close) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	if (db->state == DB_DONE) {
		return Nan::ThrowTypeError("This database connection has already been closed.");
	}
	if (db->in_each) {
		return Nan::ThrowTypeError("You cannot close a database while it is executing a query.");
	}
	
	db->state = DB_DONE;
	db->CloseChildHandles();
	if (db->CloseHandles() != SQLITE_OK) {
		return Nan::ThrowError("Failed to successfully close the database connection.");
	}
	
	info.GetReturnValue().Set(info.This());
}

// .closeAsync() -> Promise

NAN_METHOD(Database::CloseAsync) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	v8::Local<v8::Promise::Resolver> resolver = v8::Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
	
	if (db->state == DB_DONE) {
		resolver->Reject(Nan::TypeError("This database connection has already been closed."));
	}
	else if (db->in_each) {
		resolver->Reject(Nan::TypeError("You cannot close a database while it is executing a query."));
	}
	
	else {
		db->state = DB_DONE;
		db->Ref();
		CloseWorker* worker = new CloseWorker(db);
		worker->SaveToPersistent((uint32_t)0, resolver);
		Nan::AsyncQueueWorker(worker);
	}
	
	info.GetReturnValue().Set(resolver->GetPromise());
}
