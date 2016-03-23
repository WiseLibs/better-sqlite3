// Given the name of a named parameter, returns the index of the parameter.
// If the named parameter does not exist, 0 is returned.

int Binder::GetNamedParameterIndex(const char* string, int length) {
	int index;
	char temp[length + 2];
	strlcpy(temp + 1, string, length + 1);
	
	temp[0] = '@';
	index = sqlite3_bind_parameter_index(handle, temp);
	if (index) {
		return index;
	}
	
	temp[0] = ':';
	index = sqlite3_bind_parameter_index(handle, temp);
	if (index) {
		return index;
	}
	
	temp[0] = '$';
	index = sqlite3_bind_parameter_index(handle, temp);
	if (index) {
		return index;
	}
	
	return index;
}
