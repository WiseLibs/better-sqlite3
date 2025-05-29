#ifndef BETTER_SQLITE3_UTIL_MACROS_HPP
#define BETTER_SQLITE3_UTIL_MACROS_HPP

#include "../better_sqlite3_deps.hpp"

// Buffer creation macro for V8 Sandbox compatibility
#if defined(V8_ENABLE_SANDBOX)
// When V8 Sandbox is enabled (in newer Electron versions), we need to use
// Buffer::Copy instead of Buffer::New to ensure the ArrayBuffer backing store
// is allocated inside the sandbox
static inline v8::MaybeLocal<v8::Object>
BufferSandboxNew(v8::Isolate *isolate, char *data, size_t length,
                 void (*finalizeCallback)(char *, void *), void *finalizeHint) {
  v8::MaybeLocal<v8::Object> buffer = node::Buffer::Copy(isolate, data, length);
  finalizeCallback(data, finalizeHint);
  return buffer;
}
#define SAFE_NEW_BUFFER(env, data, length, finalizeCallback, finalizeHint)     \
  BufferSandboxNew(env, data, length, finalizeCallback, finalizeHint)
#else
// When V8 Sandbox is not enabled, we can use the more efficient Buffer::New
#define SAFE_NEW_BUFFER(env, data, length, finalizeCallback, finalizeHint)     \
  node::Buffer::New(env, data, length, finalizeCallback, finalizeHint)
#endif

void SetPrototypeGetter(v8::Isolate *isolate, v8::Local<v8::External> data,
                        v8::Local<v8::FunctionTemplate> recv, const char *name,
                        v8::AccessorNameGetterCallback func);
v8::Local<v8::String> StringFromUtf8(v8::Isolate *isolate, char const *data,
                                     int length);
v8::Local<v8::String> InternalizedFromUtf8(v8::Isolate *isolate,
                                           char const *data, int length);
v8::Local<v8::Value> InternalizedFromUtf8OrNull(v8::Isolate *isolate,
                                                char const *data, int length);
v8::Local<v8::String> InternalizedFromLatin1(v8::Isolate *isolate,
                                             char const *str);
void SetFrozen(v8::Isolate *isolate, v8::Local<v8::Context> ctx,
               v8::Local<v8::Object> obj, v8::Global<v8::String> &key,
               v8::Local<v8::Value> value);
void ThrowError(char const *message);
void ThrowTypeError(char const *message);
void ThrowRangeError(char const *message);
bool IS_SKIPPED(char c);
template <typename T> T *ALLOC_ARRAY(size_t count);
template <typename T> void FREE_ARRAY(T *array_pointer);
v8::Local<v8::FunctionTemplate>
NewConstructorTemplate(v8::Isolate *isolate, v8::Local<v8::External> data,
                       v8::FunctionCallback func, char const *name);
void SetPrototypeMethod(v8::Isolate *isolate, v8::Local<v8::External> data,
                        v8::Local<v8::FunctionTemplate> recv, char const *name,
                        v8::FunctionCallback func);
void SetPrototypeSymbolMethod(v8::Isolate *isolate,
                              v8::Local<v8::External> data,
                              v8::Local<v8::FunctionTemplate> recv,
                              v8::Local<v8::Symbol> symbol,
                              v8::FunctionCallback func);
LZZ_INLINE v8::Local<v8::String> StringFromUtf8(v8::Isolate *isolate,
                                                char const *data, int length) {
  return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kNormal,
                                 length)
      .ToLocalChecked();
}
LZZ_INLINE v8::Local<v8::String>
InternalizedFromUtf8(v8::Isolate *isolate, char const *data, int length) {
  return v8::String::NewFromUtf8(isolate, data,
                                 v8::NewStringType::kInternalized, length)
      .ToLocalChecked();
}
LZZ_INLINE v8::Local<v8::Value>
InternalizedFromUtf8OrNull(v8::Isolate *isolate, char const *data, int length) {
  if (data == NULL)
    return v8::Null(isolate);
  return InternalizedFromUtf8(isolate, data, length);
}
LZZ_INLINE v8::Local<v8::String> InternalizedFromLatin1(v8::Isolate *isolate,
                                                        char const *str) {
  return v8::String::NewFromOneByte(isolate,
                                    reinterpret_cast<const uint8_t *>(str),
                                    v8::NewStringType::kInternalized)
      .ToLocalChecked();
}
LZZ_INLINE void SetFrozen(v8::Isolate *isolate, v8::Local<v8::Context> ctx,
                          v8::Local<v8::Object> obj,
                          v8::Global<v8::String> &key,
                          v8::Local<v8::Value> value) {
  obj->DefineOwnProperty(
         ctx, key.Get(isolate), value,
         static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly))
      .FromJust();
}
LZZ_INLINE bool IS_SKIPPED(char c) {
  return c == ' ' || c == ';' || (c >= '\t' && c <= '\r');
}
template <typename T> LZZ_INLINE T *ALLOC_ARRAY(size_t count) {
  return static_cast<T *>(::operator new[](count * sizeof(T)));
}
template <typename T> LZZ_INLINE void FREE_ARRAY(T *array_pointer) {
  ::operator delete[](array_pointer);
}

#endif // BETTER_SQLITE3_UTIL_MACROS_HPP
