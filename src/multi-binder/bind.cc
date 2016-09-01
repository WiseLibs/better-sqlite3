// Given the arguments to a JS function, and the length of arguments to loop
// through, binds all values given.
// Named parameters are given by objects (key-value pairs).
// Anonymous parameters are either directly in the arguments object, or in an
// Array (or Array-like object).
// If an error occurs, error is set to an appropriately descriptive string.

void MultiBinder::Bind(Nan::NAN_METHOD_ARGS_TYPE info, int len) {
	// bool bound_object = false;
	unsigned int count = 0;
	
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
			
			double array_like_length = GetArrayLikeLength(obj);
			if (error) {
				return;
			}
			
			// Array-like objects
			if (array_like_length >= 0) {
				count += BindArrayLike(obj, (unsigned int)array_like_length);
				if (error) {
					return;
				}
				continue;
			}
			
			// Plain objects
			if (IsPlainObject(obj)) {
				error = "Named parameters are not yet supported in transactions.";
				return;
				// if (bound_object) {
				// 	error = "You cannot specify named parameters in two different objects.";
				// 	return;
				// }
				// bound_object = true;
				
				// count += BindObject(v8::Local<v8::Object>::Cast(arg));
				// if (error) {
				// 	return;
				// }
				// continue;
			}
		}
		
		// All other values
		BindValue(arg);
		if (error) {
			return;
		}
		count += 1;
		
	} // for
	
	if (handle_index != handle_count - 1 || count != param_count_sum) {
		if (handle_index < handle_count - 1 || count < param_count_sum) {
			error = "Too few parameter values were given.";
		} else {
			error = "Too many parameter values were given.";
		}
	}
	
}
