#include "backup.hpp"
#include "../better_sqlite3_impl.hpp"

v8::Local<v8::Function> Backup::Init(v8::Isolate *isolate,
                                     v8::Local<v8::External> data) {
  v8::Local<v8::FunctionTemplate> t =
      NewConstructorTemplate(isolate, data, JS_new, "Backup");
  SetPrototypeMethod(isolate, data, t, "transfer", JS_transfer);
  SetPrototypeMethod(isolate, data, t, "close", JS_close);
  return t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
}
void Backup::CloseHandles() {
  if (alive) {
    alive = false;
    std::string filename(sqlite3_db_filename(dest_handle, "main"));
    sqlite3_backup_finish(backup_handle);
    int status = sqlite3_close(dest_handle);
    assert(status == SQLITE_OK);
    ((void)status);
    if (unlink)
      remove(filename.c_str());
  }
}
Backup::~Backup() {
  if (alive)
    db->RemoveBackup(this);
  CloseHandles();
}
Backup::Backup(Database *db, sqlite3 *dest_handle,
               sqlite3_backup *backup_handle, sqlite3_uint64 id, bool unlink)
    : node::ObjectWrap(), db(db), dest_handle(dest_handle),
      backup_handle(backup_handle), id(id), alive(true), unlink(unlink) {
  assert(db != NULL);
  assert(dest_handle != NULL);
  assert(backup_handle != NULL);
  db->AddBackup(this);
}
void Backup::JS_new(v8::FunctionCallbackInfo<v8::Value> const &info) {
  Addon *addon = static_cast<Addon *>(info.Data().As<v8::External>()->Value());
  if (!addon->privileged_info)
    return ThrowTypeError("Disabled constructor");
  assert(info.IsConstructCall());
  Database *db =
      node ::ObjectWrap ::Unwrap<Database>(addon->privileged_info->This());
  if (!db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  if (db->GetState()->busy)
    return ThrowTypeError("This database connection is busy executing a query");

  v8::Local<v8::Object> database =
      (*addon->privileged_info)[0].As<v8::Object>();
  v8::Local<v8::String> attachedName =
      (*addon->privileged_info)[1].As<v8::String>();
  v8::Local<v8::String> destFile =
      (*addon->privileged_info)[2].As<v8::String>();
  bool unlink = (*addon->privileged_info)[3].As<v8::Boolean>()->Value();

  v8::Isolate *isolate = info.GetIsolate();
  sqlite3 *dest_handle;
  v8::String::Utf8Value dest_file(isolate, destFile);
  v8::String::Utf8Value attached_name(isolate, attachedName);
  int mask = (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

  if (sqlite3_open_v2(*dest_file, &dest_handle, mask, NULL) != SQLITE_OK) {
    Database::ThrowSqliteError(addon, dest_handle);
    int status = sqlite3_close(dest_handle);
    assert(status == SQLITE_OK);
    ((void)status);
    return;
  }

  sqlite3_extended_result_codes(dest_handle, 1);
  sqlite3_limit(dest_handle, SQLITE_LIMIT_LENGTH, INT_MAX);
  sqlite3_backup *backup_handle =
      sqlite3_backup_init(dest_handle, "main", db->GetHandle(), *attached_name);
  if (backup_handle == NULL) {
    Database::ThrowSqliteError(addon, dest_handle);
    int status = sqlite3_close(dest_handle);
    assert(status == SQLITE_OK);
    ((void)status);
    return;
  }

  Backup *backup =
      new Backup(db, dest_handle, backup_handle, addon->NextId(), unlink);
  backup->Wrap(info.This());
  SetFrozen(isolate, isolate->GetCurrentContext(), info.This(),
            addon->cs.database, database);

  info.GetReturnValue().Set(info.This());
}
void Backup::JS_transfer(v8::FunctionCallbackInfo<v8::Value> const &info) {
  Backup *backup = node ::ObjectWrap ::Unwrap<Backup>(info.This());
  if (info.Length() <= (0) || !info[0]->IsInt32())
    return ThrowTypeError("Expected "
                          "first"
                          " argument to be "
                          "a 32-bit signed integer");
  int pages = (info[0].As<v8::Int32>())->Value();
  if (!backup->db->GetState()->open)
    return ThrowTypeError("The database connection is not open");
  assert(backup->db->GetState()->busy == false);
  assert(backup->alive == true);

  sqlite3_backup *backup_handle = backup->backup_handle;
  int status = sqlite3_backup_step(backup_handle, pages) & 0xff;

  Addon *addon = backup->db->GetAddon();
  if (status == SQLITE_OK || status == SQLITE_DONE || status == SQLITE_BUSY) {
    int total_pages = sqlite3_backup_pagecount(backup_handle);
    int remaining_pages = sqlite3_backup_remaining(backup_handle);
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
    v8::Local<v8::Object> result = v8::Object::New(isolate);
    result
        ->Set(ctx, addon->cs.totalPages.Get(isolate),
              v8::Int32::New(isolate, total_pages))
        .FromJust();
    result
        ->Set(ctx, addon->cs.remainingPages.Get(isolate),
              v8::Int32::New(isolate, remaining_pages))
        .FromJust();
    info.GetReturnValue().Set(result);
    if (status == SQLITE_DONE)
      backup->unlink = false;
  } else {
    Database::ThrowSqliteError(addon, sqlite3_errstr(status), status);
  }
}
void Backup::JS_close(v8::FunctionCallbackInfo<v8::Value> const &info) {
  Backup *backup = node ::ObjectWrap ::Unwrap<Backup>(info.This());
  assert(backup->db->GetState()->busy == false);
  if (backup->alive)
    backup->db->RemoveBackup(backup);
  backup->CloseHandles();
  info.GetReturnValue().Set(info.This());
}
