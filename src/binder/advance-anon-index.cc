// Increments anon_index until it is out of range, or a nameless parameter
// index is reached. It is incremented at least once.

void Binder::AdvanceAnonIndex() {
	while (sqlite3_bind_parameter_name(++anon_index) != NULL) {}
}
