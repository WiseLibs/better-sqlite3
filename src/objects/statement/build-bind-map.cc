void Statement::BuildBindMap() {
	int param_count = sqlite3_bind_parameter_count(st_handle);
	v8::Local<v8::Function> cons = v8::Local<v8::Function>::Cast(db->handle()->GetHiddenValue(NEW_INTERNAL_STRING_FAST("NullFactory")));
	v8::Local<v8::Object> namedParams = Nan::NewInstance(cons).ToLocalChecked();
	for (int i=1; i<=param_count; ++i) {
		const char* name = sqlite3_bind_parameter_name(st_handle, i);
		if (name != NULL) {
			Nan::ForceSet(namedParams, NEW_INTERNAL_STRING8(name + 1), Nan::New<v8::Number>((double)i));
		}
	}
	handle()->SetHiddenValue(NEW_INTERNAL_STRING_FAST("bindMap"), namedParams);
}
