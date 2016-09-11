// Attempts to bind a string to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindString(v8::Local<v8::String> value, int index) {
	if (!index) {index = NextAnonIndex();}
	
	int status;
	v8::String::Value utf16(value);
	if (utf16.length() > 1024) {
		persistent->Set((uint32_t)index, value);
		status = sqlite3_bind_text16(handle, index, *utf16, utf16.length() * sizeof (uint16_t), SQLITE_STATIC);
	} else {
		status = sqlite3_bind_text16(handle, index, *utf16, utf16.length() * sizeof (uint16_t), SQLITE_TRANSIENT);
	}
	
	SetBindingError(status);
}
