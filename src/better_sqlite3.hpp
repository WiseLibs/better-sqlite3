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
#line 130 "./src/util/macros.lzz"
template <class T> using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;
#line 146 "./src/util/constants.lzz"
typedef v8::Persistent<v8::String> ConstantString;
#define LZZ_INLINE inline
#line 18 "./src/util/macros.lzz"
v8::Local <v8::String> StringFromUtf8 (v8::Isolate * isolate, char const * data, int length);
#line 21 "./src/util/macros.lzz"
v8::Local <v8::String> InternalizedFromUtf8 (v8::Isolate * isolate, char const * data, int length);
#line 25 "./src/util/macros.lzz"
void SetFrozen (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Object> obj, ConstantString & key, v8::Local <v8::Value> value);
#line 30 "./src/util/macros.lzz"
void ThrowError (char const * message);
#line 31 "./src/util/macros.lzz"
void ThrowTypeError (char const * message);
#line 32 "./src/util/macros.lzz"
void ThrowRangeError (char const * message);
#line 74 "./src/util/macros.lzz"
std::string CONCAT (char const * a, char const * b, char const * c);
#line 82 "./src/util/macros.lzz"
template <typename T>
#line 82 "./src/util/macros.lzz"
T * ALLOC_ARRAY (size_t count);
#line 87 "./src/util/macros.lzz"
template <typename T>
#line 87 "./src/util/macros.lzz"
void FREE_ARRAY (T * array_pointer);
#line 91 "./src/util/macros.lzz"
v8::Local <v8::Value> Require (v8::Local <v8::Object> module, char const * path, bool local = false);
#line 104 "./src/util/macros.lzz"
void NODE_SET_PROTOTYPE_GETTER (v8::Local <v8::FunctionTemplate> recv, char const * name, v8::AccessorGetterCallback getter);
#line 118 "./src/util/macros.lzz"
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
  static ConstantString source;
#line 14 "./src/util/constants.lzz"
  static ConstantString memory;
#line 15 "./src/util/constants.lzz"
  static ConstantString readonly;
#line 16 "./src/util/constants.lzz"
  static ConstantString name;
#line 17 "./src/util/constants.lzz"
  static ConstantString next;
#line 18 "./src/util/constants.lzz"
  static ConstantString length;
#line 19 "./src/util/constants.lzz"
  static ConstantString done;
#line 20 "./src/util/constants.lzz"
  static ConstantString value;
#line 21 "./src/util/constants.lzz"
  static ConstantString changes;
#line 22 "./src/util/constants.lzz"
  static ConstantString lastInsertRowid;
#line 23 "./src/util/constants.lzz"
  static ConstantString code;
#line 24 "./src/util/constants.lzz"
  static ConstantString statement;
#line 26 "./src/util/constants.lzz"
private:
#line 27 "./src/util/constants.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 27 "./src/util/constants.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 131 "./src/util/constants.lzz"
  static v8::Local <v8::String> InternalizedFromLatin1 (v8::Isolate * isolate, char const * str);
#line 134 "./src/util/constants.lzz"
  static void AddString (v8::Isolate * isolate, ConstantString & constant, char const * str);
#line 137 "./src/util/constants.lzz"
  static void AddCode (v8::Isolate * isolate, int code, char const * str);
#line 140 "./src/util/constants.lzz"
  explicit CS (char _);
