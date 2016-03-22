void Binder::BindNumber(v8::Local<v8::Number> value, int index = 0) {
	if (!index) {index = anon_index;}
	AdvanceAnonIndex();
	int status = sqlite3_bind_double(handle, index, value->Value());
	SetBindingError(status);
}
