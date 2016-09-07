// Given the arguments to a JS function, and the length of arguments to loop
// through, binds all values given.
// Named parameters are given by objects (key-value pairs).
// Anonymous parameters are either directly in the arguments object, or in an
// Array (or Array-like object).
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::Bind(Nan::NAN_METHOD_ARGS_TYPE info, int len, v8::Local<v8::Object> bindMap) {
	bool bound_object = false;
	int count = 0;
	
	for (int i=0; i<len; ++i) {
		v8::Local<v8::Value> arg = info[i];
		
		// Arrays
		if (arg->IsArray()) {
			count += BindArray(v8::Local<v8::Array>::Cast(arg));
			if (error) {
				return;
			}
			continue;
		}
		
		// Objects
		if (arg->IsObject() && !arg->IsFunction() && !arg->IsArrayBufferView()) {
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(arg);
			
			// Plain objects
			if (IsPlainObject(obj)) {
				if (bound_object) {
					error = "You cannot specify named parameters in two different objects.";
					return;
				}
				bound_object = true;
				
				count += BindObject(obj, bindMap);
				if (error) {
					return;
				}
				continue;
			}
			
			// Array-like objects
			double array_like_length = GetArrayLikeLength(obj);
			if (error) {
				return;
			}
			if (array_like_length >= 0) {
				count += BindArrayLike(obj, (unsigned int)array_like_length);
				if (error) {
					return;
				}
				continue;
			}
		}
		
		// All other values
		BindValue(arg);
		if (error) {
			return;
		}
		count += 1;
		
	} // for
	
	if (count != param_count) {
		if (count < param_count) {
			error = "Too few parameter values were given.";
		} else {
			error = "Too many parameter values were given.";
		}
	}
	
}
