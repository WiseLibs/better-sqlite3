// Attempts to bind a number to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindNumber(v8::Local<v8::Number> value, int index = 0) {
	if (!index) {index = anon_index;}
	AdvanceAnonIndex();
	int status = sqlite3_bind_double(handle, index, value->Value());
	SetBindingError(status);
}
