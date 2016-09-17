// Binds each value in the given Array. Each parameter bound with this method is
// considered to be anonymous.
// If an error occurs, error is set to an appropriately descriptive string.
// Regardless of whether an error occurs, the return value is the number of
// parameters that were bound.

int Binder::BindArray(v8::Local<v8::Array> arr) {
	unsigned int length = arr->Length();
	int len = length > 0x7ffffffeU ? 0x7ffffffe : static_cast<int>(length);
	for (int i=0; i<len; ++i) {
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
