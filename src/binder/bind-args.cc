// Given the arguments to a JS function, and the length of arguments to loop
// through, binds all values given.
// Named parameters are given by objects (key-value pairs).
// Anonymous parameters are either directly in the arguments object, or in an
// Array (or Array-like object).
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is a number whose
// first bit indicates whether it tried to bind an object, and whose other 31
// bits describe the number of parameters that were bound.

int Binder::BindArgs(Nan::NAN_METHOD_ARGS_TYPE info, int len, Query* query) {
	bool bound_object = false;
	int count = 0;
	
	for (int i=0; i<len; ++i) {
		v8::Local<v8::Value> arg = info[i];
		
		// Arrays
		if (arg->IsArray()) {
			count += BindArray(v8::Local<v8::Array>::Cast(arg));
			if (error) {
				return count;
			}
			continue;
		}
		
		// Objects
		if (arg->IsObject() && !node::Buffer::HasInstance(arg)) {
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(arg);
			if (IsPlainObject(obj)) {
				if (bound_object) {
					error = COPY("You cannot specify named parameters in two different objects.");
					return count;
				}
				bound_object = true;
				
				count += BindObject(obj, query->GetBindMap());
				if (error) {
					return count;
				}
				continue;
			}
		}
		
		// All other values
		BindValue(arg);
		if (error) {
			return count;
		}
		count += 1;
		
	}
	return (count << 1) | static_cast<int>(bound_object);
}
