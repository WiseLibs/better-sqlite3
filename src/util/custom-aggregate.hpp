#ifndef BETTER_SQLITE3_UTIL_CUSTOM_AGGREGATE_HPP
#define BETTER_SQLITE3_UTIL_CUSTOM_AGGREGATE_HPP

#include "../better_sqlite3_deps.hpp"
#include "custom-function.hpp"
#include "data.hpp"
#include "macros.hpp"

class CustomAggregate : public CustomFunction {
public:
  explicit CustomAggregate(v8::Isolate *isolate, Database *db, char const *name,
                           v8::Local<v8::Value> start,
                           v8::Local<v8::Function> step,
                           v8::Local<v8::Value> inverse,
                           v8::Local<v8::Value> result, bool safe_ints);
  static void xStep(sqlite3_context *invocation, int argc,
                    sqlite3_value **argv);
  static void xInverse(sqlite3_context *invocation, int argc,
                       sqlite3_value **argv);
  static void xValue(sqlite3_context *invocation);
  static void xFinal(sqlite3_context *invocation);

private:
  static void xStepBase(sqlite3_context *invocation, int argc,
                        sqlite3_value **argv,
                        v8::Global<v8::Function> const CustomAggregate::*ptrtm);
  static void xValueBase(sqlite3_context *invocation, bool is_final);
  struct Accumulator {
  public:
    v8::Global<v8::Value> value;
    bool initialized;
    bool is_window;
  };
  Accumulator *GetAccumulator(sqlite3_context *invocation);
  static void DestroyAccumulator(sqlite3_context *invocation);
  void PropagateJSError(sqlite3_context *invocation);
  bool const invoke_result;
  bool const invoke_start;
  v8::Global<v8::Function> const inverse;
  v8::Global<v8::Function> const result;
  v8::Global<v8::Value> const start;
};
LZZ_INLINE void CustomAggregate::xStepBase(
    sqlite3_context *invocation, int argc, sqlite3_value **argv,
    v8::Global<v8::Function> const CustomAggregate::*ptrtm) {
  CustomAggregate *self =
      static_cast<CustomAggregate *>(sqlite3_user_data(invocation));
  v8::Isolate *isolate = self->isolate;
  v8::HandleScope scope(isolate);
  Accumulator *acc = self->GetAccumulator(invocation);
  if (acc->value.IsEmpty())
    return;

  v8::Local<v8::Value> args_fast[5];
  v8::Local<v8::Value> *args =
      argc <= 4 ? args_fast : ALLOC_ARRAY<v8::Local<v8::Value>>(argc + 1);
  args[0] = acc->value.Get(isolate);
  if (argc != 0)
    Data::GetArgumentsJS(isolate, args + 1, argv, argc, self->safe_ints);

  v8::MaybeLocal<v8::Value> maybeReturnValue =
      (self->*ptrtm)
          .Get(isolate)
          ->Call(isolate->GetCurrentContext(), v8::Undefined(isolate), argc + 1,
                 args);
  if (args != args_fast)
    delete[] args;

  if (maybeReturnValue.IsEmpty()) {
    self->PropagateJSError(invocation);
  } else {
    v8::Local<v8::Value> returnValue = maybeReturnValue.ToLocalChecked();
    if (!returnValue->IsUndefined())
      acc->value.Reset(isolate, returnValue);
  }
}
LZZ_INLINE void CustomAggregate::xValueBase(sqlite3_context *invocation,
                                            bool is_final) {
  CustomAggregate *self =
      static_cast<CustomAggregate *>(sqlite3_user_data(invocation));
  v8::Isolate *isolate = self->isolate;
  v8::HandleScope scope(isolate);
  Accumulator *acc = self->GetAccumulator(invocation);
  if (acc->value.IsEmpty())
    return;

  if (!is_final) {
    acc->is_window = true;
  } else if (acc->is_window) {
    DestroyAccumulator(invocation);
    return;
  }

  v8::Local<v8::Value> result = acc->value.Get(isolate);
  if (self->invoke_result) {
    v8::MaybeLocal<v8::Value> maybeResult = self->result.Get(isolate)->Call(
        isolate->GetCurrentContext(), v8::Undefined(isolate), 1, &result);
    if (maybeResult.IsEmpty()) {
      self->PropagateJSError(invocation);
      return;
    }
    result = maybeResult.ToLocalChecked();
  }

  Data::ResultValueFromJS(isolate, invocation, result, self);
  if (is_final)
    DestroyAccumulator(invocation);
}

#endif // BETTER_SQLITE3_UTIL_CUSTOM_AGGREGATE_HPP
