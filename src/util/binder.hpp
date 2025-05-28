#ifndef BETTER_SQLITE3_UTIL_BINDER_HPP
#define BETTER_SQLITE3_UTIL_BINDER_HPP

#include "../better_sqlite3_deps.hpp"

// Forward declarations
class Statement;

bool IsPlainObject(v8::Isolate *isolate, v8::Local<v8::Object> obj);
class Binder {
public:
  explicit Binder(sqlite3_stmt *_handle);
  bool Bind(v8::FunctionCallbackInfo<v8 ::Value> const &info, int argc,
            Statement *stmt);

private:
  struct Result {
    int count;
    bool bound_object;
  };
  void Fail(void (*Throw)(char const *), char const *message);
  int NextAnonIndex();
  void BindValue(v8::Isolate *isolate, v8::Local<v8::Value> value, int index);
  int BindArray(v8::Isolate *isolate, v8::Local<v8::Array> arr);
  int BindObject(v8::Isolate *isolate, v8::Local<v8::Object> obj,
                 Statement *stmt);
  Result BindArgs(v8::FunctionCallbackInfo<v8 ::Value> const &info, int argc,
                  Statement *stmt);
  sqlite3_stmt *handle;
  int param_count;
  int anon_index;
  bool success;
};

#endif // BETTER_SQLITE3_UTIL_BINDER_HPP
