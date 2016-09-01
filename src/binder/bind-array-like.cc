// Binds each value in the given Array-like object. Each parameter bound with
// this method is considered to be anonymous.
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is the number of
// parameters that were bound.

unsigned int Binder::BindArrayLike(v8::Local<v8::Object> arr, unsigned int len) {
	for (unsigned int i=0; i<len; ++i) {
		Nan::MaybeLocal<v8::Value> maybeValue = Nan::Get(arr, i);
		if (maybeValue.IsEmpty()) {
			error = "An error was thrown while trying to get values from the given array.";
			return i;
		}
		BindValue(maybeValue.ToLocalChecked());
		if (error) {
			return i;
		}
	}
	return len;
}
