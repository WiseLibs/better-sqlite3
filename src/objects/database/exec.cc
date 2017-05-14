// .exec(string sql) -> this

NAN_METHOD(Database::Exec) {
	REQUIRE_ARGUMENT_STRING(0, source);
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
	
	// Prepares the SQL string.
	Nan::Utf8String utf8(source);
	char* err;
	
	// Executes the SQL on the database handle.
	sqlite3_exec(db->db_handle, *utf8, NULL, NULL, &err);
	if (err != NULL) {
		db->ThrowError(err);
		return sqlite3_free(err);
	}
	
	info.GetReturnValue().Set(info.This());
}
