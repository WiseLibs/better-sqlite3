// Binds each value in the given object. Each parameter bound with this method
// is considered to be named.
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is the number of
// parameters that were bound.

unsigned int Binder::BindObject(v8::Local<v8::Object> obj) {
	// Get array of properties.
	Nan::MaybeLocal<v8::Array> maybeKeys = Nan::GetPropertyNames(obj);
	if (maybeKeys.IsEmpty()) {
		error = "An error was thrown while trying to get the property names of the given object.";
		return 0;
	}
	v8::Local<v8::Array> keys = maybeKeys.ToLocalChecked();
	
	// Get property count.
	unsigned int len = keys->Length();
	unsigned int symbol_count = 0;
	
	// Loop through each property.
	for (unsigned int i=0; i<len; ++i) {
		
		// Get current property name.
		Nan::MaybeLocal<v8::Value> maybeKey = Nan::Get(keys, i);
		if (maybeKey.IsEmpty()) {
			error = "An error was thrown while trying to get the property names of the given object.";
			return i - symbol_count;
		}
		v8::Local<v8::Value> key = maybeKey.ToLocalChecked();
		
		// If this property is a symbol, ignore it.
		if (key->IsSymbol()) {
			++symbol_count;
			continue;
		}
		
		// Get the parameter index of the current named parameter.
		Nan::Utf8String utf8(key);
		int index = GetNamedParameterIndex(*utf8, utf8.length());
		if (!index) {
			error = "The named parameter \"%s\" does not exist.";
			error_extra = new char[utf8.length() + 1];
			strlcpy(error_extra, *utf8, utf8.length() + 1);
			return i - symbol_count;
		}
		
		// Get the current property value.
		Nan::MaybeLocal<v8::Value> maybeValue = Nan::Get(obj, key);
		if (maybeValue.IsEmpty()) {
			error = "An error was thrown while trying to get property values of the given object.";
			return i - symbol_count;
		}
		
		// Bind value.
		BindValue(maybeValue.ToLocalChecked(), (unsigned int)index);
		if (error) {
			return i - symbol_count;
		}
	}
	
	return len - symbol_count;
}
