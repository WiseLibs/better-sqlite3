inline Napi::String StringFromUtf8(Napi::Env env, const char* data, int length) {
	if (length < 0) return Napi::String::New(env, data);
	return Napi::String::New(env, data, length);
}

// Node-API has no equivalent of V8's internalized strings, so these are simple
// aliases of StringFromUtf8; the names are kept to preserve the intent of call
// sites (strings that are used repeatedly as property keys). If Node-API ever
// gains this functionality, we can easily restore it here.
inline Napi::String InternalizedFromUtf8(Napi::Env env, const char* data, int length) {
	return StringFromUtf8(env, data, length);
}

inline Napi::Value InternalizedFromUtf8OrNull(Napi::Env env, const char* data, int length) {
	if (data == NULL) return env.Null();
	return InternalizedFromUtf8(env, data, length);
}

inline Napi::String InternalizedFromLatin1(Napi::Env env, const char* str) {
	return Napi::String::New(env, str);
}

// Replicates the semantics of v8::Value::IsInt32() (an integral number within
// the range of a 32-bit signed integer, excluding -0), which has no direct
// Node-API equivalent.
inline bool IsInt32(Napi::Value value) {
	if (!value.IsNumber()) return false;
	double num = value.As<Napi::Number>().DoubleValue();
	if (!(num >= INT_MIN && num <= INT_MAX)) return false;
	if (num == 0) return !std::signbit(num);
	return static_cast<double>(static_cast<int32_t>(num)) == num;
}

inline void SetFrozen(Napi::Env env, Napi::Object obj, const Napi::Reference<Napi::String>& key, Napi::Value value) {
	obj.DefineProperty(Napi::PropertyDescriptor::Value(key.Value(), value, napi_enumerable));
}

// The following helpers perform JavaScript operations that can execute
// arbitrary user code (functions, proxies, getters). If the user code throws,
// the exception is left pending in the environment and an empty value is
// returned. The node-addon-api equivalents (Napi::Function::Call,
// Napi::Object::Get, etc.) must NOT be used for such operations, because their
// failure paths re-throw the pending exception through Napi::Error, which
// aborts the process when the thrown value is null or undefined (a
// node-addon-api bug, present as of v8.9.0, triggered by Node-API version 10).

inline Napi::Value SafeCall(Napi::Env env, Napi::Function fn, napi_value recv, size_t argc, const napi_value* args) {
	napi_value result;
	if (napi_call_function(env, recv, fn, argc, args, &result) != napi_ok) return Napi::Value();
	return Napi::Value(env, result);
}

inline Napi::Object SafeConstruct(Napi::Env env, Napi::Function constructor) {
	napi_value result;
	if (napi_new_instance(env, constructor, 0, NULL, &result) != napi_ok) return Napi::Object();
	return Napi::Object(env, result);
}

inline Napi::Value SafeGet(Napi::Env env, Napi::Object obj, napi_value key) {
	napi_value result;
	if (napi_get_property(env, obj, key, &result) != napi_ok) return Napi::Value();
	return Napi::Value(env, result);
}

inline Napi::Value SafeGetElement(Napi::Env env, Napi::Object obj, uint32_t index) {
	napi_value result;
	if (napi_get_element(env, obj, index, &result) != napi_ok) return Napi::Value();
	return Napi::Value(env, result);
}

// Returns false if the check itself failed (leaving an exception pending).
inline bool SafeHasOwnProperty(Napi::Env env, Napi::Object obj, napi_value key, bool* result) {
	return napi_has_own_property(env, obj, key, result) == napi_ok;
}

Napi::Value ThrowError(Napi::Env env, const char* message) {
	Napi::Error::New(env, message).ThrowAsJavaScriptException();
	return env.Undefined();
}
Napi::Value ThrowTypeError(Napi::Env env, const char* message) {
	Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
	return env.Undefined();
}
Napi::Value ThrowRangeError(Napi::Env env, const char* message) {
	Napi::RangeError::New(env, message).ThrowAsJavaScriptException();
	return env.Undefined();
}

// Unwraps a native-backed object into its associated C++ instance. This must
// only be used on values that are already known to be backed by the given
// class (e.g., a receiver that was validated by TypeSafeCallback below, or a
// value produced by our own code), because napi_unwrap does not check the
// object's type.
template <typename T> inline T* Unwrap(Napi::Value value) {
	return T::Unwrap(value.As<Napi::Object>());
}

