#include "binder.hpp"
#include "../better_sqlite3_impl.hpp"

bool IsPlainObject(v8::Isolate *isolate, v8::Local<v8::Object> obj) {
  v8::Local<v8::Value> proto = obj->GetPrototype();

#if defined NODE_MODULE_VERSION && NODE_MODULE_VERSION < 93
  v8::Local<v8::Context> ctx = obj->CreationContext();
#else
  v8::Local<v8::Context> ctx = obj->GetCreationContext().ToLocalChecked();
#endif

  ctx->Enter();
  v8::Local<v8::Value> baseProto = v8::Object::New(isolate)->GetPrototype();
  ctx->Exit();
  return proto->StrictEquals(baseProto) ||
         proto->StrictEquals(v8::Null(isolate));
}
Binder::Binder(sqlite3_stmt *_handle) {
  handle = _handle;
  param_count = sqlite3_bind_parameter_count(_handle);
  anon_index = 0;
  success = true;
}
bool Binder::Bind(v8::FunctionCallbackInfo<v8::Value> const &info, int argc,
                  Statement *stmt) {
  assert(anon_index == 0);
  Result result = BindArgs(info, argc, stmt);
  if (success && result.count != param_count) {
    if (result.count < param_count) {
      if (!result.bound_object &&
          stmt->GetBindMap(info.GetIsolate())->GetSize()) {
        Fail(ThrowTypeError, "Missing named parameters");
      } else {
        Fail(ThrowRangeError, "Too few parameter values were provided");
      }
    } else {
      Fail(ThrowRangeError, "Too many parameter values were provided");
    }
  }
  return success;
}
void Binder::Fail(void (*Throw)(char const *), char const *message) {
  assert(success == true);
  assert((Throw == NULL) == (message == NULL));
  assert(Throw == ThrowError || Throw == ThrowTypeError ||
         Throw == ThrowRangeError || Throw == NULL);
  if (Throw)
    Throw(message);
  success = false;
}
int Binder::NextAnonIndex() {
  while (sqlite3_bind_parameter_name(handle, ++anon_index) != NULL) {
  }
  return anon_index;
}
void Binder::BindValue(v8::Isolate *isolate, v8::Local<v8::Value> value,
                       int index) {
  int status = Data::BindValueFromJS(isolate, handle, index, value);
  if (status != SQLITE_OK) {
    switch (status) {
    case -1:
      return Fail(
          ThrowTypeError,
          "SQLite3 can only bind numbers, strings, bigints, buffers, and null");
    case SQLITE_TOOBIG:
      return Fail(ThrowRangeError,
                  "The bound string, buffer, or bigint is too big");
    case SQLITE_RANGE:
      return Fail(ThrowRangeError, "Too many parameter values were provided");
    case SQLITE_NOMEM:
      return Fail(ThrowError, "Out of memory");
    default:
      return Fail(
          ThrowError,
          "An unexpected error occured while trying to bind parameters");
    }
    assert(false);
  }
}
int Binder::BindArray(v8::Isolate *isolate, v8::Local<v8::Array> arr) {
  v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
  uint32_t length = arr->Length();
  if (length > INT_MAX) {
    Fail(ThrowRangeError, "Too many parameter values were provided");
    return 0;
  }
  int len = static_cast<int>(length);
  for (int i = 0; i < len; ++i) {
    v8::MaybeLocal<v8::Value> maybeValue = arr->Get(ctx, i);
    if (maybeValue.IsEmpty()) {
      Fail(NULL, NULL);
      return i;
    }
    BindValue(isolate, maybeValue.ToLocalChecked(), NextAnonIndex());
    if (!success) {
      return i;
    }
  }
  return len;
}
int Binder::BindObject(v8::Isolate *isolate, v8::Local<v8::Object> obj,
                       Statement *stmt) {
  v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
  BindMap *bind_map = stmt->GetBindMap(isolate);
  BindMap::Pair *pairs = bind_map->GetPairs();
  int len = bind_map->GetSize();

  for (int i = 0; i < len; ++i) {
    v8::Local<v8::String> key = pairs[i].GetName(isolate);

    v8::Maybe<bool> has_property = obj->HasOwnProperty(ctx, key);
    if (has_property.IsNothing()) {
      Fail(NULL, NULL);
      return i;
    }
    if (!has_property.FromJust()) {
      v8::String::Utf8Value param_name(isolate, key);
      Fail(ThrowRangeError,
           (std::string("Missing named parameter \"") + *param_name + "\"")
               .c_str());
      return i;
    }

    v8::MaybeLocal<v8::Value> maybeValue = obj->Get(ctx, key);
    if (maybeValue.IsEmpty()) {
      Fail(NULL, NULL);
      return i;
    }

    BindValue(isolate, maybeValue.ToLocalChecked(), pairs[i].GetIndex());
    if (!success) {
      return i;
    }
  }

  return len;
}
Binder::Result Binder::BindArgs(v8::FunctionCallbackInfo<v8::Value> const &info,
                                int argc, Statement *stmt) {
  v8::Isolate *isolate = info.GetIsolate();
  int count = 0;
  bool bound_object = false;

  for (int i = 0; i < argc; ++i) {
    v8::Local<v8::Value> arg = info[i];

    if (arg->IsArray()) {
      count += BindArray(isolate, arg.As<v8::Array>());
      if (!success)
        break;
      continue;
    }

    if (arg->IsObject() && !node::Buffer::HasInstance(arg)) {
      v8::Local<v8::Object> obj = arg.As<v8::Object>();
      if (IsPlainObject(isolate, obj)) {
        if (bound_object) {
          Fail(ThrowTypeError,
               "You cannot specify named parameters in two different objects");
          break;
        }
        bound_object = true;

        count += BindObject(isolate, obj, stmt);
        if (!success)
          break;
        continue;
      } else if (stmt->GetBindMap(isolate)->GetSize()) {
        Fail(ThrowTypeError,
             "Named parameters can only be passed within plain objects");
        break;
      }
    }

    BindValue(isolate, arg, NextAnonIndex());
    if (!success)
      break;
    count += 1;
  }

  return {count, bound_object};
}
