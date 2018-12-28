// better_sqlite3.hpp
//

#ifndef LZZ_BETTER_SQLITE3_better_sqlite3_hpp
#define LZZ_BETTER_SQLITE3_better_sqlite3_hpp
#line 2 "./src/better_sqlite3.lzz"
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <sqlite3.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_buffer.h>
#line 79 "./src/util/macros.lzz"
#if defined(V8_MAJOR_VERSION) && (V8_MAJOR_VERSION > 6 ||                        (V8_MAJOR_VERSION == 6 && defined(V8_MINOR_VERSION) && V8_MINOR_VERSION >= 2))
#define EXTRACT_STRING(isolate, string) isolate, string
#else
#define EXTRACT_STRING(_unused, string) string
#endif
#line 147 "./src/util/macros.lzz"
template <class T> using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;
#line 166 "./src/util/constants.lzz"
typedef v8::Persistent<v8::String> ConstantString;
#define LZZ_INLINE inline
#line 18 "./src/util/macros.lzz"
v8::Local <v8::String> StringFromUtf8 (v8::Isolate * isolate, char const * data, int length);
#line 21 "./src/util/macros.lzz"
v8::Local <v8::String> InternalizedFromUtf8 (v8::Isolate * isolate, char const * data, int length);
#line 25 "./src/util/macros.lzz"
v8::Local <v8::Value> InternalizedFromUtf8OrNull (v8::Isolate * isolate, char const * data, int length);
#line 30 "./src/util/macros.lzz"
void SetFrozen (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Object> obj, ConstantString & key, v8::Local <v8::Value> value);
#line 35 "./src/util/macros.lzz"
void ThrowError (char const * message);
#line 36 "./src/util/macros.lzz"
void ThrowTypeError (char const * message);
#line 37 "./src/util/macros.lzz"
void ThrowRangeError (char const * message);
#line 88 "./src/util/macros.lzz"
std::string CONCAT (char const * a, char const * b, char const * c);
#line 96 "./src/util/macros.lzz"
char const * COPY (char const * source);
#line 104 "./src/util/macros.lzz"
template <typename T>
#line 104 "./src/util/macros.lzz"
T * ALLOC_ARRAY (size_t count);
#line 109 "./src/util/macros.lzz"
template <typename T>
#line 109 "./src/util/macros.lzz"
void FREE_ARRAY (T * array_pointer);
#line 113 "./src/util/macros.lzz"
v8::Local <v8::Value> Require (v8::Local <v8::Object> module, char const * path);
#line 121 "./src/util/macros.lzz"
void NODE_SET_PROTOTYPE_GETTER (v8::Local <v8::FunctionTemplate> recv, char const * name, v8::AccessorGetterCallback getter);
#line 135 "./src/util/macros.lzz"
void NODE_SET_PROTOTYPE_SYMBOL_METHOD (v8::Local <v8::FunctionTemplate> recv, v8::Local <v8::Symbol> symbol, v8::FunctionCallback callback);
#line 1 "./src/util/constants.lzz"
class CS
{
#line 2 "./src/util/constants.lzz"
public:
#line 3 "./src/util/constants.lzz"
  static v8::Local <v8::String> Get (v8::Isolate * isolate, ConstantString & constant);
#line 6 "./src/util/constants.lzz"
  static v8::Local <v8::String> Code (v8::Isolate * isolate, int code);
#line 12 "./src/util/constants.lzz"
  static ConstantString database;
#line 13 "./src/util/constants.lzz"
  static ConstantString reader;
#line 14 "./src/util/constants.lzz"
  static ConstantString source;
#line 15 "./src/util/constants.lzz"
  static ConstantString memory;
#line 16 "./src/util/constants.lzz"
  static ConstantString readonly;
#line 17 "./src/util/constants.lzz"
  static ConstantString name;
#line 18 "./src/util/constants.lzz"
  static ConstantString next;
#line 19 "./src/util/constants.lzz"
  static ConstantString length;
#line 20 "./src/util/constants.lzz"
  static ConstantString done;
#line 21 "./src/util/constants.lzz"
  static ConstantString value;
#line 22 "./src/util/constants.lzz"
  static ConstantString changes;
#line 23 "./src/util/constants.lzz"
  static ConstantString lastInsertRowid;
#line 24 "./src/util/constants.lzz"
  static ConstantString code;
#line 25 "./src/util/constants.lzz"
  static ConstantString statement;
#line 26 "./src/util/constants.lzz"
  static ConstantString column;
#line 27 "./src/util/constants.lzz"
  static ConstantString table;
#line 28 "./src/util/constants.lzz"
  static ConstantString type;
#line 29 "./src/util/constants.lzz"
  static ConstantString filename;
#line 30 "./src/util/constants.lzz"
  static ConstantString pending;
#line 31 "./src/util/constants.lzz"
  static ConstantString completed;
#line 32 "./src/util/constants.lzz"
  static ConstantString aborted;
#line 33 "./src/util/constants.lzz"
  static ConstantString totalPages;
#line 34 "./src/util/constants.lzz"
  static ConstantString remainingPages;
#line 36 "./src/util/constants.lzz"
private:
#line 37 "./src/util/constants.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 37 "./src/util/constants.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 151 "./src/util/constants.lzz"
  static v8::Local <v8::String> InternalizedFromLatin1 (v8::Isolate * isolate, char const * str);
#line 154 "./src/util/constants.lzz"
  static void AddString (v8::Isolate * isolate, ConstantString & constant, char const * str);
#line 157 "./src/util/constants.lzz"
  static void AddCode (v8::Isolate * isolate, int code, char const * str);
#line 160 "./src/util/constants.lzz"
  explicit CS (char _);
#line 162 "./src/util/constants.lzz"
  static std::unordered_map <int, ConstantString> codes;
};
#line 1 "./src/util/bind-map.lzz"
class BindMap
{
#line 2 "./src/util/bind-map.lzz"
public:
#line 6 "./src/util/bind-map.lzz"
  class Pair
  {
#line 7 "./src/util/bind-map.lzz"
    friend class BindMap;
#line 8 "./src/util/bind-map.lzz"
  public:
#line 10 "./src/util/bind-map.lzz"
    int GetIndex ();
#line 14 "./src/util/bind-map.lzz"
    v8::Local <v8::String> GetName (v8::Isolate * isolate);
#line 18 "./src/util/bind-map.lzz"
  private:
#line 19 "./src/util/bind-map.lzz"
    explicit Pair (v8::Isolate * isolate, char const * _name, int _index);
#line 22 "./src/util/bind-map.lzz"
    explicit Pair (v8::Isolate * isolate, Pair * pair);
#line 25 "./src/util/bind-map.lzz"
    CopyablePersistent <v8::String> const name;
#line 26 "./src/util/bind-map.lzz"
    int const index;
  };
#line 29 "./src/util/bind-map.lzz"
  explicit BindMap (char _);
#line 36 "./src/util/bind-map.lzz"
  ~ BindMap ();
#line 41 "./src/util/bind-map.lzz"
  Pair * GetPairs ();
#line 42 "./src/util/bind-map.lzz"
  int GetSize ();
#line 45 "./src/util/bind-map.lzz"
  void Add (v8::Isolate * isolate, char const * name, int index);
#line 51 "./src/util/bind-map.lzz"
private:
#line 52 "./src/util/bind-map.lzz"
  void Grow (v8::Isolate * isolate);
#line 64 "./src/util/bind-map.lzz"
  Pair * pairs;
#line 65 "./src/util/bind-map.lzz"
  int capacity;
#line 66 "./src/util/bind-map.lzz"
  int length;
};
#line 1 "./src/util/integer.lzz"
class Integer : public node::ObjectWrap
{
#line 2 "./src/util/integer.lzz"
public:
#line 4 "./src/util/integer.lzz"
  static bool HasInstance (v8::Isolate * isolate, v8::Local <v8::Value> value);
#line 10 "./src/util/integer.lzz"
  static sqlite3_int64 GetValue (v8::Local <v8::Object> integer);
#line 14 "./src/util/integer.lzz"
  static v8::Local <v8::Value> New (v8::Isolate * isolate, sqlite3_int64 value, bool safe_ints);
#line 22 "./src/util/integer.lzz"
private:
#line 23 "./src/util/integer.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 23 "./src/util/integer.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 33 "./src/util/integer.lzz"
  explicit Integer (char _);
#line 35 "./src/util/integer.lzz"
  struct ConstructorController
  {
#line 36 "./src/util/integer.lzz"
    bool privileges;
#line 37 "./src/util/integer.lzz"
    int64_t value;
  };
#line 40 "./src/util/integer.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 41 "./src/util/integer.lzz"
  static v8::Persistent <v8::Function> isInstance;
#line 42 "./src/util/integer.lzz"
  static Integer::ConstructorController * controller;
#line 44 "./src/util/integer.lzz"
  int64_t value;
};
#line 1 "./src/objects/database.lzz"
class Statement;
#line 2 "./src/objects/database.lzz"
class Backup;
#line 3 "./src/objects/database.lzz"
class Database : public node::ObjectWrap
{
#line 4 "./src/objects/database.lzz"
public:
#line 7 "./src/objects/database.lzz"
  void ThrowDatabaseError ();
#line 11 "./src/objects/database.lzz"
  static void ThrowSqliteError (sqlite3 * db_handle);
#line 15 "./src/objects/database.lzz"
  static void ThrowSqliteError (char const * message, int code);
#line 26 "./src/objects/database.lzz"
  void AddStatement (Statement * stmt);
#line 27 "./src/objects/database.lzz"
  void RemoveStatement (Statement * stmt);
#line 30 "./src/objects/database.lzz"
  void AddBackup (Backup * backup);
#line 31 "./src/objects/database.lzz"
  void RemoveBackup (Backup * backup);
#line 35 "./src/objects/database.lzz"
  struct State
  {
#line 36 "./src/objects/database.lzz"
    bool const open;
#line 37 "./src/objects/database.lzz"
    bool busy;
#line 38 "./src/objects/database.lzz"
    bool const pragma_mode;
#line 39 "./src/objects/database.lzz"
    bool const safe_ints;
#line 40 "./src/objects/database.lzz"
    bool was_js_error;
  };
#line 43 "./src/objects/database.lzz"
  State * GetState ();
#line 46 "./src/objects/database.lzz"
  sqlite3 * GetHandle ();
#line 50 "./src/objects/database.lzz"
  ~ Database ();
#line 55 "./src/objects/database.lzz"
private:
#line 57 "./src/objects/database.lzz"
  class CompareDatabase
  {
#line 57 "./src/objects/database.lzz"
  public:
#line 58 "./src/objects/database.lzz"
    bool operator () (Database const * const a, Database const * const b) const;
  };
#line 63 "./src/objects/database.lzz"
  class CompareStatement
  {
#line 63 "./src/objects/database.lzz"
  public:
#line 64 "./src/objects/database.lzz"
    bool operator () (Statement const * const a, Statement const * const b) const;
  };
#line 69 "./src/objects/database.lzz"
  class CompareBackup
  {
#line 69 "./src/objects/database.lzz"
  public:
#line 70 "./src/objects/database.lzz"
    bool operator () (Backup const * const a, Backup const * const b) const;
  };
#line 75 "./src/objects/database.lzz"
  explicit Database (sqlite3 * _db_handle);
#line 88 "./src/objects/database.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 88 "./src/objects/database.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 112 "./src/objects/database.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 155 "./src/objects/database.lzz"
  static void JS_prepare (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 161 "./src/objects/database.lzz"
  static void JS_exec (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 174 "./src/objects/database.lzz"
  static void JS_pragma (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 178 "./src/objects/database.lzz"
  static void JS_checkpoint (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 220 "./src/objects/database.lzz"
  static void JS_backup (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 227 "./src/objects/database.lzz"
  static void JS_function (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 248 "./src/objects/database.lzz"
  static void JS_aggregate (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 274 "./src/objects/database.lzz"
  static void JS_loadExtension (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 287 "./src/objects/database.lzz"
  static void JS_close (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 297 "./src/objects/database.lzz"
  static void JS_defaultSafeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 305 "./src/objects/database.lzz"
  static void JS_open (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 309 "./src/objects/database.lzz"
  static void JS_inTransaction (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 314 "./src/objects/database.lzz"
  void CloseHandles ();
#line 326 "./src/objects/database.lzz"
  static void AtExit (void * _);
#line 331 "./src/objects/database.lzz"
  static std::set <Database*, Database::CompareDatabase> dbs;
#line 332 "./src/objects/database.lzz"
  static v8::Persistent <v8::Function> SqliteError;
#line 333 "./src/objects/database.lzz"
  static int const MAX_BUFFER_SIZE = node::Buffer::kMaxLength > INT_MAX ? INT_MAX : static_cast<int>(node::Buffer::kMaxLength);
#line 334 "./src/objects/database.lzz"
  static int const MAX_STRING_SIZE = v8::String::kMaxLength > INT_MAX ? INT_MAX : static_cast<int>(v8::String::kMaxLength);
#line 336 "./src/objects/database.lzz"
  sqlite3 * const db_handle;
#line 337 "./src/objects/database.lzz"
  bool open;
#line 338 "./src/objects/database.lzz"
  bool busy;
#line 339 "./src/objects/database.lzz"
  bool pragma_mode;
#line 340 "./src/objects/database.lzz"
  bool safe_ints;
#line 341 "./src/objects/database.lzz"
  bool was_js_error;
#line 342 "./src/objects/database.lzz"
  std::set <Statement*, Database::CompareStatement> stmts;
#line 343 "./src/objects/database.lzz"
  std::set <Backup*, Database::CompareBackup> backups;
};
#line 1 "./src/objects/statement.lzz"
class Statement : public node::ObjectWrap
{
#line 2 "./src/objects/statement.lzz"
  friend class StatementIterator;
#line 3 "./src/objects/statement.lzz"
public:
#line 6 "./src/objects/statement.lzz"
  static v8::MaybeLocal <v8::Object> New (v8::Isolate * isolate, v8::Local <v8::Object> database, v8::Local <v8::String> source);
#line 16 "./src/objects/statement.lzz"
  static bool Compare (Statement const * const a, Statement const * const b);
#line 21 "./src/objects/statement.lzz"
  BindMap * GetBindMap (v8::Isolate * isolate);
#line 34 "./src/objects/statement.lzz"
  void CloseHandles ();
#line 41 "./src/objects/statement.lzz"
  ~ Statement ();
#line 47 "./src/objects/statement.lzz"
private:
#line 50 "./src/objects/statement.lzz"
  class Extras
  {
#line 50 "./src/objects/statement.lzz"
    friend class Statement;
#line 51 "./src/objects/statement.lzz"
    explicit Extras (sqlite3_uint64 _id);
#line 52 "./src/objects/statement.lzz"
    BindMap bind_map;
#line 53 "./src/objects/statement.lzz"
    sqlite3_uint64 const id;
  };
#line 56 "./src/objects/statement.lzz"
  explicit Statement (Database * _db, sqlite3_stmt * _handle, bool _returns_data);
#line 75 "./src/objects/statement.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 75 "./src/objects/statement.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 96 "./src/objects/statement.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 137 "./src/objects/statement.lzz"
  static void JS_run (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 155 "./src/objects/statement.lzz"
  static void JS_get (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 175 "./src/objects/statement.lzz"
  static void JS_all (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 203 "./src/objects/statement.lzz"
  static void JS_iterate (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 208 "./src/objects/statement.lzz"
  static void JS_bind (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 218 "./src/objects/statement.lzz"
  static void JS_pluck (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 228 "./src/objects/statement.lzz"
  static void JS_expand (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 238 "./src/objects/statement.lzz"
  static void JS_raw (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 248 "./src/objects/statement.lzz"
  static void JS_safeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 256 "./src/objects/statement.lzz"
  static void JS_columns (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 297 "./src/objects/statement.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 298 "./src/objects/statement.lzz"
  static sqlite3_uint64 next_id;
#line 299 "./src/objects/statement.lzz"
  static bool constructing_privileges;
#line 301 "./src/objects/statement.lzz"
  Database * const db;
#line 302 "./src/objects/statement.lzz"
  sqlite3_stmt * const handle;
#line 303 "./src/objects/statement.lzz"
  Extras * const extras;
#line 304 "./src/objects/statement.lzz"
  bool alive;
#line 305 "./src/objects/statement.lzz"
  bool bound;
#line 306 "./src/objects/statement.lzz"
  bool has_bind_map;
#line 307 "./src/objects/statement.lzz"
  bool safe_ints;
#line 308 "./src/objects/statement.lzz"
  bool pluck;
#line 309 "./src/objects/statement.lzz"
  bool expand;
#line 310 "./src/objects/statement.lzz"
  bool raw;
#line 311 "./src/objects/statement.lzz"
  bool const returns_data;
};
#line 1 "./src/objects/statement-iterator.lzz"
class StatementIterator : public node::ObjectWrap
{
#line 2 "./src/objects/statement-iterator.lzz"
public:
#line 5 "./src/objects/statement-iterator.lzz"
  static v8::MaybeLocal <v8::Object> New (v8::Isolate * isolate, v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 16 "./src/objects/statement-iterator.lzz"
  ~ StatementIterator ();
#line 18 "./src/objects/statement-iterator.lzz"
private:
#line 20 "./src/objects/statement-iterator.lzz"
  explicit StatementIterator (Statement * _stmt, bool _bound);
#line 35 "./src/objects/statement-iterator.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 35 "./src/objects/statement-iterator.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 48 "./src/objects/statement-iterator.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 65 "./src/objects/statement-iterator.lzz"
  static void JS_next (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 71 "./src/objects/statement-iterator.lzz"
  static void JS_return (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 77 "./src/objects/statement-iterator.lzz"
  static void JS_symbolIterator (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 81 "./src/objects/statement-iterator.lzz"
  void Next (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 98 "./src/objects/statement-iterator.lzz"
  void Return (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 104 "./src/objects/statement-iterator.lzz"
  void Throw ();
#line 110 "./src/objects/statement-iterator.lzz"
  void Cleanup ();
#line 116 "./src/objects/statement-iterator.lzz"
  static v8::Local <v8::Object> NewRecord (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Value> value, bool done = false);
#line 123 "./src/objects/statement-iterator.lzz"
  static v8::Local <v8::Object> DoneRecord (v8::Isolate * isolate);
#line 127 "./src/objects/statement-iterator.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 128 "./src/objects/statement-iterator.lzz"
  static v8::FunctionCallbackInfo <v8 :: Value> const * caller_info;
#line 130 "./src/objects/statement-iterator.lzz"
  Statement * const stmt;
#line 131 "./src/objects/statement-iterator.lzz"
  sqlite3_stmt * const handle;
#line 132 "./src/objects/statement-iterator.lzz"
  bool const safe_ints;
#line 133 "./src/objects/statement-iterator.lzz"
  bool const pluck;
#line 134 "./src/objects/statement-iterator.lzz"
  bool const expand;
#line 135 "./src/objects/statement-iterator.lzz"
  bool const raw;
#line 136 "./src/objects/statement-iterator.lzz"
  bool const bound;
#line 137 "./src/objects/statement-iterator.lzz"
  bool alive;
};
#line 1 "./src/objects/backup.lzz"
class Backup : public node::ObjectWrap
{
#line 2 "./src/objects/backup.lzz"
public:
#line 5 "./src/objects/backup.lzz"
  static v8::MaybeLocal <v8::Object> New (v8::Isolate * isolate, v8::Local <v8::Object> database, v8::Local <v8::String> sourceDatabase, v8::Local <v8::String> destFile);
#line 15 "./src/objects/backup.lzz"
  static bool Compare (Backup const * const a, Backup const * const b);
#line 20 "./src/objects/backup.lzz"
  void CloseHandles ();
#line 29 "./src/objects/backup.lzz"
  ~ Backup ();
#line 34 "./src/objects/backup.lzz"
private:
#line 36 "./src/objects/backup.lzz"
  explicit Backup (Database * _db, sqlite3 * _dest_handle, sqlite3_backup * _backup_handle);
#line 49 "./src/objects/backup.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 49 "./src/objects/backup.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 63 "./src/objects/backup.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 105 "./src/objects/backup.lzz"
  static void JS_transfer (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 144 "./src/objects/backup.lzz"
  static void JS_abort (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 152 "./src/objects/backup.lzz"
  static void JS_state (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 161 "./src/objects/backup.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 162 "./src/objects/backup.lzz"
  static sqlite3_uint64 next_id;
#line 163 "./src/objects/backup.lzz"
  static bool constructing_privileges;
#line 165 "./src/objects/backup.lzz"
  Database * const db;
#line 166 "./src/objects/backup.lzz"
  sqlite3 * const dest_handle;
#line 167 "./src/objects/backup.lzz"
  sqlite3_backup * const backup_handle;
#line 168 "./src/objects/backup.lzz"
  sqlite3_uint64 const id;
#line 169 "./src/objects/backup.lzz"
  bool alive;
#line 170 "./src/objects/backup.lzz"
  bool success;
};
#line 1 "./src/util/custom-function.lzz"
class CustomFunction
{
#line 2 "./src/util/custom-function.lzz"
public:
#line 4 "./src/util/custom-function.lzz"
  explicit CustomFunction (v8::Isolate * _isolate, Database * _db, v8::Local <v8::Function> _fn, char const * _name, bool _safe_ints);
#line 6 "./src/util/custom-function.lzz"
  virtual ~ CustomFunction ();
#line 8 "./src/util/custom-function.lzz"
  static void xDestroy (void * self);
#line 12 "./src/util/custom-function.lzz"
  static void xFunc (sqlite3_context * invocation, int argc, sqlite3_value * * argv);
#line 29 "./src/util/custom-function.lzz"
  void ThrowResultValueError (sqlite3_context * invocation);
#line 34 "./src/util/custom-function.lzz"
protected:
#line 35 "./src/util/custom-function.lzz"
  virtual void PropagateJSError (sqlite3_context * invocation);
#line 41 "./src/util/custom-function.lzz"
private:
#line 42 "./src/util/custom-function.lzz"
  char const * const name;
#line 43 "./src/util/custom-function.lzz"
  Database * const db;
#line 44 "./src/util/custom-function.lzz"
protected:
#line 45 "./src/util/custom-function.lzz"
  v8::Isolate * const isolate;
#line 46 "./src/util/custom-function.lzz"
  CopyablePersistent <v8::Function> const fn;
#line 47 "./src/util/custom-function.lzz"
  bool const safe_ints;
};
#line 1 "./src/util/custom-aggregate.lzz"
class CustomAggregate : public CustomFunction
{
#line 2 "./src/util/custom-aggregate.lzz"
public:
#line 4 "./src/util/custom-aggregate.lzz"
  explicit CustomAggregate (v8::Isolate * _isolate, Database * _db, v8::Local <v8::Value> _start, v8::Local <v8::Function> _step, v8::Local <v8::Value> _inverse, v8::Local <v8::Value> _result, char const * _name, bool _safe_ints);
#line 7 "./src/util/custom-aggregate.lzz"
  static void xStep (sqlite3_context * invocation, int argc, sqlite3_value * * argv);
#line 11 "./src/util/custom-aggregate.lzz"
  static void xInverse (sqlite3_context * invocation, int argc, sqlite3_value * * argv);
#line 15 "./src/util/custom-aggregate.lzz"
  static void xValue (sqlite3_context * invocation);
#line 19 "./src/util/custom-aggregate.lzz"
  static void xFinal (sqlite3_context * invocation);
#line 23 "./src/util/custom-aggregate.lzz"
private:
#line 24 "./src/util/custom-aggregate.lzz"
  static void xStepBase (sqlite3_context * invocation, int argc, sqlite3_value * * argv, CopyablePersistent <v8::Function> const CustomAggregate::* ptrtm);
#line 43 "./src/util/custom-aggregate.lzz"
  static void xValueBase (sqlite3_context * invocation, bool is_final);
#line 67 "./src/util/custom-aggregate.lzz"
  struct Accumulator
  {
#line 67 "./src/util/custom-aggregate.lzz"
  public:
#line 68 "./src/util/custom-aggregate.lzz"
    CopyablePersistent <v8::Value> value;
#line 69 "./src/util/custom-aggregate.lzz"
    bool initialized;
#line 70 "./src/util/custom-aggregate.lzz"
    bool is_window;
  };
#line 73 "./src/util/custom-aggregate.lzz"
  Accumulator * GetAccumulator (sqlite3_context * invocation);
#line 90 "./src/util/custom-aggregate.lzz"
  static void DestroyAccumulator (sqlite3_context * invocation);
#line 96 "./src/util/custom-aggregate.lzz"
  void PropagateJSError (sqlite3_context * invocation);
#line 101 "./src/util/custom-aggregate.lzz"
  bool const invoke_result;
#line 102 "./src/util/custom-aggregate.lzz"
  bool const invoke_start;
#line 103 "./src/util/custom-aggregate.lzz"
  CopyablePersistent <v8::Function> const inverse;
#line 104 "./src/util/custom-aggregate.lzz"
  CopyablePersistent <v8::Function> const result;
#line 105 "./src/util/custom-aggregate.lzz"
  CopyablePersistent <v8::Value> const start;
};
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 56 "./src/util/data.lzz"
  v8::Local <v8::Value> GetValueJS (v8::Isolate * isolate, sqlite3_stmt * handle, int column, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 60 "./src/util/data.lzz"
  v8::Local <v8::Value> GetValueJS (v8::Isolate * isolate, sqlite3_value * value, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 64 "./src/util/data.lzz"
  v8::Local <v8::Value> GetRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 75 "./src/util/data.lzz"
  v8::Local <v8::Value> GetExpandedRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 94 "./src/util/data.lzz"
  v8::Local <v8::Value> GetRawRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 103 "./src/util/data.lzz"
  void GetArgumentsJS (v8::Isolate * isolate, v8::Local <v8::Value> * out, sqlite3_value * * values, int argument_count, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 110 "./src/util/data.lzz"
  int BindValueFromJS (v8::Isolate * isolate, sqlite3_stmt * handle, int index, v8::Local <v8::Value> value);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 115 "./src/util/data.lzz"
  void ResultValueFromJS (v8::Isolate * isolate, sqlite3_context * invocation, v8::Local <v8::Value> value, CustomFunction * function);
}
#line 1 "./src/util/binder.lzz"
class Binder
{
#line 2 "./src/util/binder.lzz"
public:
#line 4 "./src/util/binder.lzz"
  explicit Binder (sqlite3_stmt * _handle);
#line 11 "./src/util/binder.lzz"
  bool Bind (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Statement * stmt);
#line 28 "./src/util/binder.lzz"
private:
#line 29 "./src/util/binder.lzz"
  struct Result
  {
#line 30 "./src/util/binder.lzz"
    int count;
#line 31 "./src/util/binder.lzz"
    bool bound_object;
  };
#line 34 "./src/util/binder.lzz"
  static bool IsPlainObject (v8::Isolate * isolate, v8::Local <v8::Object> obj);
#line 43 "./src/util/binder.lzz"
  void Fail (void (* Throw) (char const *), char const * message);
#line 51 "./src/util/binder.lzz"
  int NextAnonIndex ();
#line 57 "./src/util/binder.lzz"
  void BindValue (v8::Isolate * isolate, v8::Local <v8::Value> value, int index);
#line 78 "./src/util/binder.lzz"
  int BindArray (v8::Isolate * isolate, v8::Local <v8::Array> arr);
#line 104 "./src/util/binder.lzz"
  int BindObject (v8::Isolate * isolate, v8::Local <v8::Object> obj, Statement * stmt);
#line 148 "./src/util/binder.lzz"
  Result BindArgs (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Statement * stmt);
#line 185 "./src/util/binder.lzz"
  sqlite3_stmt * handle;
#line 186 "./src/util/binder.lzz"
  int param_count;
#line 187 "./src/util/binder.lzz"
  int anon_index;
#line 188 "./src/util/binder.lzz"
  bool success;
};
#line 31 "./src/better_sqlite3.lzz"
void RegisterModule (v8::Local <v8::Object> exports, v8::Local <v8::Object> module);
#line 18 "./src/util/macros.lzz"
LZZ_INLINE v8::Local <v8::String> StringFromUtf8 (v8::Isolate * isolate, char const * data, int length)
#line 18 "./src/util/macros.lzz"
                                                                                                {
        return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kNormal, length).ToLocalChecked();
}
#line 21 "./src/util/macros.lzz"
LZZ_INLINE v8::Local <v8::String> InternalizedFromUtf8 (v8::Isolate * isolate, char const * data, int length)
#line 21 "./src/util/macros.lzz"
                                                                                                      {
        return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kInternalized, length).ToLocalChecked();
}
#line 25 "./src/util/macros.lzz"
LZZ_INLINE v8::Local <v8::Value> InternalizedFromUtf8OrNull (v8::Isolate * isolate, char const * data, int length)
#line 25 "./src/util/macros.lzz"
                                                                                                           {
        if (data == NULL) return v8::Null(isolate);
        return InternalizedFromUtf8(isolate, data, length);
}
#line 30 "./src/util/macros.lzz"
LZZ_INLINE void SetFrozen (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Object> obj, ConstantString & key, v8::Local <v8::Value> value)
#line 30 "./src/util/macros.lzz"
                                                                                                                                                    {
        static const v8::PropertyAttribute FROZEN_PROPERTY = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
        obj->DefineOwnProperty(ctx, CS::Get(isolate, key), value, FROZEN_PROPERTY).FromJust();
}
#line 104 "./src/util/macros.lzz"
template <typename T>
#line 104 "./src/util/macros.lzz"
LZZ_INLINE T * ALLOC_ARRAY (size_t count)
#line 104 "./src/util/macros.lzz"
                                                      {
        return static_cast<T*>(::operator new[](count * sizeof(T)));
}
#line 109 "./src/util/macros.lzz"
template <typename T>
#line 109 "./src/util/macros.lzz"
LZZ_INLINE void FREE_ARRAY (T * array_pointer)
#line 109 "./src/util/macros.lzz"
                                                           {
        ::operator delete[](array_pointer);
}
#line 121 "./src/util/macros.lzz"
LZZ_INLINE void NODE_SET_PROTOTYPE_GETTER (v8::Local <v8::FunctionTemplate> recv, char const * name, v8::AccessorGetterCallback getter)
#line 121 "./src/util/macros.lzz"
                                                                                                                                 {
        v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ;
        v8 :: HandleScope scope ( isolate ) ;
        recv->InstanceTemplate()->SetAccessor(
                StringFromUtf8(isolate, name, -1),
                getter,
                0,
                v8::Local<v8::Value>(),
                v8::AccessControl::ALL_CAN_READ,
                v8::PropertyAttribute::None,
                v8::AccessorSignature::New(isolate, recv)
        );
}
#line 135 "./src/util/macros.lzz"
LZZ_INLINE void NODE_SET_PROTOTYPE_SYMBOL_METHOD (v8::Local <v8::FunctionTemplate> recv, v8::Local <v8::Symbol> symbol, v8::FunctionCallback callback)
#line 135 "./src/util/macros.lzz"
                                                                                                                                                {
        v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ;
        v8 :: HandleScope scope ( isolate ) ;
        recv->PrototypeTemplate()->Set(symbol, v8::FunctionTemplate::New(
                isolate,
                callback,
                v8::Local<v8::Value>(),
                v8::Signature::New(isolate, recv)
        ));
}
#line 3 "./src/util/constants.lzz"
LZZ_INLINE v8::Local <v8::String> CS::Get (v8::Isolate * isolate, ConstantString & constant)
#line 3 "./src/util/constants.lzz"
                                                                                                {
                return v8::Local<v8::String>::New(isolate, constant);
}
#line 10 "./src/util/bind-map.lzz"
LZZ_INLINE int BindMap::Pair::GetIndex ()
#line 10 "./src/util/bind-map.lzz"
                                              {
                                return index;
}
#line 14 "./src/util/bind-map.lzz"
LZZ_INLINE v8::Local <v8::String> BindMap::Pair::GetName (v8::Isolate * isolate)
#line 14 "./src/util/bind-map.lzz"
                                                                                   {
                                return v8::Local<v8::String>::New(isolate, name);
}
#line 41 "./src/util/bind-map.lzz"
LZZ_INLINE BindMap::Pair * BindMap::GetPairs ()
#line 41 "./src/util/bind-map.lzz"
                                { return pairs;
}
#line 42 "./src/util/bind-map.lzz"
LZZ_INLINE int BindMap::GetSize ()
#line 42 "./src/util/bind-map.lzz"
                             { return length;
}
#line 26 "./src/objects/database.lzz"
LZZ_INLINE void Database::AddStatement (Statement * stmt)
#line 26 "./src/objects/database.lzz"
                                                  { stmts.insert(stmts.end(), stmt);
}
#line 27 "./src/objects/database.lzz"
LZZ_INLINE void Database::RemoveStatement (Statement * stmt)
#line 27 "./src/objects/database.lzz"
                                                     { stmts.erase(stmt);
}
#line 30 "./src/objects/database.lzz"
LZZ_INLINE void Database::AddBackup (Backup * backup)
#line 30 "./src/objects/database.lzz"
                                              { backups.insert(backups.end(), backup);
}
#line 31 "./src/objects/database.lzz"
LZZ_INLINE void Database::RemoveBackup (Backup * backup)
#line 31 "./src/objects/database.lzz"
                                                 { backups.erase(backup);
}
#line 43 "./src/objects/database.lzz"
LZZ_INLINE Database::State * Database::GetState ()
#line 43 "./src/objects/database.lzz"
                                 {
                return reinterpret_cast<State*>(&open);
}
#line 46 "./src/objects/database.lzz"
LZZ_INLINE sqlite3 * Database::GetHandle ()
#line 46 "./src/objects/database.lzz"
                                    {
                return db_handle;
}
#line 16 "./src/objects/statement.lzz"
LZZ_INLINE bool Statement::Compare (Statement const * const a, Statement const * const b)
#line 16 "./src/objects/statement.lzz"
                                                                                         {
                return a->extras->id < b->extras->id;
}
#line 15 "./src/objects/backup.lzz"
LZZ_INLINE bool Backup::Compare (Backup const * const a, Backup const * const b)
#line 15 "./src/objects/backup.lzz"
                                                                                   {
                return a->id < b->id;
}
#line 24 "./src/util/custom-aggregate.lzz"
LZZ_INLINE void CustomAggregate::xStepBase (sqlite3_context * invocation, int argc, sqlite3_value * * argv, CopyablePersistent <v8::Function> const CustomAggregate::* ptrtm)
#line 24 "./src/util/custom-aggregate.lzz"
                                                                                                                                                                  {
                CustomAggregate * self = static_cast < CustomAggregate * > ( sqlite3_user_data ( invocation ) ) ; v8 :: Isolate * isolate = self -> isolate ; v8 :: HandleScope scope ( isolate ) ; Accumulator * acc = self -> GetAccumulator ( invocation ) ; if ( acc -> value . IsEmpty ( ) ) return ;

                v8::Local<v8::Value> args_fast[5];
                v8::Local<v8::Value>* args = argc <= 4 ? args_fast : ALLOC_ARRAY<v8::Local<v8::Value>>(argc + 1);
                args[0] = v8::Local<v8::Value>::New(isolate, acc->value);
                if (argc != 0) Data::GetArgumentsJS(isolate, args + 1, argv, argc, self->safe_ints);

                v8::MaybeLocal<v8::Value> maybe_return_value = v8::Local<v8::Function>::New(isolate, self->*ptrtm)->Call( isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), argc + 1, args);
                if (args != args_fast) delete[] args;

                if (maybe_return_value.IsEmpty()) {
                        self->PropagateJSError(invocation);
                } else {
                        v8::Local<v8::Value> return_value = maybe_return_value.ToLocalChecked();
                        if (!return_value->IsUndefined()) acc->value.Reset(isolate, return_value);
                }
}
#line 43 "./src/util/custom-aggregate.lzz"
LZZ_INLINE void CustomAggregate::xValueBase (sqlite3_context * invocation, bool is_final)
#line 43 "./src/util/custom-aggregate.lzz"
                                                                                  {
                CustomAggregate * self = static_cast < CustomAggregate * > ( sqlite3_user_data ( invocation ) ) ; v8 :: Isolate * isolate = self -> isolate ; v8 :: HandleScope scope ( isolate ) ; Accumulator * acc = self -> GetAccumulator ( invocation ) ; if ( acc -> value . IsEmpty ( ) ) return ;

                if (!is_final) {
                        acc->is_window = true;
                } else if (acc->is_window) {
                        DestroyAccumulator(invocation);
                        return;
                }

                v8::Local<v8::Value> result = v8::Local<v8::Value>::New(isolate, acc->value);
                if (self->invoke_result) {
                        v8::MaybeLocal<v8::Value> maybe_result = v8::Local<v8::Function>::New(isolate, self->result)->Call( isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), 1, &result);
                        if (maybe_result.IsEmpty()) {
                                self->PropagateJSError(invocation);
                                return;
                        }
                        result = maybe_result.ToLocalChecked();
                }

                Data::ResultValueFromJS(isolate, invocation, result, self);
                if (is_final) DestroyAccumulator(invocation);
}
#undef LZZ_INLINE
#endif
