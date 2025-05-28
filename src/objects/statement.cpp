#include "statement.hpp"
#include "../better_sqlite3_impl.hpp"

v8::Local<v8 ::Function> Statement::Init(v8::Isolate *isolate,
                                         v8::Local<v8 ::External> data) {
  v8::Local<v8::FunctionTemplate> t =
      NewConstructorTemplate(isolate, data, JS_new, "Statement");
  SetPrototypeMethod(isolate, data, t, "run", JS_run);
  SetPrototypeMethod(isolate, data, t, "get", JS_get);
  SetPrototypeMethod(isolate, data, t, "all", JS_all);
  SetPrototypeMethod(isolate, data, t, "iterate", JS_iterate);
  SetPrototypeMethod(isolate, data, t, "bind", JS_bind);
  SetPrototypeMethod(isolate, data, t, "pluck", JS_pluck);
  SetPrototypeMethod(isolate, data, t, "expand", JS_expand);
  SetPrototypeMethod(isolate, data, t, "raw", JS_raw);
  SetPrototypeMethod(isolate, data, t, "safeIntegers", JS_safeIntegers);
  SetPrototypeMethod(isolate, data, t, "columns", JS_columns);
  SetPrototypeGetter(isolate, data, t, "busy", JS_busy);
  return t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
}
BindMap *Statement::GetBindMap(v8::Isolate *isolate) {
  if (has_bind_map)
    return &extras->bind_map;
  BindMap *bind_map = &extras->bind_map;
  int param_count = sqlite3_bind_parameter_count(handle);
  for (int i = 1; i <= param_count; ++i) {
    const char *name = sqlite3_bind_parameter_name(handle, i);
    if (name != NULL)
      bind_map->Add(isolate, name + 1, i);
  }
  has_bind_map = true;
  return bind_map;
}
void Statement::CloseHandles() {
  if (alive) {
    alive = false;
    sqlite3_finalize(handle);
  }
}
Statement::~Statement() {
  if (alive)
    db->RemoveStatement(this);
  CloseHandles();
  delete extras;
}
Statement::Extras::Extras(sqlite3_uint64 id) : bind_map(0), id(id) {}
Statement::Statement(Database *db, sqlite3_stmt *handle, sqlite3_uint64 id,
                     bool returns_data)
    : node::ObjectWrap(), db(db), handle(handle), extras(new Extras(id)),
      alive(true), locked(false), bound(false), has_bind_map(false),
      safe_ints(db->GetState()->safe_ints), mode(Data::FLAT),
      returns_data(returns_data) {
  assert(db != NULL);
  assert(handle != NULL);
  assert(db->GetState()->open);
  assert(!db->GetState()->busy);
  db->AddStatement(this);
}
void Statement::JS_new(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Addon *addon = static_cast<Addon *>(info.Data().As<v8 ::External>()->Value());
  if (!addon->privileged_info) {
    return ThrowTypeError(
        "Statements can only be constructed by the db.prepare() method");
  }
  assert(info.IsConstructCall());
  Database *db =
      node ::ObjectWrap ::Unwrap<Database>(addon->privileged_info->This());
  if (!db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");

  v8::Local<v8::String> source = (*addon->privileged_info)[0].As<v8::String>();
  v8::Local<v8::Object> database =
      (*addon->privileged_info)[1].As<v8::Object>();
  bool pragmaMode = (*addon->privileged_info)[2].As<v8::Boolean>()->Value();
  int flags = SQLITE_PREPARE_PERSISTENT;

  if (pragmaMode) {
    if (!db->GetState()->unsafe_mode) {
      if (db->GetState()->iterators)
        return ThrowTypeError(
            "This database connection is busy executing a query");
    }
    ((void)0);
    flags = 0;
  }

  v8 ::Isolate *isolate = info.GetIsolate();
  v8::String::Utf8Value utf8(isolate, source);
  sqlite3_stmt *handle;
  const char *tail;

  if (sqlite3_prepare_v3(db->GetHandle(), *utf8, utf8.length() + 1, flags,
                         &handle, &tail) != SQLITE_OK) {
    return db->ThrowDatabaseError();
  }
  if (handle == NULL) {
    return ThrowRangeError("The supplied SQL string contains no statements");
  }

  for (char c; (c = *tail);) {
    if (IS_SKIPPED(c)) {
      ++tail;
      continue;
    }
    if (c == '/' && tail[1] == '*') {
      tail += 2;
      for (char c; (c = *tail); ++tail) {
        if (c == '*' && tail[1] == '/') {
          tail += 2;
          break;
        }
      }
    } else if (c == '-' && tail[1] == '-') {
      tail += 2;
      for (char c; (c = *tail); ++tail) {
        if (c == '\n') {
          ++tail;
          break;
        }
      }
    } else {
      sqlite3_finalize(handle);
      return ThrowRangeError(
          "The supplied SQL string contains more than one statement");
    }
  }

  v8 ::Local<v8 ::Context> ctx = isolate->GetCurrentContext();
  bool returns_data = sqlite3_column_count(handle) >= 1 || pragmaMode;
  Statement *stmt = new Statement(db, handle, addon->NextId(), returns_data);
  stmt->Wrap(info.This());
  SetFrozen(isolate, ctx, info.This(), addon->cs.reader,
            v8::Boolean::New(isolate, returns_data));
  SetFrozen(isolate, ctx, info.This(), addon->cs.readonly,
            v8::Boolean::New(isolate, sqlite3_stmt_readonly(handle) != 0));
  SetFrozen(isolate, ctx, info.This(), addon->cs.source, source);
  SetFrozen(isolate, ctx, info.This(), addon->cs.database, database);

  info.GetReturnValue().Set(info.This());
}
void Statement::JS_run(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  ((void)0);
  sqlite3_stmt *handle = stmt->handle;
  Database *db = stmt->db;
  if (!db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
  if (!db->GetState()->unsafe_mode) {
    if (db->GetState()->iterators)
      return ThrowTypeError(
          "This database connection is busy executing a query");
  }
  ((void)0);
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
  db->GetState()->busy = true;
  v8 ::Isolate *isolate = info.GetIsolate();
  if (db->Log(isolate, handle)) {
    db->GetState()->busy = false;
    db->ThrowDatabaseError();
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  }
  ((void)0);
  sqlite3 *db_handle = db->GetHandle();
  int total_changes_before = sqlite3_total_changes(db_handle);

  sqlite3_step(handle);
  if (sqlite3_reset(handle) == SQLITE_OK) {
    int changes = sqlite3_total_changes(db_handle) == total_changes_before
                      ? 0
                      : sqlite3_changes(db_handle);
    sqlite3_int64 id = sqlite3_last_insert_rowid(db_handle);
    Addon *addon = db->GetAddon();
    v8 ::Local<v8 ::Context> ctx = isolate->GetCurrentContext();
    v8::Local<v8::Object> result = v8::Object::New(isolate);
    result
        ->Set(ctx, addon->cs.changes.Get(isolate),
              v8::Int32::New(isolate, changes))
        .FromJust();
    result
        ->Set(ctx, addon->cs.lastInsertRowid.Get(isolate),
              stmt->safe_ints
                  ? v8::BigInt::New(isolate, id).As<v8::Value>()
                  : v8::Number::New(isolate, (double)id).As<v8::Value>())
        .FromJust();
    db->GetState()->busy = false;
    info.GetReturnValue().Set(result);
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  }
  db->GetState()->busy = false;
  db->ThrowDatabaseError();
  if (!bound) {
    sqlite3_clear_bindings(handle);
  }
  return;
}
void Statement::JS_get(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (!stmt->returns_data)
    return ThrowTypeError(
        "This statement does not return data. Use run() instead");
  sqlite3_stmt *handle = stmt->handle;
  Database *db = stmt->db;
  if (!db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
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
  db->GetState()->busy = true;
  v8 ::Isolate *isolate = info.GetIsolate();
  if (db->Log(isolate, handle)) {
    db->GetState()->busy = false;
    db->ThrowDatabaseError();
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  }
  ((void)0);
  int status = sqlite3_step(handle);
  if (status == SQLITE_ROW) {
    v8::Local<v8::Value> result =
        Data::GetRowJS(isolate, isolate->GetCurrentContext(), handle,
                       stmt->safe_ints, stmt->mode);
    sqlite3_reset(handle);
    db->GetState()->busy = false;
    info.GetReturnValue().Set(result);
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  } else if (status == SQLITE_DONE) {
    sqlite3_reset(handle);
    db->GetState()->busy = false;
    info.GetReturnValue().Set(v8 ::Undefined(isolate));
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  }
  sqlite3_reset(handle);
  db->GetState()->busy = false;
  db->ThrowDatabaseError();
  if (!bound) {
    sqlite3_clear_bindings(handle);
  }
  return;
}
void Statement::JS_all(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (!stmt->returns_data)
    return ThrowTypeError(
        "This statement does not return data. Use run() instead");
  sqlite3_stmt *handle = stmt->handle;
  Database *db = stmt->db;
  if (!db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
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
  db->GetState()->busy = true;
  v8 ::Isolate *isolate = info.GetIsolate();
  if (db->Log(isolate, handle)) {
    db->GetState()->busy = false;
    db->ThrowDatabaseError();
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  }
  ((void)0);
  v8 ::Local<v8 ::Context> ctx = isolate->GetCurrentContext();
  v8::Local<v8::Array> result = v8::Array::New(isolate, 0);
  uint32_t row_count = 0;
  const bool safe_ints = stmt->safe_ints;
  const char mode = stmt->mode;
  bool js_error = false;

  while (sqlite3_step(handle) == SQLITE_ROW) {
    if (row_count == 0xffffffff) {
      ThrowRangeError("Array overflow (too many rows returned)");
      js_error = true;
      break;
    }
    result
        ->Set(ctx, row_count++,
              Data::GetRowJS(isolate, ctx, handle, safe_ints, mode))
        .FromJust();
  }

  if (sqlite3_reset(handle) == SQLITE_OK && !js_error) {
    db->GetState()->busy = false;
    info.GetReturnValue().Set(result);
    if (!bound) {
      sqlite3_clear_bindings(handle);
    }
    return;
  }
  if (js_error)
    db->GetState()->was_js_error = true;
  db->GetState()->busy = false;
  db->ThrowDatabaseError();
  if (!bound) {
    sqlite3_clear_bindings(handle);
  }
  return;
}
void Statement::JS_iterate(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Addon *addon = static_cast<Addon *>(info.Data().As<v8 ::External>()->Value());
  v8 ::Isolate *isolate = info.GetIsolate();
  v8::Local<v8::Function> c = addon->StatementIterator.Get(isolate);
  addon->privileged_info = &info;
  v8::MaybeLocal<v8::Object> maybeIterator =
      c->NewInstance(isolate->GetCurrentContext(), 0, NULL);
  addon->privileged_info = NULL;
  if (!maybeIterator.IsEmpty())
    info.GetReturnValue().Set(maybeIterator.ToLocalChecked());
}
void Statement::JS_bind(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (stmt->bound)
    return ThrowTypeError(
        "The bind() method can only be invoked once per statement object");
  if (!stmt->db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (stmt->db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
  Binder binder(stmt->handle);
  if (!binder.Bind(info, info.Length(), stmt)) {
    sqlite3_clear_bindings(stmt->handle);
    return;
  }
  ((void)0);
  stmt->bound = true;
  info.GetReturnValue().Set(info.This());
}
void Statement::JS_pluck(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (!stmt->returns_data)
    return ThrowTypeError(
        "The pluck() method is only for statements that return data");
  if (stmt->db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
  bool use = true;
  if (info.Length() != 0) {
    if (info.Length() <= (0) || !info[0]->IsBoolean())
      return ThrowTypeError("Expected "
                            "first"
                            " argument to be "
                            "a boolean");
    use = (info[0].As<v8 ::Boolean>())->Value();
  }
  stmt->mode = use                         ? Data::PLUCK
               : stmt->mode == Data::PLUCK ? Data::FLAT
                                           : stmt->mode;
  info.GetReturnValue().Set(info.This());
}
void Statement::JS_expand(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (!stmt->returns_data)
    return ThrowTypeError(
        "The expand() method is only for statements that return data");
  if (stmt->db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
  bool use = true;
  if (info.Length() != 0) {
    if (info.Length() <= (0) || !info[0]->IsBoolean())
      return ThrowTypeError("Expected "
                            "first"
                            " argument to be "
                            "a boolean");
    use = (info[0].As<v8 ::Boolean>())->Value();
  }
  stmt->mode = use                          ? Data::EXPAND
               : stmt->mode == Data::EXPAND ? Data::FLAT
                                            : stmt->mode;
  info.GetReturnValue().Set(info.This());
}
void Statement::JS_raw(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (!stmt->returns_data)
    return ThrowTypeError(
        "The raw() method is only for statements that return data");
  if (stmt->db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
  bool use = true;
  if (info.Length() != 0) {
    if (info.Length() <= (0) || !info[0]->IsBoolean())
      return ThrowTypeError("Expected "
                            "first"
                            " argument to be "
                            "a boolean");
    use = (info[0].As<v8 ::Boolean>())->Value();
  }
  stmt->mode = use                       ? Data::RAW
               : stmt->mode == Data::RAW ? Data::FLAT
                                         : stmt->mode;
  info.GetReturnValue().Set(info.This());
}
void Statement::JS_safeIntegers(
    v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (stmt->db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (stmt->locked)
    return ThrowTypeError("This statement is busy executing a query");
  if (info.Length() == 0)
    stmt->safe_ints = true;
  else {
    if (info.Length() <= (0) || !info[0]->IsBoolean())
      return ThrowTypeError("Expected "
                            "first"
                            " argument to be "
                            "a boolean");
    stmt->safe_ints = (info[0].As<v8 ::Boolean>())->Value();
  }
  info.GetReturnValue().Set(info.This());
}
void Statement::JS_columns(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  if (!stmt->returns_data)
    return ThrowTypeError(
        "The columns() method is only for statements that return data");
  if (!stmt->db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (stmt->db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  Addon *addon = stmt->db->GetAddon();
  v8 ::Isolate *isolate = info.GetIsolate();
  v8 ::Local<v8 ::Context> ctx = isolate->GetCurrentContext();

  int column_count = sqlite3_column_count(stmt->handle);
  v8::Local<v8::Array> columns = v8::Array::New(isolate);

  v8::Local<v8::String> name = addon->cs.name.Get(isolate);
  v8::Local<v8::String> columnName = addon->cs.column.Get(isolate);
  v8::Local<v8::String> tableName = addon->cs.table.Get(isolate);
  v8::Local<v8::String> databaseName = addon->cs.database.Get(isolate);
  v8::Local<v8::String> typeName = addon->cs.type.Get(isolate);

  for (int i = 0; i < column_count; ++i) {
    v8::Local<v8::Object> column = v8::Object::New(isolate);

    column
        ->Set(ctx, name,
              InternalizedFromUtf8OrNull(
                  isolate, sqlite3_column_name(stmt->handle, i), -1))
        .FromJust();
    column
        ->Set(ctx, columnName,
              InternalizedFromUtf8OrNull(
                  isolate, sqlite3_column_origin_name(stmt->handle, i), -1))
        .FromJust();
    column
        ->Set(ctx, tableName,
              InternalizedFromUtf8OrNull(
                  isolate, sqlite3_column_table_name(stmt->handle, i), -1))
        .FromJust();
    column
        ->Set(ctx, databaseName,
              InternalizedFromUtf8OrNull(
                  isolate, sqlite3_column_database_name(stmt->handle, i), -1))
        .FromJust();
    column
        ->Set(ctx, typeName,
              InternalizedFromUtf8OrNull(
                  isolate, sqlite3_column_decltype(stmt->handle, i), -1))
        .FromJust();

    columns->Set(ctx, i, column).FromJust();
  }

  info.GetReturnValue().Set(columns);
}
void Statement::JS_busy(v8::Local<v8 ::Name> _,
                        v8::PropertyCallbackInfo<v8 ::Value> const &info) {
  Statement *stmt = node ::ObjectWrap ::Unwrap<Statement>(info.This());
  info.GetReturnValue().Set(stmt->alive && stmt->locked);
}
