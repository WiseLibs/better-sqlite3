#include "macros.hpp"
#include "../better_sqlite3_impl.hpp"

void SetPrototypeGetter(v8::Isolate *isolate, v8::Local<v8::External> data,
                        v8::Local<v8::FunctionTemplate> recv, const char *name,
                        v8::AccessorNameGetterCallback func) {
  v8::HandleScope scope(isolate);

#if defined NODE_MODULE_VERSION && NODE_MODULE_VERSION < 121
  recv->InstanceTemplate()->SetAccessor(
      InternalizedFromLatin1(isolate, name), func, 0, data,
      v8::AccessControl::DEFAULT, v8::PropertyAttribute::None);
#else
  recv->InstanceTemplate()->SetNativeDataProperty(
      InternalizedFromLatin1(isolate, name), func, 0, data);
#endif
}

void ThrowError(char const *message) {
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  isolate->ThrowException(
      v8::Exception::Error(StringFromUtf8(isolate, message, -1)));
}
void ThrowTypeError(char const *message) {
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  isolate->ThrowException(
      v8::Exception::TypeError(StringFromUtf8(isolate, message, -1)));
}
void ThrowRangeError(char const *message) {
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  isolate->ThrowException(
      v8::Exception::RangeError(StringFromUtf8(isolate, message, -1)));
}
v8::Local<v8::FunctionTemplate>
NewConstructorTemplate(v8::Isolate *isolate, v8::Local<v8::External> data,
                       v8::FunctionCallback func, char const *name) {
  v8::Local<v8::FunctionTemplate> t =
      v8::FunctionTemplate::New(isolate, func, data);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(InternalizedFromLatin1(isolate, name));
  return t;
}
void SetPrototypeMethod(v8::Isolate *isolate, v8::Local<v8::External> data,
                        v8::Local<v8::FunctionTemplate> recv, char const *name,
                        v8::FunctionCallback func) {
  v8::HandleScope scope(isolate);
  recv->PrototypeTemplate()->Set(
      InternalizedFromLatin1(isolate, name),
      v8::FunctionTemplate::New(isolate, func, data,
                                v8::Signature::New(isolate, recv)));
}
void SetPrototypeSymbolMethod(v8::Isolate *isolate,
                              v8::Local<v8::External> data,
                              v8::Local<v8::FunctionTemplate> recv,
                              v8::Local<v8::Symbol> symbol,
                              v8::FunctionCallback func) {
  v8::HandleScope scope(isolate);
  recv->PrototypeTemplate()->Set(
      symbol, v8::FunctionTemplate::New(isolate, func, data,
                                        v8::Signature::New(isolate, recv)));
}
