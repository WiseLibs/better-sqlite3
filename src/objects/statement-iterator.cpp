#include "statement-iterator.hpp"
#include "../better_sqlite3_impl.hpp"

// Inline implementations that depend on Addon
v8::Local<v8::Object> StatementIterator::NewRecord(v8::Isolate *isolate,
                                                   v8::Local<v8::Context> ctx,
                                                   v8::Local<v8::Value> value,
                                                   Addon *addon, bool done) {
  v8::Local<v8::Object> record = v8::Object::New(isolate);
  record->Set(ctx, addon->cs.value.Get(isolate), value).FromJust();
  record->Set(ctx, addon->cs.done.Get(isolate), v8::Boolean::New(isolate, done))
      .FromJust();
  return record;
}

v8::Local<v8::Object> StatementIterator::DoneRecord(v8::Isolate *isolate,
                                                    Addon *addon) {
  return NewRecord(isolate, isolate->GetCurrentContext(),
                   v8::Undefined(isolate), addon, true);
}

v8::Local<v8::Function> StatementIterator::Init(v8::Isolate *isolate,
                                                v8::Local<v8::External> data) {
  v8::Local<v8::FunctionTemplate> t =
      NewConstructorTemplate(isolate, data, JS_new, "StatementIterator");
  SetPrototypeMethod(isolate, data, t, "next", JS_next);
  SetPrototypeMethod(isolate, data, t, "return", JS_return);
  SetPrototypeSymbolMethod(isolate, data, t, v8::Symbol::GetIterator(isolate),
                           JS_symbolIterator);
  return t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
}
StatementIterator::~StatementIterator() {}
StatementIterator::StatementIterator(Statement *stmt, bool bound)
    : node::ObjectWrap(), stmt(stmt), handle(stmt->handle),
      db_state(stmt->db->GetState()), bound(bound), safe_ints(stmt->safe_ints),
      mode(stmt->mode), alive(true), logged(!db_state->has_logger) {
  assert(stmt != NULL);
  assert(handle != NULL);
  assert(stmt->bound == bound);
  assert(stmt->alive == true);
  assert(stmt->locked == false);
  assert(db_state->iterators < USHRT_MAX);
  stmt->locked = true;
  db_state->iterators += 1;
}
void StatementIterator::JS_new(
    v8::FunctionCallbackInfo<v8::Value> const &info) {
  Addon *addon = static_cast<Addon *>(info.Data().As<v8::External>()->Value());
  if (!addon->privileged_info)
    return ThrowTypeError("Disabled constructor");
  assert(info.IsConstructCall());

  StatementIterator *iter;
  {
    const v8::FunctionCallbackInfo<v8::Value> &info = *addon->privileged_info;
    Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
    if (!stmt->returns_data)
      return ThrowTypeError(
          "This statement does not return data. Use run() instead");
    sqlite3_stmt *handle = stmt->handle;
    Database *db = stmt->db;
    if (!db->GetState()->open)
      return ThrowTypeError("The database connection is not open");
    if (db->GetState()->busy)
      return ThrowTypeError(
          "This database connection is busy executing a query");
    if (stmt->locked)
      return ThrowTypeError("This statement is busy executing a query");
    if (db->GetState()->iterators == USHRT_MAX)
      return ThrowRangeError("Too many active database iterators");
    const bool bound = stmt->bound;
    if (!bound) {
      Binder binder(handle);
      if (!binder.Bind(info, info.Length(), stmt)) {
        sqlite3_clear_bindings(handle);
        return;
      }
      ((void)0);
    } else if (info.Length() > 0) {
      return ThrowTypeError("This statement already has bound parameters");
    }
    ((void)0);
    iter = new StatementIterator(stmt, bound);
  }
  v8::Isolate *isolate = info.GetIsolate();
  v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
  iter->Wrap(info.This());
  SetFrozen(isolate, ctx, info.This(), addon->cs.statement,
            addon->privileged_info->This());

  info.GetReturnValue().Set(info.This());
}
void StatementIterator::JS_next(
    v8::FunctionCallbackInfo<v8::Value> const &info) {
  StatementIterator *iter =
      node ::ObjectWrap ::Unwrap<StatementIterator>(info.This());
  if (iter->db_state->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (iter->alive)
    iter->Next(info);
  else
    info.GetReturnValue().Set(
        DoneRecord(info.GetIsolate(), iter->db_state->addon));
}
void StatementIterator::JS_return(
    v8::FunctionCallbackInfo<v8::Value> const &info) {
  StatementIterator *iter =
      node ::ObjectWrap ::Unwrap<StatementIterator>(info.This());
  if (iter->db_state->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (iter->alive)
    iter->Return(info);
  else
    info.GetReturnValue().Set(
        DoneRecord(info.GetIsolate(), iter->db_state->addon));
}
void StatementIterator::JS_symbolIterator(
    v8::FunctionCallbackInfo<v8::Value> const &info) {
  info.GetReturnValue().Set(info.This());
}
void StatementIterator::Next(v8::FunctionCallbackInfo<v8::Value> const &info) {
  assert(alive == true);
  db_state->busy = true;
  if (!logged) {
    logged = true;
    if (stmt->db->Log(info.GetIsolate(), handle)) {
      db_state->busy = false;
      Throw();
      return;
    }
  }
  int status = sqlite3_step(handle);
  db_state->busy = false;
  if (status == SQLITE_ROW) {
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
    info.GetReturnValue().Set(NewRecord(
        isolate, ctx, Data::GetRowJS(isolate, ctx, handle, safe_ints, mode),
        db_state->addon, false));
  } else {
    if (status == SQLITE_DONE)
      Return(info);
    else
      Throw();
  }
}
void StatementIterator::Return(
    v8::FunctionCallbackInfo<v8::Value> const &info) {
  Cleanup();
  info.GetReturnValue().Set(DoneRecord(info.GetIsolate(), db_state->addon));
  if (!bound) {
    sqlite3_clear_bindings(handle);
  }
  return;
}
void StatementIterator::Throw() {
  Cleanup();
  Database *db = stmt->db;
  db->ThrowDatabaseError();
  if (!bound) {
    sqlite3_clear_bindings(handle);
  }
  return;
}
void StatementIterator::Cleanup() {
  assert(alive == true);
  alive = false;
  stmt->locked = false;
  db_state->iterators -= 1;
  sqlite3_reset(handle);
}
