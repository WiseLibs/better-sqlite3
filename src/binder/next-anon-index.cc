// Increments anon_index until it is out of range, or a nameless parameter
// index is reached. The resulting index is returned.

unsigned int Binder::NextAnonIndex() {
	while (sqlite3_bind_parameter_name(handle, ++anon_index) != NULL) {}
	return anon_index;
}
