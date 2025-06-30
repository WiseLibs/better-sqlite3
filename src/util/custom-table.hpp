#ifndef BETTER_SQLITE3_UTIL_CUSTOM_TABLE_HPP
#define BETTER_SQLITE3_UTIL_CUSTOM_TABLE_HPP

#include "../better_sqlite3_deps.hpp"
#include "data-converter.hpp"

// Forward declarations
struct Addon;
class Database;

class CustomTable {
public:
  explicit CustomTable(v8::Isolate *isolate, Database *db, char const *name,
                       v8::Local<v8::Function> factory);
  static void Destructor(void *self);
  static sqlite3_module MODULE;
  static sqlite3_module EPONYMOUS_MODULE;

private:
  class VTab {
    friend class CustomTable;
    explicit VTab(CustomTable *parent, v8::Local<v8::Function> generator,
                  std::vector<std::string> parameter_names, bool safe_ints);
    static CustomTable::VTab *Upcast(sqlite3_vtab *vtab);
    sqlite3_vtab *Downcast();
    sqlite3_vtab base;
    CustomTable *const parent;
    int const parameter_count;
    bool const safe_ints;
    v8::Global<v8::Function> const generator;
    std::vector<std::string> const parameter_names;
  };
  class Cursor {
    friend class CustomTable;
    static CustomTable::Cursor *Upcast(sqlite3_vtab_cursor *cursor);
    sqlite3_vtab_cursor *Downcast();
    CustomTable::VTab *GetVTab();
    sqlite3_vtab_cursor base;
    v8::Global<v8::Object> iterator;
    v8::Global<v8::Function> next;
    v8::Global<v8::Array> row;
    bool done;
    sqlite_int64 rowid;
  };
  class TempDataConverter : DataConverter {
    friend class CustomTable;
    explicit TempDataConverter(CustomTable *parent);
    void PropagateJSError(sqlite3_context *invocation);
    std::string GetDataErrorPrefix();
    CustomTable *const parent;
    int status;
  };
  static int xCreate(sqlite3 *db_handle, void *_self, int argc,
                     char const *const *argv, sqlite3_vtab **output,
                     char **errOutput);
  static int xConnect(sqlite3 *db_handle, void *_self, int argc,
                      char const *const *argv, sqlite3_vtab **output,
                      char **errOutput);
  static int xDisconnect(sqlite3_vtab *vtab);
  static int xOpen(sqlite3_vtab *vtab, sqlite3_vtab_cursor **output);
  static int xClose(sqlite3_vtab_cursor *cursor);
  static int xFilter(sqlite3_vtab_cursor *_cursor, int idxNum,
                     char const *idxStr, int argc, sqlite3_value **argv);
  static int xNext(sqlite3_vtab_cursor *_cursor);
  static int xEof(sqlite3_vtab_cursor *cursor);
  static int xColumn(sqlite3_vtab_cursor *_cursor, sqlite3_context *invocation,
                     int column);
  static int xRowid(sqlite3_vtab_cursor *cursor, sqlite_int64 *output);
  static int xBestIndex(sqlite3_vtab *vtab, sqlite3_index_info *output);
  void PropagateJSError();
  Addon *const addon;
  v8::Isolate *const isolate;
  Database *const db;
  std::string const name;
  v8::Global<v8::Function> const factory;
};
LZZ_INLINE CustomTable::VTab *CustomTable::VTab::Upcast(sqlite3_vtab *vtab) {
  return reinterpret_cast<VTab *>(vtab);
}
LZZ_INLINE sqlite3_vtab *CustomTable::VTab::Downcast() {
  return reinterpret_cast<sqlite3_vtab *>(this);
}
LZZ_INLINE CustomTable::Cursor *
CustomTable::Cursor::Upcast(sqlite3_vtab_cursor *cursor) {
  return reinterpret_cast<Cursor *>(cursor);
}
LZZ_INLINE sqlite3_vtab_cursor *CustomTable::Cursor::Downcast() {
  return reinterpret_cast<sqlite3_vtab_cursor *>(this);
}
LZZ_INLINE CustomTable::VTab *CustomTable::Cursor::GetVTab() {
  return VTab::Upcast(base.pVtab);
}

#endif // BETTER_SQLITE3_UTIL_CUSTOM_TABLE_HPP
