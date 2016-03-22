// Binds each value in the given Array. Each parameter bound with this method is
// considered to be anonymous.
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is the number of
// parameters that were bound.

unsigned int Binder::BindArray(v8::Local<v8::Array> arr) {
	return BindArrayLike(v8::Local<v8::Object>::Cast(arr), arr->Length());
}
