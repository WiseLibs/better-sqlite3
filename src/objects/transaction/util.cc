// Fills the transaction's bind_map and returns a pointer to the bind_map.
// After the first invocation, a cached version is returned, rather than
// rebuilding it.
BindMap* Transaction::GetBindMap() {
	if (!(state & HAS_BIND_MAP)) {
		int capacity = 0;
		BindMap* bind_map = &extras->bind_map;
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		
		for (unsigned int h=0; h<handle_count; ++h) {
			sqlite3_stmt* handle = handles[h];
			int param_count = sqlite3_bind_parameter_count(handle);
			
			for (int i=1; i<=param_count; ++i) {
				const char* name = sqlite3_bind_parameter_name(handle, i);
				if (name != NULL) {
					if (bind_map->length == capacity) {
						bind_map->Grow(isolate, &capacity);
					}
					bind_map->Add(isolate, name + 1, i, h);
				}
			}
		}
		state |= HAS_BIND_MAP;
		return bind_map;
	}
	return &extras->bind_map;
}

// .safeIntegers([boolean state]) -> this
NAN_METHOD(Transaction::SafeIntegers) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	if (trans->db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query");
	}
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		trans->state |= SAFE_INTS;
	} else {
		trans->state &= ~SAFE_INTS;
	}
	
	info.GetReturnValue().Set(info.This());
}
