#ifndef BETTER_SQLITE3_OBJECTS_STATEMENT_ITERATOR_HPP
#define BETTER_SQLITE3_OBJECTS_STATEMENT_ITERATOR_HPP

#include "../better_sqlite3_deps.hpp"
#include "database.hpp"

class StatementIterator : public node::ObjectWrap {
public:
  static v8::Local<v8::Function> Init(v8::Isolate *isolate,
                                      v8::Local<v8::External> data);
  ~StatementIterator();

private:
  explicit StatementIterator(Statement *stmt, bool bound);
  static void JS_new(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_next(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void JS_return(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void
  JS_symbolIterator(v8::FunctionCallbackInfo<v8::Value> const &info);
  void Next(v8::FunctionCallbackInfo<v8::Value> const &info);
  void Return(v8::FunctionCallbackInfo<v8::Value> const &info);
  void Throw();
  void Cleanup();
  static v8::Local<v8::Object> NewRecord(v8::Isolate *isolate,
                                         v8::Local<v8::Context> ctx,
                                         v8::Local<v8::Value> value,
                                         Addon *addon, bool done);
  static v8::Local<v8::Object> DoneRecord(v8::Isolate *isolate, Addon *addon);
  Statement *const stmt;
  sqlite3_stmt *const handle;
  Database::State *const db_state;
  bool const bound;
  bool const safe_ints;
  char const mode;
  bool alive;
  bool logged;
};
// Implementation moved to cpp file due to Addon dependency

#endif // BETTER_SQLITE3_OBJECTS_STATEMENT_ITERATOR_HPP
