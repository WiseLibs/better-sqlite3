// Binds each value in the given object. Each parameter bound with this method
// is considered to be named.
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is the number of
// parameters that were bound.

int Binder::BindObject(v8::Local<v8::Object> obj, BindMap* bindMap) {
	int len = bindMap->length;
	BindPair* pairs = bindMap->pairs;
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	
	for (int i=0; i<len; ++i) {
		v8::Local<v8::String> key = v8::Local<v8::String>::New(isolate, pairs[i].name);
		
		// Check if the named parameter was provided.
		v8::Maybe<bool> has_property = Nan::HasOwnProperty(obj, key);
		if (has_property.IsNothing()) {
			error = COPY("");
			return i;
		}
		if (!has_property.FromJust()) {
			v8::String::Utf8Value param_name(key);
			CONCAT3(message, "Missing named parameter \"", *param_name, "\"");
			error = COPY(message.c_str());
			return i;
		}
		
		// Get the current property value.
		Nan::MaybeLocal<v8::Value> maybeValue = Nan::Get(obj, key);
		if (maybeValue.IsEmpty()) {
			error = COPY("");
			return i;
		}
		
		BindValue(maybeValue.ToLocalChecked(), pairs[i].index);
		if (error) {
			return i;
		}
	}
	
	return len;
}
