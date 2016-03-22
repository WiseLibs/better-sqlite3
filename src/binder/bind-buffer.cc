void Binder::BindBuffer(v8::Local<v8::Object> value, int index = 0) {
	if (!index) {index = anon_index;}
	AdvanceAnonIndex();
	
	int status = sqlite3_bind_text(handle, index, node::Buffer::Data(value), node::Buffer::Length(value), SQLITE_TRANSIENT);
	
	SetBindingError(status);
}
