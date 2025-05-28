#include "data.hpp"
#include "../better_sqlite3_impl.hpp"

// Constants are now defined in data.hpp
namespace Data {
v8::Local<v8::Value> GetValueJS(v8::Isolate *isolate, sqlite3_stmt *handle,
                                int column, bool safe_ints) {
  switch (sqlite3_column_type(handle, column)) {
  case SQLITE_INTEGER:
    if (safe_ints) {
      return v8 ::BigInt ::New(isolate, sqlite3_column_int64(handle, column));
    }
  case SQLITE_FLOAT:
    return v8 ::Number ::New(isolate, sqlite3_column_double(handle, column));
  case SQLITE_TEXT:
    return StringFromUtf8(
        isolate,
        reinterpret_cast<const char *>(sqlite3_column_text(handle, column)),
        sqlite3_column_bytes(handle, column));
  case SQLITE_BLOB:
    return node ::Buffer ::Copy(
               isolate,
               static_cast<const char *>(sqlite3_column_blob(handle, column)),
               sqlite3_column_bytes(handle, column))
        .ToLocalChecked();
  default:
    assert(sqlite3_column_type(handle, column) == SQLITE_NULL);
    return v8 ::Null(isolate);
  }
  assert(false);
  ;
}
} // namespace Data
namespace Data {
v8::Local<v8::Value> GetValueJS(v8::Isolate *isolate, sqlite3_value *value,
                                bool safe_ints) {
  switch (sqlite3_value_type(value)) {
  case SQLITE_INTEGER:
    if (safe_ints) {
      return v8 ::BigInt ::New(isolate, sqlite3_value_int64(value));
    }
  case SQLITE_FLOAT:
    return v8 ::Number ::New(isolate, sqlite3_value_double(value));
  case SQLITE_TEXT:
    return StringFromUtf8(
        isolate, reinterpret_cast<const char *>(sqlite3_value_text(value)),
        sqlite3_value_bytes(value));
  case SQLITE_BLOB:
    return node ::Buffer ::Copy(
               isolate, static_cast<const char *>(sqlite3_value_blob(value)),
               sqlite3_value_bytes(value))
        .ToLocalChecked();
  default:
    assert(sqlite3_value_type(value) == SQLITE_NULL);
    return v8 ::Null(isolate);
  }
  assert(false);
  ;
}
} // namespace Data
namespace Data {
v8::Local<v8::Value> GetFlatRowJS(v8::Isolate *isolate,
                                  v8::Local<v8::Context> ctx,
                                  sqlite3_stmt *handle, bool safe_ints) {
  v8::Local<v8::Object> row = v8::Object::New(isolate);
  int column_count = sqlite3_column_count(handle);
  for (int i = 0; i < column_count; ++i) {
    row->Set(ctx,
             InternalizedFromUtf8(isolate, sqlite3_column_name(handle, i), -1),
             Data::GetValueJS(isolate, handle, i, safe_ints))
        .FromJust();
  }
  return row;
}
} // namespace Data
namespace Data {
v8::Local<v8::Value> GetExpandedRowJS(v8::Isolate *isolate,
                                      v8::Local<v8::Context> ctx,
                                      sqlite3_stmt *handle, bool safe_ints) {
  v8::Local<v8::Object> row = v8::Object::New(isolate);
  int column_count = sqlite3_column_count(handle);
  for (int i = 0; i < column_count; ++i) {
    const char *table_raw = sqlite3_column_table_name(handle, i);
    v8::Local<v8::String> table =
        InternalizedFromUtf8(isolate, table_raw == NULL ? "$" : table_raw, -1);
    v8::Local<v8::String> column =
        InternalizedFromUtf8(isolate, sqlite3_column_name(handle, i), -1);
    v8::Local<v8::Value> value =
        Data::GetValueJS(isolate, handle, i, safe_ints);
    if (row->HasOwnProperty(ctx, table).FromJust()) {
      row->Get(ctx, table)
          .ToLocalChecked()
          .As<v8::Object>()
          ->Set(ctx, column, value)
          .FromJust();
    } else {
      v8::Local<v8::Object> nested = v8::Object::New(isolate);
      row->Set(ctx, table, nested).FromJust();
      nested->Set(ctx, column, value).FromJust();
    }
  }
  return row;
}
} // namespace Data
namespace Data {
v8::Local<v8::Value> GetRawRowJS(v8::Isolate *isolate,
                                 v8::Local<v8::Context> ctx,
                                 sqlite3_stmt *handle, bool safe_ints) {
  v8::Local<v8::Array> row = v8::Array::New(isolate);
  int column_count = sqlite3_column_count(handle);
  for (int i = 0; i < column_count; ++i) {
    row->Set(ctx, i, Data::GetValueJS(isolate, handle, i, safe_ints))
        .FromJust();
  }
  return row;
}
} // namespace Data
namespace Data {
v8::Local<v8::Value> GetRowJS(v8::Isolate *isolate, v8::Local<v8::Context> ctx,
                              sqlite3_stmt *handle, bool safe_ints, char mode) {
  if (mode == FLAT)
    return GetFlatRowJS(isolate, ctx, handle, safe_ints);
  if (mode == PLUCK)
    return GetValueJS(isolate, handle, 0, safe_ints);
  if (mode == EXPAND)
    return GetExpandedRowJS(isolate, ctx, handle, safe_ints);
  if (mode == RAW)
    return GetRawRowJS(isolate, ctx, handle, safe_ints);
  assert(false);
  return v8::Local<v8::Value>();
}
} // namespace Data
namespace Data {
void GetArgumentsJS(v8::Isolate *isolate, v8::Local<v8::Value> *out,
                    sqlite3_value **values, int argument_count,
                    bool safe_ints) {
  assert(argument_count > 0);
  for (int i = 0; i < argument_count; ++i) {
    out[i] = Data::GetValueJS(isolate, values[i], safe_ints);
  }
}
} // namespace Data
namespace Data {
int BindValueFromJS(v8::Isolate *isolate, sqlite3_stmt *handle, int index,
                    v8::Local<v8::Value> value) {
  if (value->IsNumber()) {
    return sqlite3_bind_double(handle, index, value.As<v8 ::Number>()->Value());
  } else if (value->IsBigInt()) {
    bool lossless;
    int64_t v = value.As<v8 ::BigInt>()->Int64Value(&lossless);
    if (lossless) {
      return sqlite3_bind_int64(handle, index, v);
    }
  } else if (value->IsString()) {
    v8 ::String ::Utf8Value utf8(isolate, value.As<v8 ::String>());
    return sqlite3_bind_text(handle, index, *utf8, utf8.length(),
                             SQLITE_TRANSIENT);
  } else if (node ::Buffer ::HasInstance(value)) {
    const char *data = node ::Buffer ::Data(value);
    return sqlite3_bind_blob(handle, index, data ? data : "",
                             node ::Buffer ::Length(value), SQLITE_TRANSIENT);
  } else if (value->IsNull() || value->IsUndefined()) {
    return sqlite3_bind_null(handle, index);
  };
  return value->IsBigInt() ? SQLITE_TOOBIG : -1;
}
} // namespace Data
namespace Data {
void ResultValueFromJS(v8::Isolate *isolate, sqlite3_context *invocation,
                       v8::Local<v8::Value> value, DataConverter *converter) {
  if (value->IsNumber()) {
    return sqlite3_result_double(invocation, value.As<v8 ::Number>()->Value());
  } else if (value->IsBigInt()) {
    bool lossless;
    int64_t v = value.As<v8 ::BigInt>()->Int64Value(&lossless);
    if (lossless) {
      return sqlite3_result_int64(invocation, v);
    }
  } else if (value->IsString()) {
    v8 ::String ::Utf8Value utf8(isolate, value.As<v8 ::String>());
    return sqlite3_result_text(invocation, *utf8, utf8.length(),
                               SQLITE_TRANSIENT);
  } else if (node ::Buffer ::HasInstance(value)) {
    const char *data = node ::Buffer ::Data(value);
    return sqlite3_result_blob(invocation, data ? data : "",
                               node ::Buffer ::Length(value), SQLITE_TRANSIENT);
  } else if (value->IsNull() || value->IsUndefined()) {
    return sqlite3_result_null(invocation);
  };
  converter->ThrowDataConversionError(invocation, value->IsBigInt());
}
} // namespace Data
