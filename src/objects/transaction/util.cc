// Used by std::set to organize the pointers it holds.
bool Transaction::Compare::operator() (const Transaction* a, const Transaction* b) {
	return a->id < b->id;
}

// Closes all associated sqlite3 handles if the transaction is not busy.
// Returns false if the transaction is busy.
bool Transaction::CloseIfPossible() {
	if (!(state & BUSY)) {
		CloseHandles();
		return true;
	}
	return false;
}

// Removes itself from its database's associated std::set.
void Transaction::EraseFromSet() {
	db->transs.erase(this);
}

// Builds a JavaScript array that has an object for each sqlite3_stmt handle
// that has bind parameters. Each object maps the handle's parameter names
// to their respective parameter index.
void Transaction::BuildBindMap() {
	v8::Local<v8::Function> cons = v8::Local<v8::Function>::Cast(db->handle()->GetHiddenValue(NEW_INTERNAL_STRING_FAST("NullFactory")));
	v8::Local<v8::Object> array = Nan::New<v8::Object>();
	for (unsigned int h=0; h<handle_count; ++h) {
		sqlite3_stmt* handle = handles[h];
		int param_count = sqlite3_bind_parameter_count(handle);
		if (param_count > 0) {
			v8::Local<v8::Object> namedParams = Nan::NewInstance(cons).ToLocalChecked();
			for (int i=1; i<=param_count; ++i) {
				const char* name = sqlite3_bind_parameter_name(handle, i);
				if (name != NULL) {
					Nan::Set(namedParams, NEW_INTERNAL_STRING8(name + 1), Nan::New<v8::Number>((double)i));
				}
			}
			Nan::Set(array, h, namedParams);
		}
	}
	handle()->SetHiddenValue(NEW_INTERNAL_STRING_FAST("bindMap"), array);
}