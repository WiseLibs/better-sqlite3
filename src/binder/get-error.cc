// Returns a pointer to an error string, if an error occured. Otherwise, NULL.
// The underlying memory is destroyed when the Binder instance if destroyed.

const char* Binder::GetError() {
	if (!error) {return NULL;}
	if (!error_extra) {return error;}
	if (error_full) {return error_full;}
	
	int len = strlen(error) + strlen(error_extra) - 1;
	error_full = new char[len];
	sqlite3_snprintf(len, const_cast<char*>(error_full), error, error_extra);
	
	return error_full;
}
