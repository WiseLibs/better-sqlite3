// Used by std::set to organize the pointers it holds.
bool Statement::Compare::operator() (const Statement* a, const Statement* b) const {
	return a->id < b->id;
}

// Builds a JavaScript object that maps the statement's parameter names with
// the parameter index of each one. After the second invocation, a cached version
// is returned, rather than rebuilding it.
BindMap Statement::GetBindMap() {
	if (!(state & HAS_BIND_MAP)) {
		int param_count = sqlite3_bind_parameter_count(st_handle);
			int capacity = 0;
			bind_pair_count = 0;
			
			for (int i=1; i<=param_count; ++i) {
				const char* name = sqlite3_bind_parameter_name(st_handle, i);
				if (name != NULL) {
					if (bind_pair_count == capacity) {
						bind_pairs = BindMap::Grow(bind_pairs, &capacity);
					}
					bind_pairs[bind_pair_count].name = std::string(name + 1);
					bind_pairs[bind_pair_count].index = i;
					bind_pair_count += 1;
				}
			}
			state |= HAS_BIND_MAP;
	}
	return BindMap(bind_pairs, bind_pair_count);
}

// get .returnsData -> boolean
NAN_GETTER(Statement::ReturnsData) {
	info.GetReturnValue().Set((Nan::ObjectWrap::Unwrap<Statement>(info.This())->state & RETURNS_DATA) ? true : false);
}

// .safeIntegers(boolean) -> this
NAN_METHOD(Statement::SafeIntegers) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->db->busy) {
		return Nan::ThrowTypeError("This database connection is busy executing a query.");
	}
	
	if (info.Length() == 0 || info[0]->BooleanValue() == true) {
		stmt->state |= SAFE_INTS;
	} else {
		stmt->state &= ~SAFE_INTS;
	}
	
	info.GetReturnValue().Set(info.This());
}
