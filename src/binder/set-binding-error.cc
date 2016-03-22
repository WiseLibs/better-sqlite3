void Binder::SetBindingError(int status) {
	if (status != SQLITE_OK) {
		switch (status) {
			case SQLITE_RANGE:
				error = "Too many parameters were provided.";
				break;
			case SQLITE_TOOBIG:
				error = "The bound string or Buffer is too big.";
				break;
			case SQLITE_NOMEM:
				error = "Out of memory.";
				break;
			default:
				error = "An unexpected error occured while trying to bind parameters.";
		}
	}
}
