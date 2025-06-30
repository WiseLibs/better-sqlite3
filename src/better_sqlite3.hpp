#ifndef BETTER_SQLITE3_HPP
#define BETTER_SQLITE3_HPP

#include "better_sqlite3_deps.hpp"

// Forward declarations
struct Addon;
class Statement;
class Backup;
class Database;

// Include all component headers
#include "objects/backup.hpp"
#include "objects/database.hpp"
#include "objects/statement-iterator.hpp"
#include "objects/statement.hpp"
#include "util/bind-map.hpp"
#include "util/binder.hpp"
#include "util/constants.hpp"
#include "util/custom-aggregate.hpp"
#include "util/custom-function.hpp"
#include "util/custom-table.hpp"
#include "util/data-converter.hpp"
#include "util/data.hpp"
#include "util/macros.hpp"

// Addon struct definition
struct Addon {
  static void
  JS_setErrorConstructor(v8::FunctionCallbackInfo<v8::Value> const &info);
  static void Cleanup(void *ptr);
  explicit Addon(v8::Isolate *isolate);
  sqlite3_uint64 NextId();
  v8::Global<v8::Function> Statement;
  v8::Global<v8::Function> StatementIterator;
  v8::Global<v8::Function> Backup;
  v8::Global<v8::Function> SqliteError;
  v8::FunctionCallbackInfo<v8::Value> const *privileged_info;
  sqlite3_uint64 next_id;
  CS cs;
  std::set<Database *, Database::CompareDatabase> dbs;
};

// Addon inline implementation
LZZ_INLINE sqlite3_uint64 Addon::NextId() { return next_id++; }

#undef LZZ_INLINE

#endif // BETTER_SQLITE3_HPP
