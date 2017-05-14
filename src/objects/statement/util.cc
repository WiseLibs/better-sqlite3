// Fills the statement's bind_map and returns a pointer to the bind_map.
// After the first invocation, a cached version is returned, rather than
// rebuilding it.
BindMap* Statement::GetBindMap() {
	if (!(state & HAS_BIND_MAP)) {
		int param_count = sqlite3_bind_parameter_count(st_handle);
		int capacity = 0;
		BindMap* bind_map = &extras->bind_map;
		
		for (int i=1; i<=param_count; ++i) {
			const char* name = sqlite3_bind_parameter_name(st_handle, i);
			if (name != NULL) {
				if (bind_map->length == capacity) {
					bind_map->Grow(&capacity);
				}
				bind_map->Add(std::string(name + 1), i);
			}
		}
		state |= HAS_BIND_MAP;
		return bind_map;
	}
	return &extras->bind_map;
}

// .pluck([boolean state]) -> this
NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query");
	}
	if (!(stmt->state & RETURNS_DATA)) {
		return Nan::ThrowTypeError("The pluck() method can only be used by statements that return data");
	}
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		stmt->state |= PLUCK_COLUMN;
	} else {
		stmt->state &= ~PLUCK_COLUMN;
	}
	
	info.GetReturnValue().Set(info.This());
}

// .safeIntegers([boolean state]) -> this
NAN_METHOD(Statement::SafeIntegers) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query");
	}
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		stmt->state |= SAFE_INTS;
	} else {
		stmt->state &= ~SAFE_INTS;
	}
	
	info.GetReturnValue().Set(info.This());
}

// get .returnsData -> boolean
NAN_GETTER(Statement::ReturnsData) {
	info.GetReturnValue().Set((Nan::ObjectWrap::Unwrap<Statement>(info.This())->state & RETURNS_DATA) ? true : false);
}
