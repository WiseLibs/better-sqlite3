// Increments anon_index until it is out of range, or a nameless parameter
// index is reached. The resulting index is returned. Unlike the normal
// Binder, this also loops through all handles.

int MultiBinder::NextAnonIndex() {
startloop:
	while (sqlite3_bind_parameter_name(handle, ++anon_index) != NULL) {}
	if (anon_index > param_count) {
		while (handle_index + 1 < handle_count) {
			handle = handles[++handle_index];
			param_count = sqlite3_bind_parameter_count(handle);
			if (param_count != 0) {
				anon_index = 1;
				param_count_sum += param_count;
				if (sqlite3_bind_parameter_name(handle, anon_index) == NULL) {
					break;
				}
				goto startloop;
			}
		}
	}
	return anon_index;
}
