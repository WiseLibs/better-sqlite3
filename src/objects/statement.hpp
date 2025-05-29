#ifndef BETTER_SQLITE3_OBJECTS_STATEMENT_HPP
#define BETTER_SQLITE3_OBJECTS_STATEMENT_HPP

#include "../better_sqlite3_deps.hpp"
#include "../util/bind-map.hpp"
#include "../util/data.hpp"
#include "database.hpp"

class Statement : public node::ObjectWrap {
  friend class StatementIterator;

public:
  static v8::Local<v8::Function> Init(v8::Isolate *isolate,
                                      v8::Local<v8::External> data);
  static bool Compare(Statement const *const a, Statement const *const b);
  BindMap *GetBindMap(v8::Isolate *isolate);
  void CloseHandles();
  ~Statement();

private:
  class Extras {
    friend class Statement;
    explicit Extras(sqlite3_uint64 id);
    BindMap bind_map;
    sqlite3_uint64 const id;
  };
  explicit Statement(Database *db, sqlite3_stmt *handle, sqlite3_uint64 id,
                     bool returns_data);
  static void JS_new(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_run(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_get(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_all(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_iterate(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_bind(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_pluck(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_expand(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_raw(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_safeIntegers(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_columns(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_busy(v8::Local<v8::Name> _,
                      v8::PropertyCallbackInfo<v8::Value> const &info);
  Database *const db;
  sqlite3_stmt *const handle;
  Extras *const extras;
  bool alive;
  bool locked;
  bool bound;
  bool has_bind_map;
  bool safe_ints;
  char mode;
  bool const returns_data;
};
LZZ_INLINE bool Statement::Compare(Statement const *const a,
                                   Statement const *const b) {
  return a->extras->id < b->extras->id;
}

#endif // BETTER_SQLITE3_OBJECTS_STATEMENT_HPP
