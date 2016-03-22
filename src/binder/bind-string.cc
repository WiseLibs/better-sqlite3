void Binder::BindString(v8::Local<v8::String> value, int index = 0) {
	if (!index) {index = anon_index;}
	AdvanceAnonIndex();
	
	Nan::Utf8String utf8(value);
	int status = sqlite3_bind_text(handle, index, *utf8, utf8.length(), SQLITE_TRANSIENT);
	
	SetBindingError(status);
}
