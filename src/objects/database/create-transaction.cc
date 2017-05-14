// .transaction(Array sqls) -> Transaction

NAN_METHOD(Database::CreateTransaction) {
	REQUIRE_ARGUMENT_ARRAY(0, sources);
	
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (!db->open) {
		return Nan::ThrowTypeError("The database connection is not open");
	}
	if (db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query");
	}
	if (db->readonly) {
		return Nan::ThrowTypeError("This operation is not available while in readonly mode");
	}
	
	unsigned int len = sources->Length();
	if (!(len > 0)) {
		return Nan::ThrowRangeError("No SQL statements were provided");
	}
	if (len > max_transaction_length) {
		return Nan::ThrowRangeError("Too many SQL statements were provided");
	}
	
	// Get the values of each source string.
	SQLRope rope(len);
	for (unsigned int i=0; i<len; ++i) {
		Nan::MaybeLocal<v8::Value> maybeValue = Nan::Get(sources, i);
		if (maybeValue.IsEmpty()) {
			return;
		}
		v8::Local<v8::Value> value = maybeValue.ToLocalChecked();
		if (!value->IsString()) {
			return Nan::ThrowTypeError("Expected each item in the given array to be a string");
		}
		rope.Push(v8::Local<v8::String>::Cast(value));
	}
	
	// Join the source strings together.
	size_t joined_length = rope.GetConcatLength();
	const uint16_t* joined_sources = rope.Concat(joined_length);
	v8::Local<v8::String> joinedSources = v8::String::NewFromTwoByte(info.GetIsolate(), joined_sources, v8::NewStringType::kNormal, joined_length).ToLocalChecked();
	delete[] joined_sources;
	
	
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
		v8::String::Value* source = rope.Get(i);
		int utf16_length = source->length();
		const uint16_t* utf16 = **source;
		
		const void* tail;
		int status = sqlite3_prepare16_v2(db->db_handle, utf16, utf16_length * sizeof(uint16_t) + 1, &(trans->handles[i]), &tail);
		
		// Validates the newly created statement.
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct SQL statement (", sqlite3_errmsg(db->db_handle), ")");
			return Nan::ThrowError(message.c_str());
		}
		if (trans->handles[i] == NULL) {
			return Nan::ThrowTypeError("One of the supplied SQL strings contains no statements");
		}
		if (tail != (const void*)(utf16 + utf16_length)) {
			return Nan::ThrowRangeError("Each provided string may only contain a single SQL statement");
		}
		if (sqlite3_stmt_readonly(trans->handles[i])) {
			return Nan::ThrowTypeError("Transactions cannot contain read-only statements");
		}
	}
	Nan::ForceSet(transaction, NEW_INTERNAL_STRING_FAST("source"), joinedSources, FROZEN);
	Nan::ForceSet(transaction, NEW_INTERNAL_STRING_FAST("database"), info.This(), FROZEN);
	if (db->safe_ints) {trans->state |= SAFE_INTS;}
	
	// Pushes onto transs set.
	trans->extras->id = NEXT_TRANSACTION_ID++;
	db->transs.insert(db->transs.end(), trans);
	
	info.GetReturnValue().Set(transaction);
}
