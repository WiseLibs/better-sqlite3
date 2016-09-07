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
	v8::Local<v8::Object> transaction = Nan::NewInstance(cons).ToLocalChecked();
	CONSTRUCTING_PRIVILEGES = false;
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(transaction);
	
	// Initializes C++ object properties.
	trans->db = db;
	trans->handle_count = len;
	trans->handles = new sqlite3_stmt* [len]();
	
	// Create statement handles from each source string.
	for (unsigned int i=0; i<len; ++i) {
		v8::Local<v8::String> source = v8::Local<v8::String>::Cast(Nan::Get(trimmedSources, i).ToLocalChecked());
		v8::String::Value utf16(source);
		const void* tail;
		
		int status = sqlite3_prepare16(db->write_handle, *utf16, utf16.length() * sizeof (uint16_t) + 1, &(trans->handles[i]), &tail);
		
		// Validates the newly created statement.
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errstr(status), ").");
			return Nan::ThrowError(message);
		}
		if (trans->handles[i] == NULL) {
			return Nan::ThrowTypeError("One of the supplied SQL strings contains no statements.");
		}
		if (tail != (const void*)(*utf16 + utf16.length())) {
			return Nan::ThrowTypeError("Each provided string may only contain a single SQL statement.");
		}
		if (sqlite3_stmt_readonly(trans->handles[i])) {
			return Nan::ThrowTypeError("Transactions cannot contain read-only statements.");
		}
	}
	
	// Initializes JavaScript object properties.
	transaction->SetHiddenValue(NEW_INTERNAL_STRING_FAST("database"), info.This());
	Nan::ForceSet(transaction, NEW_INTERNAL_STRING_FAST("source"), joinedSource, FROZEN);
	trans->BuildBindMap();
	
	// Pushes onto transs set.
	trans->id = NEXT_TRANSACTION_ID++;
	db->transs.insert(db->transs.end(), trans);
	
	info.GetReturnValue().Set(transaction);
}
