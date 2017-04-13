// Attempts to bind a value to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindValue(v8::Local<v8::Value> value, int index) {
	if (!index) {index = NextAnonIndex();}
	int status = Data::BindValueFromJS(handle, index, value);
	if (status != SQLITE_OK) {
		switch (status) {
			case -1:
				error = "SQLite3 can only bind numbers, strings, Buffers, and null.";
				break;
			case SQLITE_RANGE:
				error = "Too many parameters were provided.";
				break;
			case SQLITE_TOOBIG:
				error = "The bound string or Buffer is too big.";
				break;
			case SQLITE_NOMEM:
				error = "Out of memory.";
				break;
			default:
				error = "An unexpected error occured while trying to bind parameters.";
		}
	}
}
