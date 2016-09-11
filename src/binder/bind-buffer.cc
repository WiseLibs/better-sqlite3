// Attempts to bind a Buffer to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindBuffer(v8::Local<v8::Object> value, int index) {
	if (!index) {index = NextAnonIndex();}
	
	int status;
	size_t length = node::Buffer::Length(value);
	if (length > 1024) {
		persistent->Set((uint32_t)index, value);
		status = sqlite3_bind_blob(handle, index, (void*)node::Buffer::Data(value), length, SQLITE_STATIC);
	} else {
		status = sqlite3_bind_blob(handle, index, (void*)node::Buffer::Data(value), length, SQLITE_TRANSIENT);
	}
	
	SetBindingError(status);
}
