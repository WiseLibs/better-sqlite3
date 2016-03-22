// Attempts to bind null to the given parameter index.
// If no index is given, the next anonymous index is used.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::BindNull(unsigned int index = 0) {
	if (!index) {index = NextAnonIndex();}
	int status = sqlite3_bind_null(handle, (int)index);
	SetBindingError(status);
}
