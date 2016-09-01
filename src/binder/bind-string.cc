// Attempts to bind a string to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindString(v8::Local<v8::String> value, unsigned int index) {
	if (!index) {index = NextAnonIndex();}
	
	Nan::Utf8String utf8(value);
	int status = sqlite3_bind_text(handle, (int)index, *utf8, utf8.length(), SQLITE_TRANSIENT);
	
	SetBindingError(status);
}
