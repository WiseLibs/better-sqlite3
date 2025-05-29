#ifndef BETTER_SQLITE3_OBJECTS_BACKUP_HPP
#define BETTER_SQLITE3_OBJECTS_BACKUP_HPP

#include "../better_sqlite3_deps.hpp"

// Forward declarations
class Database;

class Backup : public node::ObjectWrap {
public:
  static v8::Local<v8::Function> Init(v8::Isolate *isolate,
                                      v8::Local<v8::External> data);
  static bool Compare(Backup const *const a, Backup const *const b);
  void CloseHandles();
  ~Backup();

private:
  explicit Backup(Database *db, sqlite3 *dest_handle,
                  sqlite3_backup *backup_handle, sqlite3_uint64 id,
                  bool unlink);
  static void JS_new(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_transfer(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_close(v8::FunctionCallbackInfo<v8::Value> const &info);
  Database *const db;
  sqlite3 *const dest_handle;
  sqlite3_backup *const backup_handle;
  sqlite3_uint64 const id;
  bool alive;
  bool unlink;
};
LZZ_INLINE bool Backup::Compare(Backup const *const a, Backup const *const b) {
  return a->id < b->id;
}

#endif // BETTER_SQLITE3_OBJECTS_BACKUP_HPP
