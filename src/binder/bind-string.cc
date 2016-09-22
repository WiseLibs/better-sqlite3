// Attempts to bind a string to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindString(v8::Local<v8::String> value, int index) {
	if (!index) {index = NextAnonIndex();}
	
	v8::String::Utf8Value utf8(value);
	int status = sqlite3_bind_text(handle, index, *utf8, utf8.length(), bind_type);
	
	SetBindingError(status);
}
