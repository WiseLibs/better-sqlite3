// Binds each value in the given object. Each parameter bound with this method
// is considered to be named.
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is the number of
// parameters that were bound. Unlike the normal Binder, this will bind
// parameters to all handles, not just the current one.

unsigned int MultiBinder::BindObject(v8::Local<v8::Object> obj) {
	// Get array of properties.
	Nan::MaybeLocal<v8::Array> maybeKeys = Nan::GetPropertyNames(obj);
	if (maybeKeys.IsEmpty()) {
		error = "An error was thrown while trying to get the property names of the given object.";
		return 0;
	}
	v8::Local<v8::Array> keys = maybeKeys.ToLocalChecked();
	
	// Get property count.
	unsigned int len = keys->Length();
	unsigned int bound_count = 0;
	
	// Save current handle.
	sqlite3_stmt* current_handle = handle;
	
	// Loop through each property.
	for (unsigned int i=0; i<len; ++i) {
		
		// Get current property name.
		Nan::MaybeLocal<v8::Value> maybeKey = Nan::Get(keys, i);
		if (maybeKey.IsEmpty()) {
			error = "An error was thrown while trying to get the property names of the given object.";
			return bound_count;
		}
		v8::Local<v8::Value> key = maybeKey.ToLocalChecked();
		
		// If this property is a symbol, ignore it.
		if (key->IsSymbol()) {
			continue;
		}
		
		// Get the current property value.
		Nan::MaybeLocal<v8::Value> maybeValue = Nan::Get(obj, key);
		if (maybeValue.IsEmpty()) {
			error = "An error was thrown while trying to get property values of the given object.";
			return bound_count;
		}
		v8::Local<v8::Value> value = maybeValue.ToLocalChecked();
		
		// Dissect the property name.
		Nan::Utf8String utf8(key);
		const char* utf8_value = *utf8;
		int utf8_length = utf8.length();
		
		
		bool someoneHadNamedParameter = false;
		
		
		// Loop through each handle.
		for (unsigned int h=0; h<handle_count; ++h) {
			handle = handles[h];
			
			// Get the parameter index of the current named parameter.
			unsigned int index = GetNamedParameterIndex(utf8_value, utf8_length);
			if (index) {
				
				// Bind value.
				BindValue(value, index);
				if (error) {
					return bound_count;
				}
				++bound_count;
				
				if (!someoneHadNamedParameter) {
					someoneHadNamedParameter = true;
				}
			}
			
		}
		
		
		// If no handles had this named parameter, provide an error.
		if (!someoneHadNamedParameter) {
			error = "The named parameter \"%s\" does not exist.";
			error_extra = new char[utf8_length + 1];
			strlcpy(error_extra, utf8_value, utf8_length + 1);
			return bound_count;
		}
	}
	
	handle = current_handle;
	return bound_count;
}
