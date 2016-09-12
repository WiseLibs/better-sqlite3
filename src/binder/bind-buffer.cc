// Attempts to bind a Buffer to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindBuffer(v8::Local<v8::Object> value, int index) {
	if (!index) {index = NextAnonIndex();}
	
	int status = sqlite3_bind_blob(handle, index, (void*)node::Buffer::Data(value), node::Buffer::Length(value), bind_type);
	
	SetBindingError(status);
}
