// Returns a pointer to an error string, if an error occured. Otherwise, NULL.
// The underlying memory is destroyed when the Binder instance if destroyed.

const char* Binder::GetError() {
	if (!error) {return NULL;}
	if (!error_extra) {return error;}
	if (error_full) {return error_full;}
	
	int len = strlen(error) + strlen(error_extra) - 2;
	error_full = new const char[len + 1];
	snprintf(const_cast<char*>(full), len, error, error_extra);
	
	return error_full;
}
