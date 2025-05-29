#ifndef BETTER_SQLITE3_OBJECTS_DATABASE_HPP
#define BETTER_SQLITE3_OBJECTS_DATABASE_HPP

#include "../better_sqlite3_deps.hpp"

// Forward declarations
struct Addon;
class Statement;
class Backup;

class Database : public node::ObjectWrap {
public:
  static v8::Local<v8 ::Function> Init(v8::Isolate *isolate,
                                       v8::Local<v8 ::External> data);
  class CompareDatabase {
  public:
    bool operator()(Database const *const a, Database const *const b) const;
  };
  class CompareStatement {
  public:
    bool operator()(Statement const *const a, Statement const *const b) const;
  };
  class CompareBackup {
  public:
    bool operator()(Backup const *const a, Backup const *const b) const;
  };
  void ThrowDatabaseError();
  static void ThrowSqliteError(Addon *addon, sqlite3 *db_handle);
  static void ThrowSqliteError(Addon *addon, char const *message, int code);
  bool Log(v8::Isolate *isolate, sqlite3_stmt *handle);
  void AddStatement(Statement *stmt);
  void RemoveStatement(Statement *stmt);
  void AddBackup(Backup *backup);
  void RemoveBackup(Backup *backup);
  struct State {
    bool const open;
    bool busy;
    bool const safe_ints;
    bool const unsafe_mode;
    bool was_js_error;
    bool const has_logger;
    unsigned short int iterators;
    Addon *const addon;
  };
  State *GetState();
  sqlite3 *GetHandle();
  Addon *GetAddon();
  void CloseHandles();
  ~Database();

private:
  explicit Database(v8::Isolate *isolate, Addon *addon, sqlite3 *db_handle,
                    v8::Local<v8::Value> logger);
  static void JS_new(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_prepare(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_exec(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_backup(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_serialize(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_function(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_aggregate(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_table(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void
  JS_loadExtension(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_close(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void
  JS_defaultSafeIntegers(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_unsafeMode(v8::FunctionCallbackInfo<v8 ::Value> const &info);
  static void JS_open(v8::Local<v8 ::Name> _,
                      v8::PropertyCallbackInfo<v8 ::Value> const &info);
  static void
  JS_inTransaction(v8::Local<v8 ::Name> _,
                   v8::PropertyCallbackInfo<v8 ::Value> const &info);
  static bool Deserialize(v8::Local<v8::Object> buffer, Addon *addon,
                          sqlite3 *db_handle, bool readonly);
  static void FreeSerialization(char *data, void *_);
  static int const
      MAX_BUFFER_SIZE = node::Buffer::kMaxLength > INT_MAX
                            ? INT_MAX
                            : static_cast<int>(node::Buffer::kMaxLength);
  static int const
      MAX_STRING_SIZE = v8::String::kMaxLength > INT_MAX
                            ? INT_MAX
                            : static_cast<int>(v8::String::kMaxLength);
  sqlite3 *const db_handle;
  bool open;
  bool busy;
  bool safe_ints;
  bool unsafe_mode;
  bool was_js_error;
  bool const has_logger;
  unsigned short int iterators;
  Addon *const addon;
  v8::Global<v8::Value> const logger;
  std::set<Statement *, CompareStatement> stmts;
  std::set<Backup *, CompareBackup> backups;
};
LZZ_INLINE void Database::AddStatement(Statement *stmt) {
  stmts.insert(stmts.end(), stmt);
}
LZZ_INLINE void Database::RemoveStatement(Statement *stmt) {
  stmts.erase(stmt);
}
LZZ_INLINE void Database::AddBackup(Backup *backup) {
  backups.insert(backups.end(), backup);
}
LZZ_INLINE void Database::RemoveBackup(Backup *backup) {
  backups.erase(backup);
}
LZZ_INLINE Database::State *Database::GetState() {
  // Cast Database members to State struct - members layout must match exactly
  // State: {open, busy, safe_ints, unsafe_mode, was_js_error, has_logger, iterators, addon}
  // This relies on the fact that Database members from 'open' onwards have identical layout to State
  static_assert(std::is_standard_layout_v<State>, "State must have standard layout for safe casting");
  return reinterpret_cast<State *>(&open);
}
LZZ_INLINE sqlite3 *Database::GetHandle() { return db_handle; }
LZZ_INLINE Addon *Database::GetAddon() { return addon; }

#endif // BETTER_SQLITE3_OBJECTS_DATABASE_HPP
