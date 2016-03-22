// Attempts to bind a Buffer to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindBuffer(v8::Local<v8::Object> value, int index = 0) {
	if (!index) {index = anon_index;}
	AdvanceAnonIndex();
	
	int status = sqlite3_bind_text(handle, index, node::Buffer::Data(value), node::Buffer::Length(value), SQLITE_TRANSIENT);
	
	SetBindingError(status);
}