// Generates a random type tag when the addon is loaded. Type tags must not be
// hardcoded, because multiple copies (or even different versions) of the addon
// can be loaded into a single process (see the "nativeBinding" option), and
// objects created by one copy must not be accepted by another copy's methods,
// whose class layouts may differ.
inline napi_type_tag RandomTypeTag() {
	std::random_device rd;
	auto random64 = [&rd]() {
		return (static_cast<uint64_t>(rd()) << 32) | static_cast<uint64_t>(rd());
	};
	return { random64(), random64() };
}

// Determines whether the given value is an object that is backed by the given
// native class. Each native class is identified by a unique type tag, which
// gets applied to each of its instances upon construction.
template <typename T> inline bool IsInstanceOf(Napi::Env env, Napi::Value value) {
	bool result = false;
	napi_status status = napi_check_object_type_tag(env, value.As<Napi::Object>(), &T::TYPE_TAG, &result);
	return status == napi_ok && result;
}

// Wraps a native method so that it can only be invoked on a receiver that is
// backed by the expected native class. Node-API has no equivalent of
// v8::Signature, and napi_unwrap alone does not check the object's type, so
// without this check, a method borrowed onto a foreign wrapped object (e.g.,
// db.exec.call(stmt)) would reinterpret the wrapped pointer as the wrong type.
template <typename T, Napi::Value (*method)(const Napi::CallbackInfo&)>
napi_value TypeSafeCallback(napi_env env, napi_callback_info info) {
	Napi::CallbackInfo cbinfo(env, info);
	if (!IsInstanceOf<T>(env, cbinfo.This())) {
		Napi::TypeError::New(env, "Illegal invocation").ThrowAsJavaScriptException();
		return NULL;
	}
	return method(cbinfo);
}

// These match the default attributes of properties created by a V8 template.
constexpr napi_property_attributes DEFAULT_ATTRIBUTES =
	static_cast<napi_property_attributes>(napi_writable | napi_enumerable | napi_configurable);

template <typename T, Napi::Value (*method)(const Napi::CallbackInfo&)>
napi_property_descriptor PrototypeMethod(const char* name, Addon* addon) {
	napi_property_descriptor desc = {};
	desc.utf8name = name;
	desc.method = TypeSafeCallback<T, method>;
	desc.attributes = DEFAULT_ATTRIBUTES;
	desc.data = addon;
	return desc;
}

template <typename T, Napi::Value (*method)(const Napi::CallbackInfo&)>
napi_property_descriptor PrototypeSymbolMethod(Napi::Symbol symbol, Addon* addon) {
	napi_property_descriptor desc = {};
	desc.name = symbol;
	desc.method = TypeSafeCallback<T, method>;
	desc.attributes = DEFAULT_ATTRIBUTES;
	desc.data = addon;
	return desc;
}

// Defines a getter as an own property of the given object. V8 exposed these
// getters as native data properties on each instance, which made them visible
// to console.log(); Node-API has no native data properties, so an own accessor
// property is the closest equivalent (unlike a prototype accessor, it is still
// displayed by console.log(), albeit as [Getter]).
template <typename T, Napi::Value (*method)(const Napi::CallbackInfo&)>
void SetInstanceGetter(Napi::Object obj, const char* name, Addon* addon) {
	napi_property_descriptor desc = {};
	desc.utf8name = name;
	desc.getter = TypeSafeCallback<T, method>;
	desc.attributes = napi_enumerable;
	desc.data = addon;
	napi_status status = napi_define_properties(obj.Env(), obj, 1, &desc);
	assert(status == napi_ok); ((void)status);
}

// Determines whether to skip the given character at the start of an SQL string.
inline bool IS_SKIPPED(char c) {
	return c == ' ' || c == ';' || (c >= '\t' && c <= '\r');
}

// Allocates an empty array, without calling constructors/initializers.
template<class T> inline T* ALLOC_ARRAY(size_t count) {
	return static_cast<T*>(::operator new[](count * sizeof(T)));
}

// Deallocates an array, without calling destructors.
template<class T> inline void FREE_ARRAY(T* array_pointer) {
	::operator delete[](array_pointer);
}
