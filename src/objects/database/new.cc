bool OPEN_RIGHT_AWAY = true;

// new Database(string filename, [object options]) -> Database

NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENT_STRING(0, filename);
	REQUIRE_ARGUMENT_STRING(1, filenameGiven);
	REQUIRE_ARGUMENT_BOOLEAN(2, inMemory);
	
	Database* db = new Database();
	db->Wrap(info.This());
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("memory"), inMemory ? Nan::True() : Nan::False(), FROZEN);
	Nan::ForceSet(info.This(), NEW_INTERNAL_STRING_FAST("name"), filenameGiven, FROZEN);
	
	if (OPEN_RIGHT_AWAY) {
		char* fname = C_STRING(filename);
		int status = db->OpenHandles(fname);
		delete[] fname;
		if (status != SQLITE_OK) {
			CONCAT2(message, "SQLite: ", sqlite3_errmsg(db->db_handle));
			db->CloseHandles();
			Nan::ThrowError(message.c_str());
			return;
		}
		db->state = DB_READY;
	}
	
	info.GetReturnValue().Set(info.This());
}

// Database.openAsync(string filename, [object options]) -> Promise

NAN_METHOD(Database::OpenAsync) {
	if (info.Length() < 3) {
		return Nan::ThrowTypeError("Expected to receive at least 3 arguments.");
	}
	
	OPEN_RIGHT_AWAY = false;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
	v8::Local<v8::Value> args[3] = {info[0], info[1], info[2]};
	v8::Local<v8::Object> database = Nan::NewInstance(cons, 3, args).ToLocalChecked();
	OPEN_RIGHT_AWAY = true;
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(database);
	v8::Local<v8::Promise::Resolver> resolver = v8::Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
	
	db->Ref();
	OpenWorker* worker = new OpenWorker(db, C_STRING(v8::Local<v8::String>::Cast(info[0])));
	worker->SaveToPersistent((uint32_t)0, resolver);
	Nan::AsyncQueueWorker(worker);
	
	info.GetReturnValue().Set(resolver->GetPromise());
}
