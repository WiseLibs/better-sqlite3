#include "custom-aggregate.hpp"
#include "../better_sqlite3_impl.hpp"

CustomAggregate::CustomAggregate(v8::Isolate *isolate, Database *db,
                                 char const *name, v8::Local<v8::Value> start,
                                 v8::Local<v8::Function> step,
                                 v8::Local<v8::Value> inverse,
                                 v8::Local<v8::Value> result, bool safe_ints)
    : CustomFunction(isolate, db, name, step, safe_ints),
      invoke_result(result->IsFunction()), invoke_start(start->IsFunction()),
      inverse(isolate, inverse->IsFunction() ? inverse.As<v8::Function>()
                                             : v8::Local<v8::Function>()),
      result(isolate, result->IsFunction() ? result.As<v8::Function>()
                                           : v8::Local<v8::Function>()),
      start(isolate, start) {}
void CustomAggregate::xStep(sqlite3_context *invocation, int argc,
                            sqlite3_value **argv) {
  xStepBase(invocation, argc, argv, &CustomAggregate::fn);
}
void CustomAggregate::xInverse(sqlite3_context *invocation, int argc,
                               sqlite3_value **argv) {
  xStepBase(invocation, argc, argv, &CustomAggregate::inverse);
}
void CustomAggregate::xValue(sqlite3_context *invocation) {
  xValueBase(invocation, false);
}
void CustomAggregate::xFinal(sqlite3_context *invocation) {
  xValueBase(invocation, true);
}
CustomAggregate::Accumulator *
CustomAggregate::GetAccumulator(sqlite3_context *invocation) {
  Accumulator *acc = static_cast<Accumulator *>(
      sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
  if (!acc->initialized) {
    assert(acc->value.IsEmpty());
    acc->initialized = true;
    if (invoke_start) {
      v8::MaybeLocal<v8::Value> maybeSeed =
          start.Get(isolate).As<v8::Function>()->Call(
              isolate->GetCurrentContext(), v8::Undefined(isolate), 0, NULL);
      if (maybeSeed.IsEmpty())
        PropagateJSError(invocation);
      else
        acc->value.Reset(isolate, maybeSeed.ToLocalChecked());
    } else {
      assert(!start.IsEmpty());
      acc->value.Reset(isolate, start);
    }
  }
  return acc;
}
void CustomAggregate::DestroyAccumulator(sqlite3_context *invocation) {
  Accumulator *acc = static_cast<Accumulator *>(
      sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
  assert(acc->initialized);
  acc->value.Reset();
}
void CustomAggregate::PropagateJSError(sqlite3_context *invocation) {
  DestroyAccumulator(invocation);
  CustomFunction::PropagateJSError(invocation);
}
