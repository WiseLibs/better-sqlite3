// .pluck(boolean|number|string option) -> this

NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("The pluck() method can only be used by read-only statements.");
	}
	REQUIRE_ARGUMENTS(1);
	if (stmt->config_locked) {
		return Nan::ThrowError("A statement's pluck setting cannot be altered after it has been executed.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	v8::Local<v8::Value> arg = info[0];
	
	
	// False means don't pluck any columns.
	if (arg->IsFalse()) {
		stmt->pluck_column = -1;
		
		
	} else {
		sqlite3_stmt* handle = stmt->handles->GetFirst();
		int column_count = sqlite3_column_count(handle);
		
		
		// True means pluck the first column.
		if (arg->IsTrue()) {
			if (column_count < 1) {return Nan::ThrowTypeError("This statement does not return any result columns.");}
			stmt->pluck_column = 0;
			
			
		// A number means pluck the column of that index (the first column is 0).
		} else if (arg->IsNumber()) {
			double num = v8::Local<v8::Number>::Cast(arg)->Value();
			if (!IS_POSITIVE_INTEGER(num)) {
				return Nan::ThrowTypeError("Column numbers must be finite, positive integers.");
			}
			if (column_count <= num) {
				const char format[] = "This statement only returns %d result columns.";
				char buffer[sizeof(format) + 64];
				int len = sprintf(buffer, format, column_count);
				return Nan::ThrowTypeError(Nan::New<v8::String>(buffer, len).ToLocalChecked());
			}
			stmt->pluck_column = (int)num;
			
			
		// A string means pluck the column of the given name.
		} else if (arg->IsString()) {
			Nan::Utf8String utf8(v8::Local<v8::String>::Cast(arg));
			const char* str = *utf8;
			int i = 0;
			for (; i<column_count; i++) {
				const char* name = sqlite3_column_name(handle, i);
				if (strcmp(name, str) == 0) {
					stmt->pluck_column = i;
					break;
				}
			}
			if (i == column_count) {
				return Nan::ThrowTypeError("The specified column name is not returned by this statement.");
			}
			
			
		// Any other value is considered an error.
		} else {
			return Nan::ThrowTypeError("You must specify true, false, a column number, or a column name.");
		}
	}
	
	info.GetReturnValue().Set(info.This());
}
