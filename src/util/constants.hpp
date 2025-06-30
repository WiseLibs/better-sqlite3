#ifndef BETTER_SQLITE3_UTIL_CONSTANTS_HPP
#define BETTER_SQLITE3_UTIL_CONSTANTS_HPP

#include "../better_sqlite3_deps.hpp"

class CS {
public:
  v8::Local<v8::String> Code(v8::Isolate *isolate, int code);
  explicit CS(v8::Isolate *isolate);
  v8::Global<v8::String> database;
  v8::Global<v8::String> reader;
  v8::Global<v8::String> source;
  v8::Global<v8::String> memory;
  v8::Global<v8::String> readonly;
  v8::Global<v8::String> name;
  v8::Global<v8::String> next;
  v8::Global<v8::String> length;
  v8::Global<v8::String> done;
  v8::Global<v8::String> value;
  v8::Global<v8::String> changes;
  v8::Global<v8::String> lastInsertRowid;
  v8::Global<v8::String> statement;
  v8::Global<v8::String> column;
  v8::Global<v8::String> table;
  v8::Global<v8::String> type;
  v8::Global<v8::String> totalPages;
  v8::Global<v8::String> remainingPages;

private:
  static void SetString(v8::Isolate *isolate, v8::Global<v8::String> &constant,
                        char const *str);
  void SetCode(v8::Isolate *isolate, int code, char const *str);
  std::unordered_map<int, v8::Global<v8::String>> codes;
};

#endif // BETTER_SQLITE3_UTIL_CONSTANTS_HPP
