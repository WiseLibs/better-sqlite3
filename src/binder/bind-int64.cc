// Attempts to bind an Int64 to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindInt64(Int64* int64, int index) {
	if (!index) {index = NextAnonIndex();}
	int status = sqlite3_bind_int64(handle, index, int64->GetValue());
	SetBindingError(status);
}
