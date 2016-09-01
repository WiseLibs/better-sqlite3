// Increments anon_index until it is out of range, or a nameless parameter
// index is reached. The resulting index is returned. Unlike the normal
// Binder, this also loops through all handles.

unsigned int MultiBinder::NextAnonIndex() {
	while (sqlite3_bind_parameter_name(handle, ++anon_index) != NULL) {}
	if (anon_index > param_count && handle_index + 1 < handle_count) {
		do {
			handle = handles[++handle_index];
			param_count = sqlite3_bind_parameter_count(handle);
		} while (param_count == 0 && handle_index + 1 < handle_count);
		anon_index = 1;
		param_count_sum += param_count;
	}
	return anon_index;
}
