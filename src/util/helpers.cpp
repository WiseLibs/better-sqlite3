inline v8::Local<v8::String> StringFromUtf8(v8::Isolate* isolate, const char* data, int length) {
	return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kNormal, length).ToLocalChecked();
}

inline v8::Local<v8::String> InternalizedFromUtf8(v8::Isolate* isolate, const char* data, int length) {
	return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kInternalized, length).ToLocalChecked();
}

inline v8::Local<v8::Value> InternalizedFromUtf8OrNull(v8::Isolate* isolate, const char* data, int length) {
	if (data == NULL) return v8::Null(isolate);
	return InternalizedFromUtf8(isolate, data, length);
}

inline v8::Local<v8::String> InternalizedFromLatin1(v8::Isolate* isolate, const char* str) {
	return v8::String::NewFromOneByte(isolate, reinterpret_cast<const uint8_t*>(str), v8::NewStringType::kInternalized).ToLocalChecked();
}

inline void SetFrozen(v8::Isolate* isolate, v8::Local<v8::Context> ctx, v8::Local<v8::Object> obj, v8::Global<v8::String>& key, v8::Local<v8::Value> value) {
	obj->DefineOwnProperty(ctx, key.Get(isolate), value, static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly)).FromJust();
}

void ThrowError(const char* message) { EasyIsolate; isolate->ThrowException(v8::Exception::Error(StringFromUtf8(isolate, message, -1))); }
void ThrowTypeError(const char* message) { EasyIsolate; isolate->ThrowException(v8::Exception::TypeError(StringFromUtf8(isolate, message, -1))); }
void ThrowRangeError(const char* message) { EasyIsolate; isolate->ThrowException(v8::Exception::RangeError(StringFromUtf8(isolate, message, -1))); }

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

v8::Local<v8::FunctionTemplate> NewConstructorTemplate(
	v8::Isolate* isolate,
	v8::Local<v8::External> data,
	v8::FunctionCallback func,
	const char* name
) {
	v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, func, data);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(InternalizedFromLatin1(isolate, name));
	return t;
}

void SetPrototypeMethod(
	v8::Isolate* isolate,
	v8::Local<v8::External> data,
	v8::Local<v8::FunctionTemplate> recv,
	const char* name,
	v8::FunctionCallback func
) {
	v8::HandleScope scope(isolate);
	recv->PrototypeTemplate()->Set(
		InternalizedFromLatin1(isolate, name),
		v8::FunctionTemplate::New(isolate, func, data, v8::Signature::New(isolate, recv))
	);
}

void SetPrototypeSymbolMethod(
	v8::Isolate* isolate,
	v8::Local<v8::External> data,
	v8::Local<v8::FunctionTemplate> recv,
	v8::Local<v8::Symbol> symbol,
	v8::FunctionCallback func
) {
	v8::HandleScope scope(isolate);
	recv->PrototypeTemplate()->Set(
		symbol,
		v8::FunctionTemplate::New(isolate, func, data, v8::Signature::New(isolate, recv))
	);
}

void SetPrototypeGetter(
	v8::Isolate* isolate,
	v8::Local<v8::External> data,
	v8::Local<v8::FunctionTemplate> recv,
	const char* name,
	v8::AccessorNameGetterCallback func
) {
	v8::HandleScope scope(isolate);
	recv->InstanceTemplate()->SetNativeDataProperty(
		InternalizedFromLatin1(isolate, name),
		func,
		0,
		data
	);
}

#if defined(V8_ENABLE_SANDBOX)
// When V8 Sandbox is enabled (in newer Electron versions), we need to use Buffer::Copy
// instead of Buffer::New to ensure the ArrayBuffer backing store is allocated inside the sandbox
static inline v8::MaybeLocal<v8::Object> BufferSandboxNew(v8::Isolate* isolate, char* data, size_t length, void (*finalizeCallback)(char*, void*), void* finalizeHint) {
    v8::MaybeLocal<v8::Object> buffer = node::Buffer::Copy(isolate, data, length);
    finalizeCallback(data, finalizeHint);
    return buffer;
}
#define SAFE_NEW_BUFFER(env, data, length, finalizeCallback, finalizeHint) BufferSandboxNew(env, data, length, finalizeCallback, finalizeHint)
#else
// When V8 Sandbox is not enabled, we can use the more efficient Buffer::New
#define SAFE_NEW_BUFFER(env, data, length, finalizeCallback, finalizeHint) node::Buffer::New(env, data, length, finalizeCallback, finalizeHint)
#endif
