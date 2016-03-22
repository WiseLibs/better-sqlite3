// Given the arguments to a JS function, and the first index of the arguments
// which we want bind, binds all values given.
// If an error occurs, error is set to an appropriately descriptive string.

void Binder::Bind(Nan::NAN_METHOD_ARGS_TYPE info, int i) {
	int len = info.Length();
	bool bound_object = false;
	unsigned int count = 0;
	
	for (; i<len; i++) {
		v8::Local<v8::Value> arg = info[i];
		
		if (arg->IsArray()) {
			
			count += BindArray(v8::Local<v8::Array>::Cast(arg));
			if (error) {
				return;
			}
			
		} else if (arg->IsObject() && !node::Buffer::HasInstance(arg)) {
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(arg);
			
			double array_like_length = GetArrayLikeLength(obj));
			if (error) {
				return;
			}
			
			if (array_like_length >= 0) {
				count += BindArrayLike(obj, (unsigned int)array_like_length);
				if (error) {
					return;
				}
			} else {
				if (bound_object) {
					error = "You cannot specify named parameters in two different objects.";
					return;
				}
				bound_object = true;
				
				count += BindObject(v8::Local<v8::Object>::Cast(arg));
				if (error) {
					return;
				}
			}
			
		} else {
			
			BindValue(arg);
			if (error) {
				return;
			}
			count += 1;
			
		} // if else if ...
	} // for
	
	if (count != param_count) {
		if (count < param_count) {
			error = "Too few parameter values were given.";
		} else {
			error = "Too many parameter values were given.";
		}
	}
	
}
