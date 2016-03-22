void Binder::BindNull(int index = 0) {
	if (!index) {index = anon_index;}
	AdvanceAnonIndex();
	int status = sqlite3_bind_null(handle, index);
	SetBindingError(status);
}
