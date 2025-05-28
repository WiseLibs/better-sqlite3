#include "custom-function.hpp"
#include "../better_sqlite3_impl.hpp"

CustomFunction::CustomFunction(v8::Isolate *isolate, Database *db,
                               char const *name, v8::Local<v8::Function> fn,
                               bool safe_ints)
    : name(name), db(db), isolate(isolate), fn(isolate, fn),
      safe_ints(safe_ints) {}
CustomFunction::~CustomFunction() {}
void CustomFunction::xDestroy(void *self) {
  delete static_cast<CustomFunction *>(self);
}
void CustomFunction::xFunc(sqlite3_context *invocation, int argc,
                           sqlite3_value **argv) {
  CustomFunction *self =
      static_cast<CustomFunction *>(sqlite3_user_data(invocation));
  v8 ::Isolate *isolate = self->isolate;
  v8 ::HandleScope scope(isolate);

  v8::Local<v8::Value> args_fast[4];
  v8::Local<v8::Value> *args = NULL;
  if (argc != 0) {
    args = argc <= 4 ? args_fast : ALLOC_ARRAY<v8::Local<v8::Value>>(argc);
    Data::GetArgumentsJS(isolate, args, argv, argc, self->safe_ints);
  }

  v8::MaybeLocal<v8::Value> maybeReturnValue = self->fn.Get(isolate)->Call(
      isolate->GetCurrentContext(), v8::Undefined(isolate), argc, args);
  if (args != args_fast)
    delete[] args;

  if (maybeReturnValue.IsEmpty())
    self->PropagateJSError(invocation);
  else
    Data::ResultValueFromJS(isolate, invocation,
                            maybeReturnValue.ToLocalChecked(), self);
}
void CustomFunction::PropagateJSError(sqlite3_context *invocation) {
  assert(db->GetState()->was_js_error == false);
  db->GetState()->was_js_error = true;
  sqlite3_result_error(invocation, "", 0);
}
std::string CustomFunction::GetDataErrorPrefix() {
  return std::string("User-defined function ") + name + "() returned";
}
