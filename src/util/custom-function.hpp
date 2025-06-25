#ifndef BETTER_SQLITE3_UTIL_CUSTOM_FUNCTION_HPP
#define BETTER_SQLITE3_UTIL_CUSTOM_FUNCTION_HPP

#include "../better_sqlite3_deps.hpp"
#include "data-converter.hpp"

// Forward declarations
class Database;

class CustomFunction : protected DataConverter {
public:
  explicit CustomFunction(v8::Isolate *isolate, Database *db, char const *name,
                          v8::Local<v8::Function> fn, bool safe_ints);
  virtual ~CustomFunction();
  static void xDestroy(void *self);
  static void xFunc(sqlite3_context *invocation, int argc,
                    sqlite3_value **argv);

protected:
  void PropagateJSError(sqlite3_context *invocation);
  std::string GetDataErrorPrefix();

private:
  std::string const name;
  Database *const db;

protected:
  v8::Isolate *const isolate;
  v8::Global<v8::Function> const fn;
  bool const safe_ints;
};

#endif // BETTER_SQLITE3_UTIL_CUSTOM_FUNCTION_HPP
