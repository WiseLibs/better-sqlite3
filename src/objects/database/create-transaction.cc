// .transaction(Array sqls) -> Transaction

NAN_METHOD(Database::CreateTransaction) {
	REQUIRE_ARGUMENT_ARRAY(0, sources);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	unsigned int len = sources->Length();
	v8::Local<v8::Array> trimmedSources = Nan::New<v8::Array>(len);
	
	if (!(len > 0)) {
		return Nan::ThrowTypeError("No SQL statements were provided.");
	}
	
	// Validate and trim source strings.
	v8::Local<v8::String> semicolon = Nan::New(";").ToLocalChecked();
	for (unsigned int i=0; i<len; ++i) {
		Nan::MaybeLocal<v8::Value> maybeValue = Nan::Get(sources, i);
		if (maybeValue.IsEmpty()) {
			return;
		}
		v8::Local<v8::Value> value = maybeValue.ToLocalChecked();
		if (!value->IsString()) {
			return Nan::ThrowTypeError("Expected each item in the given array to be a string.");
		}
		v8::Local<v8::String> source = v8::Local<v8::String>::Cast(value);
		TRIM_STRING(source);
		{
			v8::Local<v8::StringObject> sourceObject = Nan::New<v8::StringObject>(source);  
			v8::Local<v8::Value> charAtArgs[1] = {Nan::New<v8::Number>((double)(source->Length() - 1))};
			INVOKE_METHOD(lastChar, sourceObject, "charAt", 1, charAtArgs);
			if (!lastChar->IsString()) {
				return Nan::ThrowTypeError("Expected String.prototype.charAt to return a string.");
			}
			if (!lastChar->StrictEquals(semicolon)) {
				source = v8::String::Concat(source, semicolon);
			}
		}
		Nan::Set(trimmedSources, i, source);
	}
	
	// Create joined source string.
	v8::Local<v8::Value> joinArgs[1] = {Nan::New("\n").ToLocalChecked()};
	INVOKE_METHOD(joinedSource, trimmedSources, "join", 1, joinArgs)
	if (!joinedSource->IsString()) {
		return Nan::ThrowTypeError("Expected Array.prototype.join to return a string.");
	}
	
	
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Transaction::constructor);
	v8::Local<v8::Object> transaction = cons->NewInstance(0, NULL);
	CONSTRUCTING_PRIVILEGES = false;
	
	// Initializes C++ object properties.
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(transaction);
	trans->db = db;
	trans->handle_count = len;
	trans->handles = new sqlite3_stmt* [len]();
	trans->handle_types = new bool [len]();
	bool readonly = true;
	
	// Create statement handles from each source string.
	for (unsigned int i=0; i<len; ++i) {
		v8::Local<v8::String> source = v8::Local<v8::String>::Cast(Nan::Get(trimmedSources, i).ToLocalChecked());
		Nan::Utf8String utf8(source);
		const char* tail;
		
		LOCK_DB(db->write_handle);
		int status = sqlite3_prepare_v2(db->write_handle, *utf8, utf8.length() + 1, &(trans->handles[i]), &tail);
		
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->write_handle), ").");
			UNLOCK_DB(db->write_handle);
			return Nan::ThrowError(message);
		}
		UNLOCK_DB(db->write_handle);
		if (trans->handles[i] == NULL) {
			return Nan::ThrowTypeError("One of the supplied SQL strings contains no statements.");
		}
		if (tail != *utf8 + utf8.length()) {
			return Nan::ThrowTypeError("Each provided string may only contain a single SQL statement.");
		}
		if ((trans->handle_types[i] = (sqlite3_stmt_readonly(trans->handles[i]) ? false : true))) {
			readonly = false;
		} else if (sqlite3_column_count(trans->handles[i]) < 1) {
			return Nan::ThrowTypeError("You gave a read-only SQL statement that returns no result columns.");
		}
	}
	
	if (readonly) {
		return Nan::ThrowTypeError("Transactions cannot be read-only (use prepared statements instead).");
	}
	
	trans->returns_data = !trans->handle_types[len - 1];
	
	// Initializes JavaScript object properties.
	transaction->SetHiddenValue(Nan::New("database").ToLocalChecked(), info.This());
	Nan::ForceSet(transaction, Nan::New("source").ToLocalChecked(), joinedSource, FROZEN);
	Nan::ForceSet(transaction, Nan::New("returnsData").ToLocalChecked(), trans->returns_data ? Nan::True() : Nan::False(), FROZEN);
	
	// Pushes onto transs list.
	db->transs.Add(trans);
	
	info.GetReturnValue().Set(transaction);
}
