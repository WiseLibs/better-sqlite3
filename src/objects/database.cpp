#include "database.hpp"
#include "../better_sqlite3_impl.hpp"

v8::Local<v8 ::Function> Database::Init(v8::Isolate *isolate,
                                        v8::Local<v8 ::External> data) {
  v8::Local<v8::FunctionTemplate> t =
      NewConstructorTemplate(isolate, data, JS_new, "Database");
  SetPrototypeMethod(isolate, data, t, "prepare", JS_prepare);
  SetPrototypeMethod(isolate, data, t, "exec", JS_exec);
  SetPrototypeMethod(isolate, data, t, "backup", JS_backup);
  SetPrototypeMethod(isolate, data, t, "serialize", JS_serialize);
  SetPrototypeMethod(isolate, data, t, "function", JS_function);
  SetPrototypeMethod(isolate, data, t, "aggregate", JS_aggregate);
  SetPrototypeMethod(isolate, data, t, "table", JS_table);
  SetPrototypeMethod(isolate, data, t, "loadExtension", JS_loadExtension);
  SetPrototypeMethod(isolate, data, t, "close", JS_close);
  SetPrototypeMethod(isolate, data, t, "defaultSafeIntegers",
                     JS_defaultSafeIntegers);
  SetPrototypeMethod(isolate, data, t, "unsafeMode", JS_unsafeMode);
  SetPrototypeGetter(isolate, data, t, "open", JS_open);
  SetPrototypeGetter(isolate, data, t, "inTransaction", JS_inTransaction);
  return t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
}
bool Database::CompareDatabase::operator()(Database const *const a,
                                           Database const *const b) const {
  return a < b;
}
bool Database::CompareStatement::operator()(Statement const *const a,
                                            Statement const *const b) const {
  return Statement::Compare(a, b);
}
bool Database::CompareBackup::operator()(Backup const *const a,
                                         Backup const *const b) const {
  return Backup::Compare(a, b);
}
void Database::ThrowDatabaseError() {
  if (was_js_error)
    was_js_error = false;
  else
    ThrowSqliteError(addon, db_handle);
}
void Database::ThrowSqliteError(Addon *addon, sqlite3 *db_handle) {
  assert(db_handle != NULL);
  ThrowSqliteError(addon, sqlite3_errmsg(db_handle),
                   sqlite3_extended_errcode(db_handle));
}
void Database::ThrowSqliteError(Addon *addon, char const *message, int code) {
  assert(message != NULL);
  assert((code & 0xff) != SQLITE_OK);
  assert((code & 0xff) != SQLITE_ROW);
  assert((code & 0xff) != SQLITE_DONE);
  v8 ::Isolate *isolate = v8 ::Isolate ::GetCurrent();
  v8::Local<v8::Value> args[2] = {StringFromUtf8(isolate, message, -1),
                                  addon->cs.Code(isolate, code)};
  isolate->ThrowException(
      addon->SqliteError.Get(isolate)
          ->NewInstance(isolate->GetCurrentContext(), 2, args)
          .ToLocalChecked());
}
bool Database::Log(v8::Isolate *isolate, sqlite3_stmt *handle) {
  assert(was_js_error == false);
  if (!has_logger)
    return false;
  char *expanded = sqlite3_expanded_sql(handle);
  v8::Local<v8::Value> arg =
      StringFromUtf8(isolate, expanded ? expanded : sqlite3_sql(handle), -1);
  was_js_error =
      logger.Get(isolate)
          .As<v8::Function>()
          ->Call(isolate->GetCurrentContext(), v8::Undefined(isolate), 1, &arg)
          .IsEmpty();
  if (expanded)
    sqlite3_free(expanded);
  return was_js_error;
}
void Database::CloseHandles() {
  if (open) {
    open = false;
    for (Statement *stmt : stmts)
      stmt->CloseHandles();
    for (Backup *backup : backups)
      backup->CloseHandles();
    stmts.clear();
    backups.clear();
    int status = sqlite3_close(db_handle);
    assert(status == SQLITE_OK);
    ((void)status);
  }
}
Database::~Database() {
  if (open)
    addon->dbs.erase(this);
  CloseHandles();
}
Database::Database(v8::Isolate *isolate, Addon *addon, sqlite3 *db_handle,
                   v8::Local<v8::Value> logger)
    : node::ObjectWrap(), db_handle(db_handle), open(true), busy(false),
      safe_ints(false), unsafe_mode(false), was_js_error(false),
      has_logger(logger->IsFunction()), iterators(0), addon(addon),
      logger(isolate, logger), stmts(), backups() {
  assert(db_handle != NULL);
  addon->dbs.insert(this);
}
void Database::JS_new(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  assert(info.IsConstructCall());
  if (info.Length() <= (0) || !info[0]->IsString())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> filename = (info[0].As<v8 ::String>());
  if (info.Length() <= (1) || !info[1]->IsString())
    return ThrowTypeError("Expected "
                          "second"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> filenameGiven = (info[1].As<v8 ::String>());
  if (info.Length() <= (2) || !info[2]->IsBoolean())
    return ThrowTypeError("Expected "
                          "third"
                          " argument to be "
                          "a boolean");
  bool in_memory = (info[2].As<v8 ::Boolean>())->Value();
  if (info.Length() <= (3) || !info[3]->IsBoolean())
    return ThrowTypeError("Expected "
                          "fourth"
                          " argument to be "
                          "a boolean");
  bool readonly = (info[3].As<v8 ::Boolean>())->Value();
  if (info.Length() <= (4) || !info[4]->IsBoolean())
    return ThrowTypeError("Expected "
                          "fifth"
                          " argument to be "
                          "a boolean");
  bool must_exist = (info[4].As<v8 ::Boolean>())->Value();
  if (info.Length() <= (5) || !info[5]->IsInt32())
    return ThrowTypeError("Expected "
                          "sixth"
                          " argument to be "
                          "a 32-bit signed integer");
  int timeout = (info[5].As<v8 ::Int32>())->Value();
  if (info.Length() <= (6))
    return ThrowTypeError("Expected a "
                          "seventh"
                          " argument");
  v8 ::Local<v8 ::Value> logger = info[6];
  if (info.Length() <= (7))
    return ThrowTypeError("Expected a "
                          "eighth"
                          " argument");
  v8 ::Local<v8 ::Value> buffer = info[7];

  Addon *addon = static_cast<Addon *>(info.Data().As<v8 ::External>()->Value());
  v8 ::Isolate *isolate = info.GetIsolate();
  sqlite3 *db_handle;
  v8::String::Utf8Value utf8(isolate, filename);
  int mask = readonly     ? SQLITE_OPEN_READONLY
             : must_exist ? SQLITE_OPEN_READWRITE
                          : (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

  if (sqlite3_open_v2(*utf8, &db_handle, mask, NULL) != SQLITE_OK) {
    ThrowSqliteError(addon, db_handle);
    int status = sqlite3_close(db_handle);
    assert(status == SQLITE_OK);
    ((void)status);
    return;
  }

  assert(sqlite3_db_mutex(db_handle) == NULL);
  sqlite3_extended_result_codes(db_handle, 1);
  sqlite3_busy_timeout(db_handle, timeout);
  sqlite3_limit(db_handle, SQLITE_LIMIT_LENGTH,
                MAX_BUFFER_SIZE < MAX_STRING_SIZE ? MAX_BUFFER_SIZE
                                                  : MAX_STRING_SIZE);
  sqlite3_limit(db_handle, SQLITE_LIMIT_SQL_LENGTH, MAX_STRING_SIZE);
  int status = sqlite3_db_config(
      db_handle, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL);
  assert(status == SQLITE_OK);
  status = sqlite3_db_config(db_handle, SQLITE_DBCONFIG_DEFENSIVE, 1, NULL);
  assert(status == SQLITE_OK);

  if (node::Buffer::HasInstance(buffer) &&
      !Deserialize(buffer.As<v8::Object>(), addon, db_handle, readonly)) {
    int status = sqlite3_close(db_handle);
    assert(status == SQLITE_OK);
    ((void)status);
    return;
  }

  v8 ::Local<v8 ::Context> ctx = isolate->GetCurrentContext();
  Database *db = new Database(isolate, addon, db_handle, logger);
  db->Wrap(info.This());
  SetFrozen(isolate, ctx, info.This(), addon->cs.memory,
            v8::Boolean::New(isolate, in_memory));
  SetFrozen(isolate, ctx, info.This(), addon->cs.readonly,
            v8::Boolean::New(isolate, readonly));
  SetFrozen(isolate, ctx, info.This(), addon->cs.name, filenameGiven);

  info.GetReturnValue().Set(info.This());
}
void Database::JS_prepare(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  if (info.Length() <= (0) || !info[0]->IsString())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> source = (info[0].As<v8 ::String>());
  if (info.Length() <= (1) || !info[1]->IsObject())
    return ThrowTypeError("Expected "
                          "second"
                          " argument to be "
                          "an object");
  v8 ::Local<v8 ::Object> database = (info[1].As<v8 ::Object>());
  if (info.Length() <= (2) || !info[2]->IsBoolean())
    return ThrowTypeError("Expected "
                          "third"
                          " argument to be "
                          "a boolean");
  bool pragmaMode = (info[2].As<v8 ::Boolean>())->Value();
  (void)source;
  (void)database;
  (void)pragmaMode;
  Addon *addon = static_cast<Addon *>(info.Data().As<v8 ::External>()->Value());
  v8 ::Isolate *isolate = info.GetIsolate();
  v8::Local<v8::Function> c = addon->Statement.Get(isolate);
  addon->privileged_info = &info;
  v8::MaybeLocal<v8::Object> maybeStatement =
      c->NewInstance(isolate->GetCurrentContext(), 0, NULL);
  addon->privileged_info = NULL;
  if (!maybeStatement.IsEmpty())
    info.GetReturnValue().Set(maybeStatement.ToLocalChecked());
}
void Database::JS_exec(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() <= (0) || !info[0]->IsString())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> source = (info[0].As<v8 ::String>());
  if (!db->open)
    return ThrowTypeError("The database connection is not open");
  if (db->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (!db->unsafe_mode) {
    if (db->iterators)
      return ThrowTypeError(
          "This database connection is busy executing a query");
  }
  ((void)0);
  db->busy = true;

  v8 ::Isolate *isolate = info.GetIsolate();
  v8::String::Utf8Value utf8(isolate, source);
  const char *sql = *utf8;
  const char *tail;

  int status;
  const bool has_logger = db->has_logger;
  sqlite3 *const db_handle = db->db_handle;
  sqlite3_stmt *handle;

  for (;;) {
    while (IS_SKIPPED(*sql))
      ++sql;
    status = sqlite3_prepare_v2(db_handle, sql, -1, &handle, &tail);
    sql = tail;
    if (!handle)
      break;
    if (has_logger && db->Log(isolate, handle)) {
      sqlite3_finalize(handle);
      status = -1;
      break;
    }
    do
      status = sqlite3_step(handle);
    while (status == SQLITE_ROW);
    status = sqlite3_finalize(handle);
    if (status != SQLITE_OK)
      break;
  }

  db->busy = false;
  if (status != SQLITE_OK) {
    db->ThrowDatabaseError();
  }
}
void Database::JS_backup(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  if (info.Length() <= (0) || !info[0]->IsObject())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "an object");
  v8 ::Local<v8 ::Object> database = (info[0].As<v8 ::Object>());
  if (info.Length() <= (1) || !info[1]->IsString())
    return ThrowTypeError("Expected "
                          "second"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> attachedName = (info[1].As<v8 ::String>());
  if (info.Length() <= (2) || !info[2]->IsString())
    return ThrowTypeError("Expected "
                          "third"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> destFile = (info[2].As<v8 ::String>());
  if (info.Length() <= (3) || !info[3]->IsBoolean())
    return ThrowTypeError("Expected "
                          "fourth"
                          " argument to be "
                          "a boolean");
  bool unlink = (info[3].As<v8 ::Boolean>())->Value();
  (void)database;
  (void)attachedName;
  (void)destFile;
  (void)unlink;
  Addon *addon = static_cast<Addon *>(info.Data().As<v8 ::External>()->Value());
  v8 ::Isolate *isolate = info.GetIsolate();
  v8::Local<v8::Function> c = addon->Backup.Get(isolate);
  addon->privileged_info = &info;
  v8::MaybeLocal<v8::Object> maybeBackup =
      c->NewInstance(isolate->GetCurrentContext(), 0, NULL);
  addon->privileged_info = NULL;
  if (!maybeBackup.IsEmpty())
    info.GetReturnValue().Set(maybeBackup.ToLocalChecked());
}
void Database::JS_serialize(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() <= (0) || !info[0]->IsString())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> attachedName = (info[0].As<v8 ::String>());
  if (!db->open)
    return ThrowTypeError("The database connection is not open");
  if (db->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (db->iterators)
    return ThrowTypeError("This database connection is busy executing a query");

  v8 ::Isolate *isolate = info.GetIsolate();
  v8::String::Utf8Value attached_name(isolate, attachedName);
  sqlite3_int64 length = -1;
  unsigned char *data =
      sqlite3_serialize(db->db_handle, *attached_name, &length, 0);

  if (!data && length) {
    ThrowError("Out of memory");
    return;
  }

  info.GetReturnValue().Set(SAFE_NEW_BUFFER(isolate,
                                            reinterpret_cast<char *>(data),
                                            length, FreeSerialization, NULL)
                                .ToLocalChecked());
}
void Database::JS_function(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() <= (0) || !info[0]->IsFunction())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a function");
  v8 ::Local<v8 ::Function> fn = (info[0].As<v8 ::Function>());
  if (info.Length() <= (1) || !info[1]->IsString())
    return ThrowTypeError("Expected "
                          "second"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> nameString = (info[1].As<v8 ::String>());
  if (info.Length() <= (2) || !info[2]->IsInt32())
    return ThrowTypeError("Expected "
                          "third"
                          " argument to be "
                          "a 32-bit signed integer");
  int argc = (info[2].As<v8 ::Int32>())->Value();
  if (info.Length() <= (3) || !info[3]->IsInt32())
    return ThrowTypeError("Expected "
                          "fourth"
                          " argument to be "
                          "a 32-bit signed integer");
  int safe_ints = (info[3].As<v8 ::Int32>())->Value();
  if (info.Length() <= (4) || !info[4]->IsBoolean())
    return ThrowTypeError("Expected "
                          "fifth"
                          " argument to be "
                          "a boolean");
  bool deterministic = (info[4].As<v8 ::Boolean>())->Value();
  if (info.Length() <= (5) || !info[5]->IsBoolean())
    return ThrowTypeError("Expected "
                          "sixth"
                          " argument to be "
                          "a boolean");
  bool direct_only = (info[5].As<v8 ::Boolean>())->Value();
  if (!db->open)
    return ThrowTypeError("The database connection is not open");
  if (db->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (db->iterators)
    return ThrowTypeError("This database connection is busy executing a query");

  v8 ::Isolate *isolate = info.GetIsolate();
  v8::String::Utf8Value name(isolate, nameString);
  int mask = SQLITE_UTF8;
  if (deterministic)
    mask |= SQLITE_DETERMINISTIC;
  if (direct_only)
    mask |= SQLITE_DIRECTONLY;
  safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(db->safe_ints);

  if (sqlite3_create_function_v2(
          db->db_handle, *name, argc, mask,
          new CustomFunction(isolate, db, *name, fn, safe_ints),
          CustomFunction::xFunc, NULL, NULL,
          CustomFunction::xDestroy) != SQLITE_OK) {
    db->ThrowDatabaseError();
  }
}
void Database::JS_aggregate(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() <= (0))
    return ThrowTypeError("Expected a "
                          "first"
                          " argument");
  v8 ::Local<v8 ::Value> start = info[0];
  if (info.Length() <= (1) || !info[1]->IsFunction())
    return ThrowTypeError("Expected "
                          "second"
                          " argument to be "
                          "a function");
  v8 ::Local<v8 ::Function> step = (info[1].As<v8 ::Function>());
  if (info.Length() <= (2))
    return ThrowTypeError("Expected a "
                          "third"
                          " argument");
  v8 ::Local<v8 ::Value> inverse = info[2];
  if (info.Length() <= (3))
    return ThrowTypeError("Expected a "
                          "fourth"
                          " argument");
  v8 ::Local<v8 ::Value> result = info[3];
  if (info.Length() <= (4) || !info[4]->IsString())
    return ThrowTypeError("Expected "
                          "fifth"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> nameString = (info[4].As<v8 ::String>());
  if (info.Length() <= (5) || !info[5]->IsInt32())
    return ThrowTypeError("Expected "
                          "sixth"
                          " argument to be "
                          "a 32-bit signed integer");
  int argc = (info[5].As<v8 ::Int32>())->Value();
  if (info.Length() <= (6) || !info[6]->IsInt32())
    return ThrowTypeError("Expected "
                          "seventh"
                          " argument to be "
                          "a 32-bit signed integer");
  int safe_ints = (info[6].As<v8 ::Int32>())->Value();
  if (info.Length() <= (7) || !info[7]->IsBoolean())
    return ThrowTypeError("Expected "
                          "eighth"
                          " argument to be "
                          "a boolean");
  bool deterministic = (info[7].As<v8 ::Boolean>())->Value();
  if (info.Length() <= (8) || !info[8]->IsBoolean())
    return ThrowTypeError("Expected "
                          "ninth"
                          " argument to be "
                          "a boolean");
  bool direct_only = (info[8].As<v8 ::Boolean>())->Value();
  if (!db->open)
    return ThrowTypeError("The database connection is not open");
  if (db->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (db->iterators)
    return ThrowTypeError("This database connection is busy executing a query");

  v8 ::Isolate *isolate = info.GetIsolate();
  v8::String::Utf8Value name(isolate, nameString);
  auto xInverse = inverse->IsFunction() ? CustomAggregate::xInverse : NULL;
  auto xValue = xInverse ? CustomAggregate::xValue : NULL;
  int mask = SQLITE_UTF8;
  if (deterministic)
    mask |= SQLITE_DETERMINISTIC;
  if (direct_only)
    mask |= SQLITE_DIRECTONLY;
  safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(db->safe_ints);

  if (sqlite3_create_window_function(
          db->db_handle, *name, argc, mask,
          new CustomAggregate(isolate, db, *name, start, step, inverse, result,
                              safe_ints),
          CustomAggregate::xStep, CustomAggregate::xFinal, xValue, xInverse,
          CustomAggregate::xDestroy) != SQLITE_OK) {
    db->ThrowDatabaseError();
  }
}
void Database::JS_table(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() <= (0) || !info[0]->IsFunction())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a function");
  v8 ::Local<v8 ::Function> factory = (info[0].As<v8 ::Function>());
  if (info.Length() <= (1) || !info[1]->IsString())
    return ThrowTypeError("Expected "
                          "second"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> nameString = (info[1].As<v8 ::String>());
  if (info.Length() <= (2) || !info[2]->IsBoolean())
    return ThrowTypeError("Expected "
                          "third"
                          " argument to be "
                          "a boolean");
  bool eponymous = (info[2].As<v8 ::Boolean>())->Value();
  if (!db->open)
    return ThrowTypeError("The database connection is not open");
  if (db->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (db->iterators)
    return ThrowTypeError("This database connection is busy executing a query");

  v8 ::Isolate *isolate = info.GetIsolate();
  v8::String::Utf8Value name(isolate, nameString);
  sqlite3_module *module =
      eponymous ? &CustomTable::EPONYMOUS_MODULE : &CustomTable::MODULE;

  db->busy = true;
  if (sqlite3_create_module_v2(db->db_handle, *name, module,
                               new CustomTable(isolate, db, *name, factory),
                               CustomTable::Destructor) != SQLITE_OK) {
    db->ThrowDatabaseError();
  }
  db->busy = false;
}
void Database::JS_loadExtension(
    v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  v8::Local<v8::String> entryPoint;
  if (info.Length() <= (0) || !info[0]->IsString())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a string");
  v8 ::Local<v8 ::String> filename = (info[0].As<v8 ::String>());
  if (info.Length() > 1) {
    if (info.Length() <= (1) || !info[1]->IsString())
      return ThrowTypeError("Expected "
                            "second"
                            " argument to be "
                            "a string");
    entryPoint = (info[1].As<v8 ::String>());
  }
  if (!db->open)
    return ThrowTypeError("The database connection is not open");
  if (db->busy)
    return ThrowTypeError("This database connection is busy executing a query");
  if (db->iterators)
    return ThrowTypeError("This database connection is busy executing a query");
  v8 ::Isolate *isolate = info.GetIsolate();
  char *error;
  int status = sqlite3_load_extension(
      db->db_handle, *v8::String::Utf8Value(isolate, filename),
      entryPoint.IsEmpty() ? NULL : *v8::String::Utf8Value(isolate, entryPoint),
      &error);
  if (status != SQLITE_OK) {
    ThrowSqliteError(db->addon, error, status);
  }
  sqlite3_free(error);
}
void Database::JS_close(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (db->open) {
    if (db->busy)
      return ThrowTypeError(
          "This database connection is busy executing a query");
    if (db->iterators)
      return ThrowTypeError(
          "This database connection is busy executing a query");
    db->addon->dbs.erase(db);
    db->CloseHandles();
  }
}
void Database::JS_defaultSafeIntegers(
    v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() == 0)
    db->safe_ints = true;
  else {
    if (info.Length() <= (0) || !info[0]->IsBoolean())
      return ThrowTypeError("Expected "
                            "first"
                            " argument to be "
                            "a boolean");
    db->safe_ints = (info[0].As<v8 ::Boolean>())->Value();
  }
}
void Database::JS_unsafeMode(v8::FunctionCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  if (info.Length() == 0)
    db->unsafe_mode = true;
  else {
    if (info.Length() <= (0) || !info[0]->IsBoolean())
      return ThrowTypeError("Expected "
                            "first"
                            " argument to be "
                            "a boolean");
    db->unsafe_mode = (info[0].As<v8 ::Boolean>())->Value();
  }
  sqlite3_db_config(db->db_handle, SQLITE_DBCONFIG_DEFENSIVE,
                    static_cast<int>(!db->unsafe_mode), NULL);
}
void Database::JS_open(v8::Local<v8 ::Name> _,
                       v8::PropertyCallbackInfo<v8 ::Value> const &info) {
  info.GetReturnValue().Set(
      node ::ObjectWrap ::Unwrap<Database>(info.This())->open);
}
void Database::JS_inTransaction(
    v8::Local<v8 ::Name> _, v8::PropertyCallbackInfo<v8 ::Value> const &info) {
  Database *db = node ::ObjectWrap ::Unwrap<Database>(info.This());
  info.GetReturnValue().Set(
      db->open && !static_cast<bool>(sqlite3_get_autocommit(db->db_handle)));
}
bool Database::Deserialize(v8::Local<v8::Object> buffer, Addon *addon,
                           sqlite3 *db_handle, bool readonly) {
  size_t length = node::Buffer::Length(buffer);
  unsigned char *data = (unsigned char *)sqlite3_malloc64(length);
  unsigned int flags =
      SQLITE_DESERIALIZE_FREEONCLOSE | SQLITE_DESERIALIZE_RESIZEABLE;

  if (readonly) {
    flags |= SQLITE_DESERIALIZE_READONLY;
  }
  if (length) {
    if (!data) {
      ThrowError("Out of memory");
      return false;
    }
    memcpy(data, node::Buffer::Data(buffer), length);
  }

  int status =
      sqlite3_deserialize(db_handle, "main", data, length, length, flags);
  if (status != SQLITE_OK) {
    ThrowSqliteError(addon,
                     status == SQLITE_ERROR ? "unable to deserialize database"
                                            : sqlite3_errstr(status),
                     status);
    return false;
  }

  return true;
}
void Database::FreeSerialization(char *data, void *_) { sqlite3_free(data); }
int const Database::MAX_BUFFER_SIZE;
int const Database::MAX_STRING_SIZE;
