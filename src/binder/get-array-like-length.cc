// Given an Array-like object, returns the value of its length property.
// If the given object is not Array-like, -1 is returned.
// If an error occurs, error is set to an appropriately descriptive string.

double Binder::GetArrayLikeLength(v8::Local<v8::Object> obj) {
	Nan::MaybeLocal<v8::Value> maybeLength = Nan::Get(obj, NEW_INTERNAL_STRING("length"));
	if (maybeLength.IsEmpty()) {
		error = "An error was thrown while trying to get the \"length\" property of the given object.";
		return -1;
	}
	v8::Local<v8::Value> length = maybeLength.ToLocalChecked();
	
	if (length->IsNumber()) {
		double value = v8::Local<v8::Number>::Cast(length)->Value();
		return (IS_POSITIVE_INTEGER(value) && value <= (double)0xffffffff) ? value : -1;
	}
	return -1;
}
