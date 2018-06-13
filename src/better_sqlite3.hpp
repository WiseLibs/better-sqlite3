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
#line 125 "./src/util/macros.lzz"
template <class T> using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;
#line 146 "./src/util/constants.lzz"
typedef v8::Persistent<v8::String> ConstantString;
#define LZZ_INLINE inline
#line 18 "./src/util/macros.lzz"
v8::Local <v8::String> StringFromUtf8 (v8::Isolate * isolate, char const * data, int length);
#line 21 "./src/util/macros.lzz"
v8::Local <v8::String> StringFromUtf16 (v8::Isolate * isolate, uint16_t const * data, int length);
#line 24 "./src/util/macros.lzz"
v8::Local <v8::String> InternalizedFromUtf8 (v8::Isolate * isolate, char const * data, int length);
#line 28 "./src/util/macros.lzz"
void SetFrozen (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Object> obj, ConstantString & key, v8::Local <v8::Value> value);
#line 33 "./src/util/macros.lzz"
void ThrowError (char const * message);
#line 34 "./src/util/macros.lzz"
void ThrowTypeError (char const * message);
#line 35 "./src/util/macros.lzz"
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
v8::Local <v8::Value> Require (v8::Local <v8::Object> module, char const * path);
#line 99 "./src/util/macros.lzz"
void NODE_SET_PROTOTYPE_GETTER (v8::Local <v8::FunctionTemplate> recv, char const * name, v8::AccessorGetterCallback getter);
#line 113 "./src/util/macros.lzz"
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
  static ConstantString lastInsertROWID;
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
#line 5 "./src/util/database-handles.lzz"
class DatabaseHandles
{
#line 5 "./src/util/database-handles.lzz"
  friend class Database;
#line 7 "./src/util/database-handles.lzz"
  explicit DatabaseHandles (v8::Local <v8::String> filename, bool readonly, bool must_exist);
#line 30 "./src/util/database-handles.lzz"
  ~ DatabaseHandles ();
#line 40 "./src/util/database-handles.lzz"
  sqlite3 * db_handle;
#line 41 "./src/util/database-handles.lzz"
  sqlite3_stmt * begin;
#line 42 "./src/util/database-handles.lzz"
  sqlite3_stmt * commit;
#line 43 "./src/util/database-handles.lzz"
  sqlite3_stmt * rollback;
#line 44 "./src/util/database-handles.lzz"
  bool success;
};
#line 5 "./src/util/transaction-handles.lzz"
class TransactionHandles
{
#line 5 "./src/util/transaction-handles.lzz"
  friend class Transaction;
#line 7 "./src/util/transaction-handles.lzz"
  explicit TransactionHandles (int capacity);
#line 13 "./src/util/transaction-handles.lzz"
  ~ TransactionHandles ();
#line 20 "./src/util/transaction-handles.lzz"
  void Add (sqlite3_stmt * handle);
#line 24 "./src/util/transaction-handles.lzz"
  sqlite3_stmt * * handles;
#line 25 "./src/util/transaction-handles.lzz"
  int handle_count;
#line 26 "./src/util/transaction-handles.lzz"
  bool success;
};
#line 4 "./src/util/sql-string.lzz"
class SQLString
{
#line 5 "./src/util/sql-string.lzz"
public:
#line 7 "./src/util/sql-string.lzz"
  explicit SQLString (uint32_t capacity);
#line 10 "./src/util/sql-string.lzz"
  ~ SQLString ();
#line 15 "./src/util/sql-string.lzz"
  void AddStatement (v8::Local <v8::String> source);
#line 21 "./src/util/sql-string.lzz"
  v8::String::Value const * GetStatement (uint32_t index);
#line 25 "./src/util/sql-string.lzz"
  v8::Local <v8::String> Concat (v8::Isolate * isolate);
#line 42 "./src/util/sql-string.lzz"
private:
#line 43 "./src/util/sql-string.lzz"
  class StatementString
  {
#line 43 "./src/util/sql-string.lzz"
    friend class SQLString;
#line 44 "./src/util/sql-string.lzz"
    explicit StatementString (v8::Local <v8::String> string);
#line 46 "./src/util/sql-string.lzz"
    v8::String::Value const value;
#line 47 "./src/util/sql-string.lzz"
    bool const missing_semicolon;
  };
#line 50 "./src/util/sql-string.lzz"
  StatementString * const strings;
#line 51 "./src/util/sql-string.lzz"
  size_t total_character_count;
#line 52 "./src/util/sql-string.lzz"
  uint32_t count;
};
#line 1 "./src/util/bind-map.lzz"
class BindMap
{
#line 2 "./src/util/bind-map.lzz"
public:
#line 8 "./src/util/bind-map.lzz"
  class Pair
  {
#line 9 "./src/util/bind-map.lzz"
    friend class BindMap;
#line 10 "./src/util/bind-map.lzz"
  public:
#line 12 "./src/util/bind-map.lzz"
    int GetIndex ();
#line 16 "./src/util/bind-map.lzz"
    v8::Local <v8::String> GetName (v8::Isolate * isolate);
#line 20 "./src/util/bind-map.lzz"
  private:
#line 21 "./src/util/bind-map.lzz"
    explicit Pair (v8::Isolate * isolate, char const * _name, int _index);
#line 24 "./src/util/bind-map.lzz"
    explicit Pair (v8::Isolate * isolate, Pair * pair);
#line 27 "./src/util/bind-map.lzz"
    CopyablePersistent <v8::String> const name;
#line 28 "./src/util/bind-map.lzz"
    int const index;
  };
#line 31 "./src/util/bind-map.lzz"
  explicit BindMap (char _);
#line 38 "./src/util/bind-map.lzz"
  ~ BindMap ();
#line 43 "./src/util/bind-map.lzz"
  Pair * GetPairs ();
#line 44 "./src/util/bind-map.lzz"
  int GetSize ();
#line 47 "./src/util/bind-map.lzz"
  void Add (v8::Isolate * isolate, char const * name, int index);
#line 56 "./src/util/bind-map.lzz"
  void Add (v8::Isolate * isolate, char const * name, int parameter_index, int transaction_index);
#line 63 "./src/util/bind-map.lzz"
  static int const PARAMETER_BITS = 10;
#line 64 "./src/util/bind-map.lzz"
  static int const PARAMETER_MASK = (1 << PARAMETER_BITS) - 1;
#line 65 "./src/util/bind-map.lzz"
  static int const MAX_TRANSACTION_LENGTH = (1 << ((sizeof(int) * 8) - PARAMETER_BITS - 1)) - 1;
#line 68 "./src/util/bind-map.lzz"
  static int GetParameterIndex (int index);
#line 71 "./src/util/bind-map.lzz"
  static int GetTransactionIndex (int index);
#line 75 "./src/util/bind-map.lzz"
private:
#line 76 "./src/util/bind-map.lzz"
  void Grow (v8::Isolate * isolate);
#line 88 "./src/util/bind-map.lzz"
  Pair * pairs;
#line 89 "./src/util/bind-map.lzz"
  int capacity;
#line 90 "./src/util/bind-map.lzz"
  int length;
};
#line 1 "./src/util/integer.lzz"
class Integer : public node::ObjectWrap
{
#line 2 "./src/util/integer.lzz"
public:
#line 4 "./src/util/integer.lzz"
  static bool HasInstance (v8::Local <v8::Value> value);
#line 11 "./src/util/integer.lzz"
  static sqlite3_int64 GetValue (v8::Local <v8::Object> integer);
#line 15 "./src/util/integer.lzz"
  static v8::Local <v8::Value> New (v8::Isolate * isolate, sqlite3_int64 value, bool safe_ints);
#line 23 "./src/util/integer.lzz"
private:
#line 24 "./src/util/integer.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 24 "./src/util/integer.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 34 "./src/util/integer.lzz"
  explicit Integer (char _);
#line 36 "./src/util/integer.lzz"
  struct ConstructorController
  {
#line 37 "./src/util/integer.lzz"
    bool privileges;
#line 38 "./src/util/integer.lzz"
    int64_t value;
  };
#line 41 "./src/util/integer.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 42 "./src/util/integer.lzz"
  static v8::Persistent <v8::Function> isInstance;
#line 43 "./src/util/integer.lzz"
  static Integer::ConstructorController * controller;
#line 45 "./src/util/integer.lzz"
  int64_t value;
};
#line 1 "./src/objects/query.lzz"
class Query
{
#line 2 "./src/objects/query.lzz"
public:
#line 4 "./src/objects/query.lzz"
  class Compare
  {
#line 4 "./src/objects/query.lzz"
  public:
#line 5 "./src/objects/query.lzz"
    template <typename T>
#line 6 "./src/objects/query.lzz"
    bool operator () (T const * const a, T const * const b) const;
  };
#line 11 "./src/objects/query.lzz"
protected:
#line 14 "./src/objects/query.lzz"
  class QueryExtras
  {
#line 14 "./src/objects/query.lzz"
    friend class Query;
#line 15 "./src/objects/query.lzz"
    explicit QueryExtras (sqlite3_uint64 _id);
#line 16 "./src/objects/query.lzz"
    BindMap bind_map;
#line 17 "./src/objects/query.lzz"
    sqlite3_uint64 const id;
  };
#line 21 "./src/objects/query.lzz"
  explicit Query (sqlite3_uint64 id);
#line 22 "./src/objects/query.lzz"
  ~ Query ();
#line 24 "./src/objects/query.lzz"
  BindMap * BindMapPointer ();
#line 28 "./src/objects/query.lzz"
  QueryExtras * const extras;
};
#line 1 "./src/objects/database.lzz"
class Statement;
#line 2 "./src/objects/database.lzz"
class Transaction;
#line 3 "./src/objects/database.lzz"
class Database : public node::ObjectWrap
{
#line 4 "./src/objects/database.lzz"
public:
#line 7 "./src/objects/database.lzz"
  void ThrowDatabaseError ();
#line 14 "./src/objects/database.lzz"
  void AddStatement (Statement * stmt);
#line 15 "./src/objects/database.lzz"
  void RemoveStatement (Statement * stmt);
#line 16 "./src/objects/database.lzz"
  void AddTransaction (Transaction * trans);
#line 17 "./src/objects/database.lzz"
  void RemoveTransaction (Transaction * trans);
#line 21 "./src/objects/database.lzz"
  struct State
  {
#line 22 "./src/objects/database.lzz"
    bool const open;
#line 23 "./src/objects/database.lzz"
    bool busy;
#line 24 "./src/objects/database.lzz"
    bool const pragma_mode;
#line 25 "./src/objects/database.lzz"
    bool const safe_ints;
#line 26 "./src/objects/database.lzz"
    bool was_js_error;
  };
#line 31 "./src/objects/database.lzz"
  struct TransactionController
  {
#line 32 "./src/objects/database.lzz"
    sqlite3_stmt * const begin;
#line 33 "./src/objects/database.lzz"
    sqlite3_stmt * const commit;
#line 34 "./src/objects/database.lzz"
    sqlite3_stmt * const rollback;
  };
#line 37 "./src/objects/database.lzz"
  State * GetState ();
#line 40 "./src/objects/database.lzz"
  sqlite3 * GetHandle ();
#line 43 "./src/objects/database.lzz"
  TransactionController GetTransactionController ();
#line 47 "./src/objects/database.lzz"
  ~ Database ();
#line 52 "./src/objects/database.lzz"
private:
#line 54 "./src/objects/database.lzz"
  explicit Database (DatabaseHandles * handles);
#line 66 "./src/objects/database.lzz"
  class DatabaseExtras
  {
#line 66 "./src/objects/database.lzz"
    friend class Database;
#line 67 "./src/objects/database.lzz"
    explicit DatabaseExtras (DatabaseHandles * handles);
#line 71 "./src/objects/database.lzz"
    std::set <Statement*, Query::Compare> stmts;
#line 72 "./src/objects/database.lzz"
    std::set <Transaction*, Query::Compare> transs;
#line 73 "./src/objects/database.lzz"
    sqlite3_stmt * const begin;
#line 74 "./src/objects/database.lzz"
    sqlite3_stmt * const commit;
#line 75 "./src/objects/database.lzz"
    sqlite3_stmt * const rollback;
  };
#line 78 "./src/objects/database.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 78 "./src/objects/database.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 100 "./src/objects/database.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 129 "./src/objects/database.lzz"
  static void JS_prepare (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 135 "./src/objects/database.lzz"
  static void JS_transaction (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 141 "./src/objects/database.lzz"
  static void JS_exec (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 153 "./src/objects/database.lzz"
  static void JS_pragma (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 157 "./src/objects/database.lzz"
  static void JS_checkpoint (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 199 "./src/objects/database.lzz"
  static void JS_register (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 225 "./src/objects/database.lzz"
  static void JS_loadExtension (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 240 "./src/objects/database.lzz"
  static void JS_close (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 249 "./src/objects/database.lzz"
  static void JS_defaultSafeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 257 "./src/objects/database.lzz"
  static void JS_open (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 261 "./src/objects/database.lzz"
  static void JS_inTransaction (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 267 "./src/objects/database.lzz"
  void CloseHandles ();
#line 282 "./src/objects/database.lzz"
  static void ThrowSqliteError (sqlite3 * db_handle);
#line 286 "./src/objects/database.lzz"
  static void ThrowSqliteError (sqlite3 * db_handle, char const * message, int code);
#line 295 "./src/objects/database.lzz"
  static v8::Persistent <v8::Function> SqliteError;
#line 296 "./src/objects/database.lzz"
  static int const MAX_BUFFER_SIZE = node::Buffer::kMaxLength > INT_MAX ? INT_MAX : static_cast<int>(node::Buffer::kMaxLength);
#line 297 "./src/objects/database.lzz"
  static int const MAX_STRING_SIZE = v8::String::kMaxLength > INT_MAX ? INT_MAX : static_cast<int>(v8::String::kMaxLength);
#line 299 "./src/objects/database.lzz"
  sqlite3 * const db_handle;
#line 300 "./src/objects/database.lzz"
  DatabaseExtras * const extras;
#line 301 "./src/objects/database.lzz"
  bool open;
#line 302 "./src/objects/database.lzz"
  bool busy;
#line 303 "./src/objects/database.lzz"
  bool pragma_mode;
#line 304 "./src/objects/database.lzz"
  bool safe_ints;
#line 305 "./src/objects/database.lzz"
  bool was_js_error;
};
#line 1 "./src/objects/statement.lzz"
class Statement : public node::ObjectWrap, public Query
{
#line 2 "./src/objects/statement.lzz"
  friend class StatementIterator;
#line 3 "./src/objects/statement.lzz"
public:
#line 6 "./src/objects/statement.lzz"
  static v8::MaybeLocal <v8::Object> New (v8::Isolate * isolate, v8::Local <v8::Object> database, v8::Local <v8::String> source);
#line 16 "./src/objects/statement.lzz"
  BindMap * GetBindMap (v8::Isolate * isolate);
#line 29 "./src/objects/statement.lzz"
  void CloseHandles ();
#line 36 "./src/objects/statement.lzz"
  ~ Statement ();
#line 41 "./src/objects/statement.lzz"
private:
#line 43 "./src/objects/statement.lzz"
  explicit Statement (Database * _db, sqlite3_stmt * _handle, bool _returns_data);
#line 59 "./src/objects/statement.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 59 "./src/objects/statement.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 78 "./src/objects/statement.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 114 "./src/objects/statement.lzz"
  static void JS_run (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 132 "./src/objects/statement.lzz"
  static void JS_get (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 150 "./src/objects/statement.lzz"
  static void JS_all (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 174 "./src/objects/statement.lzz"
  static void JS_iterate (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 179 "./src/objects/statement.lzz"
  static void JS_bind (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 189 "./src/objects/statement.lzz"
  static void JS_pluck (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 198 "./src/objects/statement.lzz"
  static void JS_safeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 206 "./src/objects/statement.lzz"
  static void JS_returnsData (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info);
#line 210 "./src/objects/statement.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 211 "./src/objects/statement.lzz"
  static sqlite3_uint64 next_id;
#line 212 "./src/objects/statement.lzz"
  static bool constructing_privileges;
#line 214 "./src/objects/statement.lzz"
  Database * const db;
#line 215 "./src/objects/statement.lzz"
  sqlite3_stmt * const handle;
#line 216 "./src/objects/statement.lzz"
  bool alive;
#line 217 "./src/objects/statement.lzz"
  bool bound;
#line 218 "./src/objects/statement.lzz"
  bool has_bind_map;
#line 219 "./src/objects/statement.lzz"
  bool safe_ints;
#line 220 "./src/objects/statement.lzz"
  bool pluck;
#line 221 "./src/objects/statement.lzz"
  bool const returns_data;
};
#line 1 "./src/objects/transaction.lzz"
class Transaction : public node::ObjectWrap, public Query
{
#line 2 "./src/objects/transaction.lzz"
public:
#line 5 "./src/objects/transaction.lzz"
  static v8::MaybeLocal <v8::Object> New (v8::Isolate * isolate, v8::Local <v8::Object> database, v8::Local <v8::Array> sources);
#line 15 "./src/objects/transaction.lzz"
  BindMap * GetBindMap (v8::Isolate * isolate);
#line 31 "./src/objects/transaction.lzz"
  void CloseHandles ();
#line 39 "./src/objects/transaction.lzz"
  ~ Transaction ();
#line 44 "./src/objects/transaction.lzz"
private:
#line 46 "./src/objects/transaction.lzz"
  explicit Transaction (Database * _db, TransactionHandles * _handles);
#line 63 "./src/objects/transaction.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 63 "./src/objects/transaction.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 77 "./src/objects/transaction.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 141 "./src/objects/transaction.lzz"
  static void JS_run (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 184 "./src/objects/transaction.lzz"
  static void JS_bind (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 194 "./src/objects/transaction.lzz"
  static void JS_safeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 202 "./src/objects/transaction.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 203 "./src/objects/transaction.lzz"
  static sqlite3_uint64 next_id;
#line 204 "./src/objects/transaction.lzz"
  static bool constructing_privileges;
#line 206 "./src/objects/transaction.lzz"
  Database * const db;
#line 207 "./src/objects/transaction.lzz"
  sqlite3_stmt * * const handles;
#line 208 "./src/objects/transaction.lzz"
  int const handle_count;
#line 209 "./src/objects/transaction.lzz"
  bool alive;
#line 210 "./src/objects/transaction.lzz"
  bool bound;
#line 211 "./src/objects/transaction.lzz"
  bool has_bind_map;
#line 212 "./src/objects/transaction.lzz"
  bool safe_ints;
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
#line 33 "./src/objects/statement-iterator.lzz"
  friend void RegisterModule (v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 33 "./src/objects/statement-iterator.lzz"
  static void Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module);
#line 46 "./src/objects/statement-iterator.lzz"
  static void JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 64 "./src/objects/statement-iterator.lzz"
  static void JS_next (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 70 "./src/objects/statement-iterator.lzz"
  static void JS_return (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 76 "./src/objects/statement-iterator.lzz"
  static void JS_symbolIterator (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 80 "./src/objects/statement-iterator.lzz"
  void Next (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 96 "./src/objects/statement-iterator.lzz"
  void Return (v8::FunctionCallbackInfo <v8 :: Value> const & info);
#line 101 "./src/objects/statement-iterator.lzz"
  void Throw ();
#line 107 "./src/objects/statement-iterator.lzz"
  void Cleanup ();
#line 114 "./src/objects/statement-iterator.lzz"
  static v8::Local <v8::Object> NewRecord (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Value> value, bool done = false);
#line 121 "./src/objects/statement-iterator.lzz"
  static v8::Local <v8::Object> DoneRecord (v8::Isolate * isolate);
#line 125 "./src/objects/statement-iterator.lzz"
  static v8::Persistent <v8::Function> constructor;
#line 126 "./src/objects/statement-iterator.lzz"
  static v8::FunctionCallbackInfo <v8 :: Value> const * caller_info;
#line 128 "./src/objects/statement-iterator.lzz"
  Statement * const stmt;
#line 129 "./src/objects/statement-iterator.lzz"
  sqlite3_stmt * const handle;
#line 130 "./src/objects/statement-iterator.lzz"
  bool const safe_ints;
#line 131 "./src/objects/statement-iterator.lzz"
  bool const pluck;
#line 132 "./src/objects/statement-iterator.lzz"
  bool const bound;
#line 133 "./src/objects/statement-iterator.lzz"
  bool alive;
};
#line 1 "./src/util/custom-function.lzz"
class CustomFunction
{
#line 2 "./src/util/custom-function.lzz"
  friend class CustomAggregate;
#line 3 "./src/util/custom-function.lzz"
public:
#line 5 "./src/util/custom-function.lzz"
  explicit CustomFunction (v8::Local <v8::Function> _fn, v8::Isolate * _isolate, Database * _db, char const * _name, int _argc, bool _safe_ints);
#line 7 "./src/util/custom-function.lzz"
  ~ CustomFunction ();
#line 9 "./src/util/custom-function.lzz"
  static void xDestroy (void * instance);
#line 13 "./src/util/custom-function.lzz"
  static void xFunc (sqlite3_context * ctx, int argc, sqlite3_value * * argv);
#line 18 "./src/util/custom-function.lzz"
  static void xStep (sqlite3_context * ctx, int argc, sqlite3_value * * argv);
#line 25 "./src/util/custom-function.lzz"
  static void xFinal (sqlite3_context * ctx);
#line 40 "./src/util/custom-function.lzz"
  void ThrowResultValueError (sqlite3_context * ctx);
#line 45 "./src/util/custom-function.lzz"
private:
#line 46 "./src/util/custom-function.lzz"
  void PropagateJSError (sqlite3_context * ctx);
#line 52 "./src/util/custom-function.lzz"
  static char const * CopyString (char const * source);
#line 59 "./src/util/custom-function.lzz"
  CopyablePersistent <v8::Function> const fn;
#line 60 "./src/util/custom-function.lzz"
  v8::Isolate * const isolate;
#line 61 "./src/util/custom-function.lzz"
  Database * const db;
#line 62 "./src/util/custom-function.lzz"
  char const * const name;
#line 63 "./src/util/custom-function.lzz"
  int const argc;
#line 64 "./src/util/custom-function.lzz"
  bool const safe_ints;
};
#line 1 "./src/util/custom-aggregate.lzz"
class CustomAggregate
{
#line 2 "./src/util/custom-aggregate.lzz"
public:
#line 4 "./src/util/custom-aggregate.lzz"
  struct Entry
  {
#line 5 "./src/util/custom-aggregate.lzz"
    v8::Local <v8::Value> value;
#line 6 "./src/util/custom-aggregate.lzz"
    bool done;
#line 7 "./src/util/custom-aggregate.lzz"
    bool threw;
  };
#line 12 "./src/util/custom-aggregate.lzz"
  void Activate (v8::Isolate * isolate, CustomFunction * cf);
#line 44 "./src/util/custom-aggregate.lzz"
  void Destroy ();
#line 52 "./src/util/custom-aggregate.lzz"
  bool IsUninitialized ();
#line 53 "./src/util/custom-aggregate.lzz"
  bool IsActive ();
#line 54 "./src/util/custom-aggregate.lzz"
  v8::Local <v8::Function> GetFn (v8::Isolate * isolate);
#line 60 "./src/util/custom-aggregate.lzz"
  Entry ProgressGenerator (v8::Isolate * isolate, v8::Local <v8::Context> ctx);
#line 72 "./src/util/custom-aggregate.lzz"
private:
#line 73 "./src/util/custom-aggregate.lzz"
  enum State
  {
#line 73 "./src/util/custom-aggregate.lzz"
    uninitialized = 0,
#line 73 "./src/util/custom-aggregate.lzz"
    active = 1,
#line 73 "./src/util/custom-aggregate.lzz"
    destroyed = 2
  };
#line 74 "./src/util/custom-aggregate.lzz"
  v8::Persistent <v8::Object> generator;
#line 75 "./src/util/custom-aggregate.lzz"
  v8::Persistent <v8::Function> next;
#line 76 "./src/util/custom-aggregate.lzz"
  v8::Persistent <v8::Function> fn;
#line 77 "./src/util/custom-aggregate.lzz"
  State state;
};
#line 53 "./src/util/data.lzz"
namespace Data
{
#line 55 "./src/util/data.lzz"
  v8::Local <v8::Value> GetValueJS (v8::Isolate * isolate, sqlite3_stmt * handle, int column, bool safe_ints);
}
#line 53 "./src/util/data.lzz"
namespace Data
{
#line 59 "./src/util/data.lzz"
  v8::Local <v8::Value> GetValueJS (v8::Isolate * isolate, sqlite3_value * value, bool safe_ints);
}
#line 53 "./src/util/data.lzz"
namespace Data
{
#line 63 "./src/util/data.lzz"
  v8::Local <v8::Value> GetRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints);
}
#line 53 "./src/util/data.lzz"
namespace Data
{
#line 74 "./src/util/data.lzz"
  v8::Local <v8::Value> * GetArgumentsJS (v8::Isolate * isolate, sqlite3_value * * values, int argument_count, bool safe_ints);
}
#line 53 "./src/util/data.lzz"
namespace Data
{
#line 85 "./src/util/data.lzz"
  int BindValueFromJS (sqlite3_stmt * handle, int index, v8::Local <v8::Value> value);
}
#line 53 "./src/util/data.lzz"
namespace Data
{
#line 90 "./src/util/data.lzz"
  void ResultValueFromJS (sqlite3_context * ctx, v8::Local <v8::Value> value, CustomFunction * function);
}
#line 1 "./src/binding/binder.lzz"
class Binder
{
#line 2 "./src/binding/binder.lzz"
public:
#line 4 "./src/binding/binder.lzz"
  explicit Binder (sqlite3_stmt * _handle);
#line 11 "./src/binding/binder.lzz"
  bool Bind (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Statement * query);
#line 28 "./src/binding/binder.lzz"
protected:
#line 29 "./src/binding/binder.lzz"
  struct Result
  {
#line 30 "./src/binding/binder.lzz"
    int count;
#line 31 "./src/binding/binder.lzz"
    bool bound_object;
  };
#line 34 "./src/binding/binder.lzz"
  static bool IsPlainObject (v8::Isolate * isolate, v8::Local <v8::Object> obj);
#line 43 "./src/binding/binder.lzz"
  void Fail (void (* Throw) (char const *), char const * message);
#line 51 "./src/binding/binder.lzz"
  virtual int NextAnonIndex ();
#line 57 "./src/binding/binder.lzz"
  void BindValue (v8::Local <v8::Value> value, int index);
#line 78 "./src/binding/binder.lzz"
  int BindArray (v8::Local <v8::Context> ctx, v8::Local <v8::Array> arr);
#line 103 "./src/binding/binder.lzz"
  virtual int BindObject (v8::Isolate * isolate, v8::Local <v8::Object> obj, Query * query);
#line 147 "./src/binding/binder.lzz"
  Result BindArgs (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Query * query);
#line 184 "./src/binding/binder.lzz"
  sqlite3_stmt * handle;
#line 185 "./src/binding/binder.lzz"
  int param_count;
#line 186 "./src/binding/binder.lzz"
  int anon_index;
#line 187 "./src/binding/binder.lzz"
  bool success;
};
#line 1 "./src/binding/multi-binder.lzz"
class MultiBinder : public Binder
{
#line 2 "./src/binding/multi-binder.lzz"
public:
#line 4 "./src/binding/multi-binder.lzz"
  explicit MultiBinder (sqlite3_stmt * * _handles, int _handle_count);
#line 10 "./src/binding/multi-binder.lzz"
  bool Bind (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Transaction * query);
#line 33 "./src/binding/multi-binder.lzz"
protected:
#line 34 "./src/binding/multi-binder.lzz"
  int NextAnonIndex ();
#line 57 "./src/binding/multi-binder.lzz"
  int BindObject (v8::Isolate * isolate, v8::Local <v8::Object> obj, Query * query);
#line 100 "./src/binding/multi-binder.lzz"
  sqlite3_stmt * * const handles;
#line 101 "./src/binding/multi-binder.lzz"
  int const handle_count;
#line 102 "./src/binding/multi-binder.lzz"
  int handle_index;
#line 103 "./src/binding/multi-binder.lzz"
  int param_count_sum;
};
#line 36 "./src/better_sqlite3.lzz"
void RegisterModule (v8::Local <v8::Object> exports, v8::Local <v8::Object> module);
#line 18 "./src/util/macros.lzz"
LZZ_INLINE v8::Local <v8::String> StringFromUtf8 (v8::Isolate * isolate, char const * data, int length)
#line 18 "./src/util/macros.lzz"
                                                                                                {
        return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kNormal, length).ToLocalChecked();
}
#line 21 "./src/util/macros.lzz"
LZZ_INLINE v8::Local <v8::String> StringFromUtf16 (v8::Isolate * isolate, uint16_t const * data, int length)
#line 21 "./src/util/macros.lzz"
                                                                                                     {
        return v8::String::NewFromTwoByte(isolate, data, v8::NewStringType::kNormal, length).ToLocalChecked();
}
#line 24 "./src/util/macros.lzz"
LZZ_INLINE v8::Local <v8::String> InternalizedFromUtf8 (v8::Isolate * isolate, char const * data, int length)
#line 24 "./src/util/macros.lzz"
                                                                                                      {
        return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kInternalized, length).ToLocalChecked();
}
#line 28 "./src/util/macros.lzz"
LZZ_INLINE void SetFrozen (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Object> obj, ConstantString & key, v8::Local <v8::Value> value)
#line 28 "./src/util/macros.lzz"
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
#line 99 "./src/util/macros.lzz"
LZZ_INLINE void NODE_SET_PROTOTYPE_GETTER (v8::Local <v8::FunctionTemplate> recv, char const * name, v8::AccessorGetterCallback getter)
#line 99 "./src/util/macros.lzz"
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
#line 113 "./src/util/macros.lzz"
LZZ_INLINE void NODE_SET_PROTOTYPE_SYMBOL_METHOD (v8::Local <v8::FunctionTemplate> recv, v8::Local <v8::Symbol> symbol, v8::FunctionCallback callback)
#line 113 "./src/util/macros.lzz"
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
#line 20 "./src/util/transaction-handles.lzz"
LZZ_INLINE void TransactionHandles::Add (sqlite3_stmt * handle)
#line 20 "./src/util/transaction-handles.lzz"
                                              {
                handles[handle_count++] = handle;
}
#line 15 "./src/util/sql-string.lzz"
LZZ_INLINE void SQLString::AddStatement (v8::Local <v8::String> source)
#line 15 "./src/util/sql-string.lzz"
                                                               {
                StatementString* string = new (strings + count++) StatementString(source);
                total_character_count += string->value.length();
                if (string->missing_semicolon) total_character_count += 1;
}
#line 21 "./src/util/sql-string.lzz"
LZZ_INLINE v8::String::Value const * SQLString::GetStatement (uint32_t index)
#line 21 "./src/util/sql-string.lzz"
                                                                     {
                return &strings[index].value;
}
#line 12 "./src/util/bind-map.lzz"
LZZ_INLINE int BindMap::Pair::GetIndex ()
#line 12 "./src/util/bind-map.lzz"
                                              {
                                return index;
}
#line 16 "./src/util/bind-map.lzz"
LZZ_INLINE v8::Local <v8::String> BindMap::Pair::GetName (v8::Isolate * isolate)
#line 16 "./src/util/bind-map.lzz"
                                                                                   {
                                return v8::Local<v8::String>::New(isolate, name);
}
#line 43 "./src/util/bind-map.lzz"
LZZ_INLINE BindMap::Pair * BindMap::GetPairs ()
#line 43 "./src/util/bind-map.lzz"
                                { return pairs;
}
#line 44 "./src/util/bind-map.lzz"
LZZ_INLINE int BindMap::GetSize ()
#line 44 "./src/util/bind-map.lzz"
                             { return length;
}
#line 68 "./src/util/bind-map.lzz"
LZZ_INLINE int BindMap::GetParameterIndex (int index)
#line 68 "./src/util/bind-map.lzz"
                                                       {
                return index & PARAMETER_MASK;
}
#line 71 "./src/util/bind-map.lzz"
LZZ_INLINE int BindMap::GetTransactionIndex (int index)
#line 71 "./src/util/bind-map.lzz"
                                                         {
                return index >> PARAMETER_BITS;
}
#line 5 "./src/objects/query.lzz"
template <typename T>
#line 6 "./src/objects/query.lzz"
bool Query::Compare::operator () (T const * const a, T const * const b) const
#line 6 "./src/objects/query.lzz"
                                                                             {
                        return a->extras->id < b->extras->id;
}
#line 24 "./src/objects/query.lzz"
LZZ_INLINE BindMap * Query::BindMapPointer ()
#line 24 "./src/objects/query.lzz"
                                         {
                return &extras->bind_map;
}
#line 14 "./src/objects/database.lzz"
LZZ_INLINE void Database::AddStatement (Statement * stmt)
#line 14 "./src/objects/database.lzz"
                                                  { extras->stmts.insert(extras->stmts.end(), stmt);
}
#line 15 "./src/objects/database.lzz"
LZZ_INLINE void Database::RemoveStatement (Statement * stmt)
#line 15 "./src/objects/database.lzz"
                                                     { extras->stmts.erase(stmt);
}
#line 16 "./src/objects/database.lzz"
LZZ_INLINE void Database::AddTransaction (Transaction * trans)
#line 16 "./src/objects/database.lzz"
                                                       { extras->transs.insert(extras->transs.end(), trans);
}
#line 17 "./src/objects/database.lzz"
LZZ_INLINE void Database::RemoveTransaction (Transaction * trans)
#line 17 "./src/objects/database.lzz"
                                                          { extras->transs.erase(trans);
}
#line 37 "./src/objects/database.lzz"
LZZ_INLINE Database::State * Database::GetState ()
#line 37 "./src/objects/database.lzz"
                                 {
                return reinterpret_cast<State*>(&open);
}
#line 40 "./src/objects/database.lzz"
LZZ_INLINE sqlite3 * Database::GetHandle ()
#line 40 "./src/objects/database.lzz"
                                    {
                return db_handle;
}
#line 43 "./src/objects/database.lzz"
LZZ_INLINE Database::TransactionController Database::GetTransactionController ()
#line 43 "./src/objects/database.lzz"
                                                                {
                return { extras->begin, extras->commit, extras->rollback };
}
#line 44 "./src/util/custom-aggregate.lzz"
LZZ_INLINE void CustomAggregate::Destroy ()
#line 44 "./src/util/custom-aggregate.lzz"
                              {
                assert(state == active);
                generator.Reset();
                next.Reset();
                fn.Reset();
                state = destroyed;
}
#line 52 "./src/util/custom-aggregate.lzz"
LZZ_INLINE bool CustomAggregate::IsUninitialized ()
#line 52 "./src/util/custom-aggregate.lzz"
                                      { return state == uninitialized;
}
#line 53 "./src/util/custom-aggregate.lzz"
LZZ_INLINE bool CustomAggregate::IsActive ()
#line 53 "./src/util/custom-aggregate.lzz"
                               { return state == active;
}
#line 54 "./src/util/custom-aggregate.lzz"
LZZ_INLINE v8::Local <v8::Function> CustomAggregate::GetFn (v8::Isolate * isolate)
#line 54 "./src/util/custom-aggregate.lzz"
                                                                   {
                return v8::Local<v8::Function>::New(isolate, fn);
}
#undef LZZ_INLINE
#endif