#line 142 "./src/util/constants.lzz"
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
class Database : public node::ObjectWrap
{
#line 3 "./src/objects/database.lzz"
public:
#line 6 "./src/objects/database.lzz"
  void ThrowDatabaseError ();
#line 12 "./src/objects/database.lzz"
  void AddStatement (Statement * stmt);
#line 13 "./src/objects/database.lzz"
  void RemoveStatement (Statement * stmt);
#line 17 "./src/objects/database.lzz"
  struct State
  {
#line 18 "./src/objects/database.lzz"
    bool const open;
#line 19 "./src/objects/database.lzz"
    bool busy;
#line 20 "./src/objects/database.lzz"
    bool const pragma_mode;
#line 21 "./src/objects/database.lzz"
    bool const safe_ints;
#line 22 "./src/objects/database.lzz"
    bool was_js_error;
  };
#line 25 "./src/objects/database.lzz"
  State * GetState ();
#line 28 "./src/objects/database.lzz"
  sqlite3 * GetHandle ();
#line 32 "./src/objects/database.lzz"
  ~ Database ();
#line 37 "./src/objects/database.lzz"
private:
#line 39 "./src/objects/database.lzz"
  class CompareDatabase
  {
#line 39 "./src/objects/database.lzz"
  public:
#line 40 "./src/objects/database.lzz"
    bool operator () (Database const * const a, Database const * const b) const;
  };
#line 45 "./src/objects/database.lzz"
  class CompareStatement
  {
#line 45 "./src/objects/database.lzz"
  public:
#line 46 "./src/objects/database.lzz"
    bool operator () (Statement const * const a, Statement const * const b) const;
  };
#line 51 "./src/objects/database.lzz"
  explicit Database (sqlite3 * _db_handle);
#line 63 "./src/objects/database.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 63 "./src/objects/database.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 86 "./src/objects/database.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 125 "./src/objects/database.lzz"
  static void JS_prepare (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 131 "./src/objects/database.lzz"
  static void JS_exec (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 143 "./src/objects/database.lzz"
  static void JS_pragma (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 147 "./src/objects/database.lzz"
  static void JS_checkpoint (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 189 "./src/objects/database.lzz"
  static void JS_function (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 210 "./src/objects/database.lzz"
  static void JS_aggregate (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 235 "./src/objects/database.lzz"
  static void JS_loadExtension (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 248 "./src/objects/database.lzz"
  static void JS_close (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 258 "./src/objects/database.lzz"
  static void JS_defaultSafeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 266 "./src/objects/database.lzz"
  static void JS_open (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 270 "./src/objects/database.lzz"
  static void JS_inTransaction (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 275 "./src/objects/database.lzz"
  void CloseHandles ();
#line 285 "./src/objects/database.lzz"
  static void ThrowSqliteError (sqlite3 * db_handle);
#line 289 "./src/objects/database.lzz"
  static void ThrowSqliteError (sqlite3 * db_handle, char const * message, int code);
#line 298 "./src/objects/database.lzz"
  static void AtExit (void * _);
#line 303 "./src/objects/database.lzz"
  static std::set <Database*, Database::CompareDatabase> dbs;
#line 304 "./src/objects/database.lzz"
  static v8::Persistent <v8::Function> SqliteError;
#line 305 "./src/objects/database.lzz"
  static int const MAX_BUFFER_SIZE = node::Buffer::kMaxLength > INT_MAX ? INT_MAX : static_cast<int>(node::Buffer::kMaxLength);
#line 306 "./src/objects/database.lzz"
  static int const MAX_STRING_SIZE = v8::String::kMaxLength > INT_MAX ? INT_MAX : static_cast<int>(v8::String::kMaxLength);
#line 308 "./src/objects/database.lzz"
  sqlite3 * const db_handle;
#line 309 "./src/objects/database.lzz"
  bool open;
#line 310 "./src/objects/database.lzz"
  bool busy;
#line 311 "./src/objects/database.lzz"
  bool pragma_mode;
#line 312 "./src/objects/database.lzz"
  bool safe_ints;
#line 313 "./src/objects/database.lzz"
  bool was_js_error;
#line 314 "./src/objects/database.lzz"
  std::set <Statement*, Database::CompareStatement> stmts;
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
#line 74 "./src/objects/statement.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 74 "./src/objects/statement.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 94 "./src/objects/statement.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 134 "./src/objects/statement.lzz"
  static void JS_run (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 152 "./src/objects/statement.lzz"
  static void JS_get (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 171 "./src/objects/statement.lzz"
  static void JS_all (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 197 "./src/objects/statement.lzz"
  static void JS_iterate (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 202 "./src/objects/statement.lzz"
  static void JS_bind (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 212 "./src/objects/statement.lzz"
  static void JS_pluck (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 222 "./src/objects/statement.lzz"
  static void JS_expand (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 232 "./src/objects/statement.lzz"
  static void JS_safeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 240 "./src/objects/statement.lzz"
  static void JS_returnsData (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 244 "./src/objects/statement.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 245 "./src/objects/statement.lzz"
  static sqlite3_uint64 next_id;
#line 246 "./src/objects/statement.lzz"
  static bool constructing_privileges;
#line 248 "./src/objects/statement.lzz"
  Database * const db;
#line 249 "./src/objects/statement.lzz"
  sqlite3_stmt * const handle;
#line 250 "./src/objects/statement.lzz"
  Extras * const extras;
#line 251 "./src/objects/statement.lzz"
  bool alive;
#line 252 "./src/objects/statement.lzz"
  bool bound;
#line 253 "./src/objects/statement.lzz"
  bool has_bind_map;
#line 254 "./src/objects/statement.lzz"
  bool safe_ints;
#line 255 "./src/objects/statement.lzz"
  bool pluck;
#line 256 "./src/objects/statement.lzz"
  bool expand;
#line 257 "./src/objects/statement.lzz"
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
#line 34 "./src/objects/statement-iterator.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 34 "./src/objects/statement-iterator.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 47 "./src/objects/statement-iterator.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 65 "./src/objects/statement-iterator.lzz"
  static void JS_next (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 71 "./src/objects/statement-iterator.lzz"
  static void JS_return (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 77 "./src/objects/statement-iterator.lzz"
  static void JS_symbolIterator (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 81 "./src/objects/statement-iterator.lzz"
  void Next (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 97 "./src/objects/statement-iterator.lzz"
  void Return (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 102 "./src/objects/statement-iterator.lzz"
  void Throw ();
#line 108 "./src/objects/statement-iterator.lzz"
  void Cleanup ();
#line 115 "./src/objects/statement-iterator.lzz"
  static v8::Local <v8::Object> NewRecord (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Value> value, bool done = false);
#line 122 "./src/objects/statement-iterator.lzz"
  static v8::Local <v8::Object> DoneRecord (v8::Isolate * isolate);
#line 126 "./src/objects/statement-iterator.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 127 "./src/objects/statement-iterator.lzz"
  static v8::FunctionCallbackInfo <v8 :: Value> const * caller_info;
#line 129 "./src/objects/statement-iterator.lzz"
  Statement * const stmt;
#line 130 "./src/objects/statement-iterator.lzz"
  sqlite3_stmt * const handle;
#line 131 "./src/objects/statement-iterator.lzz"
  bool const safe_ints;
#line 132 "./src/objects/statement-iterator.lzz"
  bool const pluck;
#line 133 "./src/objects/statement-iterator.lzz"
  bool const expand;
#line 134 "./src/objects/statement-iterator.lzz"
  bool const bound;
#line 135 "./src/objects/statement-iterator.lzz"
  bool alive;
};
#line 1 "./src/util/custom-function.lzz"
class CustomFunction
{
#line 2 "./src/util/custom-function.lzz"
public:
#line 4 "./src/util/custom-function.lzz"
  explicit CustomFunction (v8::Isolate * _isolate, Database * _db, v8::Local <v8::Function> _fn, char const * _name, bool _safe_ints);
#line 6 "./src/util/custom-function.lzz"
  ~ CustomFunction ();
#line 8 "./src/util/custom-function.lzz"
  static void xDestroy (void * instance);
#line 12 "./src/util/custom-function.lzz"
  static void xFunc (sqlite3_context * context, int argc, sqlite3_value * * argv);
#line 36 "./src/util/custom-function.lzz"
  void ThrowResultValueError (sqlite3_context * context);
#line 41 "./src/util/custom-function.lzz"
private:
#line 42 "./src/util/custom-function.lzz"
  void PropagateJSError (sqlite3_context * context);
#line 48 "./src/util/custom-function.lzz"
  static char const * CopyString (char const * source);
#line 55 "./src/util/custom-function.lzz"
  CopyablePersistent <v8::Function> const fn;
#line 56 "./src/util/custom-function.lzz"
  v8::Isolate * const isolate;
#line 57 "./src/util/custom-function.lzz"
  Database * const db;
#line 58 "./src/util/custom-function.lzz"
  char const * const name;
#line 59 "./src/util/custom-function.lzz"
  bool const safe_ints;
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
  void GetArgumentsJS (v8::Isolate * isolate, v8::Local <v8::Value> * out, sqlite3_value * * values, int argument_count, bool safe_ints);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 101 "./src/util/data.lzz"
  int BindValueFromJS (v8::Isolate * isolate, sqlite3_stmt * handle, int index, v8::Local <v8::Value> value);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 106 "./src/util/data.lzz"
  void ResultValueFromJS (v8::Isolate * isolate, sqlite3_context * context, v8::Local <v8::Value> value, CustomFunction * function);
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
#line 30 "./src/better_sqlite3.lzz"
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
LZZ_INLINE void SetFrozen (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Object> obj, ConstantString & key, v8::Local <v8::Value> value)
#line 25 "./src/util/macros.lzz"
                                                                                                                                                    {
        static const v8::PropertyAttribute FROZEN_PROPERTY = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
        obj->DefineOwnProperty(ctx, CS::Get(isolate, key), value, FROZEN_PROPERTY).FromJust();
}
#line 82 "./src/util/macros.lzz"
template <typename T>
#line 82 "./src/util/macros.lzz"
LZZ_INLINE T * ALLOC_ARRAY (size_t count)
#line 82 "./src/util/macros.lzz"
                                                      {
        return static_cast<T*>(::operator new[](count * sizeof(T)));
}
#line 87 "./src/util/macros.lzz"
template <typename T>
#line 87 "./src/util/macros.lzz"
LZZ_INLINE void FREE_ARRAY (T * array_pointer)
#line 87 "./src/util/macros.lzz"
                                                           {
        ::operator delete[](array_pointer);
}
#line 104 "./src/util/macros.lzz"
LZZ_INLINE void NODE_SET_PROTOTYPE_GETTER (v8::Local <v8::FunctionTemplate> recv, char const * name, v8::AccessorGetterCallback getter)
#line 104 "./src/util/macros.lzz"
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
#line 118 "./src/util/macros.lzz"
LZZ_INLINE void NODE_SET_PROTOTYPE_SYMBOL_METHOD (v8::Local <v8::FunctionTemplate> recv, v8::Local <v8::Symbol> symbol, v8::FunctionCallback callback)
#line 118 "./src/util/macros.lzz"
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
#line 12 "./src/objects/database.lzz"
LZZ_INLINE void Database::AddStatement (Statement * stmt)
#line 12 "./src/objects/database.lzz"
                                                  { stmts.insert(stmts.end(), stmt);
}
#line 13 "./src/objects/database.lzz"
LZZ_INLINE void Database::RemoveStatement (Statement * stmt)
#line 13 "./src/objects/database.lzz"
                                                     { stmts.erase(stmt);
}
#line 25 "./src/objects/database.lzz"
LZZ_INLINE Database::State * Database::GetState ()
#line 25 "./src/objects/database.lzz"
                                 {
                return reinterpret_cast<State*>(&open);
}
#line 28 "./src/objects/database.lzz"
LZZ_INLINE sqlite3 * Database::GetHandle ()
#line 28 "./src/objects/database.lzz"
                                    {
                return db_handle;
}
#line 16 "./src/objects/statement.lzz"
LZZ_INLINE bool Statement::Compare (Statement const * const a, Statement const * const b)
#line 16 "./src/objects/statement.lzz"
                                                                                         {
                return a->extras->id < b->extras->id;
}
#undef LZZ_INLINE
#endif
