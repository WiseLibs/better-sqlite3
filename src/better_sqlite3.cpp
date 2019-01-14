// better_sqlite3.cpp
//

#include "better_sqlite3.hpp"
#line 14 "./src/better_sqlite3.lzz"
NODE_MODULE(better_sqlite3, RegisterModule);
#define LZZ_INLINE inline
#line 35 "./src/util/macros.lzz"
void ThrowError (char const * message)
#line 35 "./src/util/macros.lzz"
                                     { v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ; isolate->ThrowException(v8::Exception::Error(StringFromUtf8(isolate, message, -1)));
}
#line 36 "./src/util/macros.lzz"
void ThrowTypeError (char const * message)
#line 36 "./src/util/macros.lzz"
                                         { v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ; isolate->ThrowException(v8::Exception::TypeError(StringFromUtf8(isolate, message, -1)));
}
#line 37 "./src/util/macros.lzz"
void ThrowRangeError (char const * message)
#line 37 "./src/util/macros.lzz"
                                          { v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ; isolate->ThrowException(v8::Exception::RangeError(StringFromUtf8(isolate, message, -1)));
}
#line 88 "./src/util/macros.lzz"
std::string CONCAT (char const * a, char const * b, char const * c)
#line 88 "./src/util/macros.lzz"
                                                                {
        std::string result(a);
        result += b;
        result += c;
        return result;
}
#line 96 "./src/util/macros.lzz"
char const * COPY (char const * source)
#line 96 "./src/util/macros.lzz"
                                     {
        size_t bytes = strlen(source) + 1;
        char* dest = new char[bytes];
        memcpy(dest, source, bytes);
        return dest;
}
#line 113 "./src/util/macros.lzz"
v8::Local <v8::Value> Require (v8::Local <v8::Object> module, char const * path)
#line 113 "./src/util/macros.lzz"
                                                                             {
        v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ;
        v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
        v8::Local<v8::Function> require = v8::Local<v8::Function>::Cast(module->Get(ctx, StringFromUtf8(isolate, "require", -1)).ToLocalChecked());
        v8::Local<v8::Value> requireArg = StringFromUtf8(isolate, path, -1);
        return require->Call(ctx, module, 1, &requireArg).ToLocalChecked();
}
#line 6 "./src/util/constants.lzz"
v8::Local <v8::String> CS::Code (v8::Isolate * isolate, int code)
#line 6 "./src/util/constants.lzz"
                                                                          {
                auto element = codes.find(code);
                if (element != codes.end()) return v8::Local<v8::String>::New(isolate, element->second);
                return StringFromUtf8(isolate, CONCAT("UNKNOWN_SQLITE_ERROR_", std::to_string(code).c_str(), "").c_str(), -1);
}
#line 12 "./src/util/constants.lzz"
ConstantString CS::database;
#line 13 "./src/util/constants.lzz"
ConstantString CS::reader;
#line 14 "./src/util/constants.lzz"
ConstantString CS::source;
#line 15 "./src/util/constants.lzz"
ConstantString CS::memory;
#line 16 "./src/util/constants.lzz"
ConstantString CS::readonly;
#line 17 "./src/util/constants.lzz"
ConstantString CS::name;
#line 18 "./src/util/constants.lzz"
ConstantString CS::next;
#line 19 "./src/util/constants.lzz"
ConstantString CS::length;
#line 20 "./src/util/constants.lzz"
ConstantString CS::done;
#line 21 "./src/util/constants.lzz"
ConstantString CS::value;
#line 22 "./src/util/constants.lzz"
ConstantString CS::changes;
#line 23 "./src/util/constants.lzz"
ConstantString CS::lastInsertRowid;
#line 24 "./src/util/constants.lzz"
ConstantString CS::code;
#line 25 "./src/util/constants.lzz"
ConstantString CS::statement;
#line 26 "./src/util/constants.lzz"
ConstantString CS::column;
#line 27 "./src/util/constants.lzz"
ConstantString CS::table;
#line 28 "./src/util/constants.lzz"
ConstantString CS::type;
#line 29 "./src/util/constants.lzz"
ConstantString CS::filename;
#line 30 "./src/util/constants.lzz"
ConstantString CS::pending;
#line 31 "./src/util/constants.lzz"
ConstantString CS::completed;
#line 32 "./src/util/constants.lzz"
ConstantString CS::aborted;
#line 33 "./src/util/constants.lzz"
ConstantString CS::totalPages;
#line 34 "./src/util/constants.lzz"
ConstantString CS::remainingPages;
#line 37 "./src/util/constants.lzz"
void CS::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 37 "./src/util/constants.lzz"
                       {
                AddString(isolate, CS::database, "database");
                AddString(isolate, CS::reader, "reader");
                AddString(isolate, CS::source, "source");
                AddString(isolate, CS::memory, "memory");
                AddString(isolate, CS::readonly, "readonly");
                AddString(isolate, CS::name, "name");
                AddString(isolate, CS::next, "next");
                AddString(isolate, CS::length, "length");
                AddString(isolate, CS::done, "done");
                AddString(isolate, CS::value, "value");
                AddString(isolate, CS::changes, "changes");
                AddString(isolate, CS::lastInsertRowid, "lastInsertRowid");
                AddString(isolate, CS::code, "code");
                AddString(isolate, CS::statement, "statement");
                AddString(isolate, CS::column, "column");
                AddString(isolate, CS::table, "table");
                AddString(isolate, CS::type, "type");
                AddString(isolate, CS::filename, "filename");
                AddString(isolate, CS::totalPages, "totalPages");
                AddString(isolate, CS::remainingPages, "remainingPages");

                AddCode(isolate, SQLITE_OK, "SQLITE_OK");
                AddCode(isolate, SQLITE_ERROR, "SQLITE_ERROR");
                AddCode(isolate, SQLITE_INTERNAL, "SQLITE_INTERNAL");
                AddCode(isolate, SQLITE_PERM, "SQLITE_PERM");
                AddCode(isolate, SQLITE_ABORT, "SQLITE_ABORT");
                AddCode(isolate, SQLITE_BUSY, "SQLITE_BUSY");
                AddCode(isolate, SQLITE_LOCKED, "SQLITE_LOCKED");
                AddCode(isolate, SQLITE_NOMEM, "SQLITE_NOMEM");
                AddCode(isolate, SQLITE_READONLY, "SQLITE_READONLY");
                AddCode(isolate, SQLITE_INTERRUPT, "SQLITE_INTERRUPT");
                AddCode(isolate, SQLITE_IOERR, "SQLITE_IOERR");
                AddCode(isolate, SQLITE_CORRUPT, "SQLITE_CORRUPT");
                AddCode(isolate, SQLITE_NOTFOUND, "SQLITE_NOTFOUND");
                AddCode(isolate, SQLITE_FULL, "SQLITE_FULL");
                AddCode(isolate, SQLITE_CANTOPEN, "SQLITE_CANTOPEN");
                AddCode(isolate, SQLITE_PROTOCOL, "SQLITE_PROTOCOL");
                AddCode(isolate, SQLITE_EMPTY, "SQLITE_EMPTY");
                AddCode(isolate, SQLITE_SCHEMA, "SQLITE_SCHEMA");
                AddCode(isolate, SQLITE_TOOBIG, "SQLITE_TOOBIG");
                AddCode(isolate, SQLITE_CONSTRAINT, "SQLITE_CONSTRAINT");
                AddCode(isolate, SQLITE_MISMATCH, "SQLITE_MISMATCH");
                AddCode(isolate, SQLITE_MISUSE, "SQLITE_MISUSE");
                AddCode(isolate, SQLITE_NOLFS, "SQLITE_NOLFS");
                AddCode(isolate, SQLITE_AUTH, "SQLITE_AUTH");
                AddCode(isolate, SQLITE_FORMAT, "SQLITE_FORMAT");
                AddCode(isolate, SQLITE_RANGE, "SQLITE_RANGE");
                AddCode(isolate, SQLITE_NOTADB, "SQLITE_NOTADB");
                AddCode(isolate, SQLITE_NOTICE, "SQLITE_NOTICE");
                AddCode(isolate, SQLITE_WARNING, "SQLITE_WARNING");
                AddCode(isolate, SQLITE_ROW, "SQLITE_ROW");
                AddCode(isolate, SQLITE_DONE, "SQLITE_DONE");
                AddCode(isolate, SQLITE_IOERR_READ, "SQLITE_IOERR_READ");
                AddCode(isolate, SQLITE_IOERR_SHORT_READ, "SQLITE_IOERR_SHORT_READ");
                AddCode(isolate, SQLITE_IOERR_WRITE, "SQLITE_IOERR_WRITE");
                AddCode(isolate, SQLITE_IOERR_FSYNC, "SQLITE_IOERR_FSYNC");
                AddCode(isolate, SQLITE_IOERR_DIR_FSYNC, "SQLITE_IOERR_DIR_FSYNC");
                AddCode(isolate, SQLITE_IOERR_TRUNCATE, "SQLITE_IOERR_TRUNCATE");
                AddCode(isolate, SQLITE_IOERR_FSTAT, "SQLITE_IOERR_FSTAT");
                AddCode(isolate, SQLITE_IOERR_UNLOCK, "SQLITE_IOERR_UNLOCK");
                AddCode(isolate, SQLITE_IOERR_RDLOCK, "SQLITE_IOERR_RDLOCK");
                AddCode(isolate, SQLITE_IOERR_DELETE, "SQLITE_IOERR_DELETE");
                AddCode(isolate, SQLITE_IOERR_BLOCKED, "SQLITE_IOERR_BLOCKED");
                AddCode(isolate, SQLITE_IOERR_NOMEM, "SQLITE_IOERR_NOMEM");
                AddCode(isolate, SQLITE_IOERR_ACCESS, "SQLITE_IOERR_ACCESS");
                AddCode(isolate, SQLITE_IOERR_CHECKRESERVEDLOCK, "SQLITE_IOERR_CHECKRESERVEDLOCK");
                AddCode(isolate, SQLITE_IOERR_LOCK, "SQLITE_IOERR_LOCK");
                AddCode(isolate, SQLITE_IOERR_CLOSE, "SQLITE_IOERR_CLOSE");
                AddCode(isolate, SQLITE_IOERR_DIR_CLOSE, "SQLITE_IOERR_DIR_CLOSE");
                AddCode(isolate, SQLITE_IOERR_SHMOPEN, "SQLITE_IOERR_SHMOPEN");
                AddCode(isolate, SQLITE_IOERR_SHMSIZE, "SQLITE_IOERR_SHMSIZE");
                AddCode(isolate, SQLITE_IOERR_SHMLOCK, "SQLITE_IOERR_SHMLOCK");
                AddCode(isolate, SQLITE_IOERR_SHMMAP, "SQLITE_IOERR_SHMMAP");
                AddCode(isolate, SQLITE_IOERR_SEEK, "SQLITE_IOERR_SEEK");
                AddCode(isolate, SQLITE_IOERR_DELETE_NOENT, "SQLITE_IOERR_DELETE_NOENT");
                AddCode(isolate, SQLITE_IOERR_MMAP, "SQLITE_IOERR_MMAP");
                AddCode(isolate, SQLITE_IOERR_GETTEMPPATH, "SQLITE_IOERR_GETTEMPPATH");
                AddCode(isolate, SQLITE_IOERR_CONVPATH, "SQLITE_IOERR_CONVPATH");
                AddCode(isolate, SQLITE_IOERR_VNODE, "SQLITE_IOERR_VNODE");
                AddCode(isolate, SQLITE_IOERR_AUTH, "SQLITE_IOERR_AUTH");
                AddCode(isolate, SQLITE_LOCKED_SHAREDCACHE, "SQLITE_LOCKED_SHAREDCACHE");
                AddCode(isolate, SQLITE_BUSY_RECOVERY, "SQLITE_BUSY_RECOVERY");
                AddCode(isolate, SQLITE_BUSY_SNAPSHOT, "SQLITE_BUSY_SNAPSHOT");
                AddCode(isolate, SQLITE_CANTOPEN_NOTEMPDIR, "SQLITE_CANTOPEN_NOTEMPDIR");
                AddCode(isolate, SQLITE_CANTOPEN_ISDIR, "SQLITE_CANTOPEN_ISDIR");
                AddCode(isolate, SQLITE_CANTOPEN_FULLPATH, "SQLITE_CANTOPEN_FULLPATH");
                AddCode(isolate, SQLITE_CANTOPEN_CONVPATH, "SQLITE_CANTOPEN_CONVPATH");
                AddCode(isolate, SQLITE_CORRUPT_VTAB, "SQLITE_CORRUPT_VTAB");
                AddCode(isolate, SQLITE_READONLY_RECOVERY, "SQLITE_READONLY_RECOVERY");
                AddCode(isolate, SQLITE_READONLY_CANTLOCK, "SQLITE_READONLY_CANTLOCK");
                AddCode(isolate, SQLITE_READONLY_ROLLBACK, "SQLITE_READONLY_ROLLBACK");
                AddCode(isolate, SQLITE_READONLY_DBMOVED, "SQLITE_READONLY_DBMOVED");
                AddCode(isolate, SQLITE_ABORT_ROLLBACK, "SQLITE_ABORT_ROLLBACK");
                AddCode(isolate, SQLITE_CONSTRAINT_CHECK, "SQLITE_CONSTRAINT_CHECK");
                AddCode(isolate, SQLITE_CONSTRAINT_COMMITHOOK, "SQLITE_CONSTRAINT_COMMITHOOK");
                AddCode(isolate, SQLITE_CONSTRAINT_FOREIGNKEY, "SQLITE_CONSTRAINT_FOREIGNKEY");
                AddCode(isolate, SQLITE_CONSTRAINT_FUNCTION, "SQLITE_CONSTRAINT_FUNCTION");
                AddCode(isolate, SQLITE_CONSTRAINT_NOTNULL, "SQLITE_CONSTRAINT_NOTNULL");
                AddCode(isolate, SQLITE_CONSTRAINT_PRIMARYKEY, "SQLITE_CONSTRAINT_PRIMARYKEY");
                AddCode(isolate, SQLITE_CONSTRAINT_TRIGGER, "SQLITE_CONSTRAINT_TRIGGER");
                AddCode(isolate, SQLITE_CONSTRAINT_UNIQUE, "SQLITE_CONSTRAINT_UNIQUE");
                AddCode(isolate, SQLITE_CONSTRAINT_VTAB, "SQLITE_CONSTRAINT_VTAB");
                AddCode(isolate, SQLITE_CONSTRAINT_ROWID, "SQLITE_CONSTRAINT_ROWID");
                AddCode(isolate, SQLITE_NOTICE_RECOVER_WAL, "SQLITE_NOTICE_RECOVER_WAL");
                AddCode(isolate, SQLITE_NOTICE_RECOVER_ROLLBACK, "SQLITE_NOTICE_RECOVER_ROLLBACK");
                AddCode(isolate, SQLITE_WARNING_AUTOINDEX, "SQLITE_WARNING_AUTOINDEX");
                AddCode(isolate, SQLITE_AUTH_USER, "SQLITE_AUTH_USER");
                AddCode(isolate, SQLITE_OK_LOAD_PERMANENTLY, "SQLITE_OK_LOAD_PERMANENTLY");
}
#line 148 "./src/util/constants.lzz"
v8::Local <v8::String> CS::InternalizedFromLatin1 (v8::Isolate * isolate, char const * str)
#line 148 "./src/util/constants.lzz"
                                                                                                   {
                return v8::String::NewFromOneByte(isolate, reinterpret_cast<const uint8_t*>(str), v8::NewStringType::kInternalized).ToLocalChecked();
}
#line 151 "./src/util/constants.lzz"
void CS::AddString (v8::Isolate * isolate, ConstantString & constant, char const * str)
#line 151 "./src/util/constants.lzz"
                                                                                               {
                constant.Reset(isolate, InternalizedFromLatin1(isolate, str));
}
#line 154 "./src/util/constants.lzz"
void CS::AddCode (v8::Isolate * isolate, int code, char const * str)
#line 154 "./src/util/constants.lzz"
                                                                             {
                codes.emplace(std::piecewise_construct, std::forward_as_tuple(code), std::forward_as_tuple(isolate, InternalizedFromLatin1(isolate, str)));
}
#line 157 "./src/util/constants.lzz"
CS::CS (char _)
#line 157 "./src/util/constants.lzz"
                            { assert(false);
}
#line 159 "./src/util/constants.lzz"
std::unordered_map <int, ConstantString> CS::codes;
#line 19 "./src/util/bind-map.lzz"
BindMap::Pair::Pair (v8::Isolate * isolate, char const * _name, int _index)
#line 20 "./src/util/bind-map.lzz"
  : name (isolate, InternalizedFromUtf8(isolate, _name, -1)), index (_index)
#line 20 "./src/util/bind-map.lzz"
                                                                                                         {}
#line 22 "./src/util/bind-map.lzz"
BindMap::Pair::Pair (v8::Isolate * isolate, Pair * pair)
#line 23 "./src/util/bind-map.lzz"
  : name (isolate, pair->name), index (pair->index)
#line 23 "./src/util/bind-map.lzz"
                                                                                {}
#line 29 "./src/util/bind-map.lzz"
BindMap::BindMap (char _)
#line 29 "./src/util/bind-map.lzz"
                                 {
                assert(_ == 0);
                pairs = NULL;
                capacity = 0;
                length = 0;
}
#line 36 "./src/util/bind-map.lzz"
BindMap::~ BindMap ()
#line 36 "./src/util/bind-map.lzz"
                   {
                while (length) pairs[--length].~Pair();
                FREE_ARRAY<Pair>(pairs);
}
#line 45 "./src/util/bind-map.lzz"
void BindMap::Add (v8::Isolate * isolate, char const * name, int index)
#line 45 "./src/util/bind-map.lzz"
                                                                    {
                assert(name != NULL);
                if (capacity == length) Grow(isolate);
                new (pairs + length++) Pair(isolate, name, index);
}
#line 52 "./src/util/bind-map.lzz"
void BindMap::Grow (v8::Isolate * isolate)
#line 52 "./src/util/bind-map.lzz"
                                        {
                assert(capacity == length);
                capacity = (capacity << 1) | 2;
                Pair* new_pairs = ALLOC_ARRAY<Pair>(capacity);
                for (int i=0; i<length; ++i) {
                        new (new_pairs + i) Pair(isolate, pairs + i);
                        pairs[i].~Pair();
                }
                FREE_ARRAY<Pair>(pairs);
                pairs = new_pairs;
}
#line 4 "./src/util/integer.lzz"
bool Integer::HasInstance (v8::Isolate * isolate, v8::Local <v8::Value> value)
#line 4 "./src/util/integer.lzz"
                                                                                  {
                return v8::Local<v8::Boolean>::Cast(
                        v8::Local<v8::Function>::New(isolate, isInstance)->Call( isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), 1, &value).ToLocalChecked()
                )->Value();
}
#line 10 "./src/util/integer.lzz"
sqlite3_int64 Integer::GetValue (v8::Local <v8::Object> integer)
#line 10 "./src/util/integer.lzz"
                                                                     {
                return static_cast<Integer*>(integer->GetAlignedPointerFromInternalField(0))->value;
}
#line 14 "./src/util/integer.lzz"
v8::Local <v8::Value> Integer::New (v8::Isolate * isolate, sqlite3_int64 value, bool safe_ints)
#line 14 "./src/util/integer.lzz"
                                                                                                   {
                if (safe_ints) {
                        *controller = { true, value };
                        return v8::Local<v8::Function>::New(isolate, constructor)->NewInstance( isolate -> GetCurrentContext ( ) ).ToLocalChecked();
                }
                return v8::Number::New(isolate, (double)value);
}
#line 23 "./src/util/integer.lzz"
void Integer::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 23 "./src/util/integer.lzz"
                       {
                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                v8::Local<v8::Function> _constructor = v8::Local<v8::Function>::Cast(Require(module, "integer"));
                v8::Local<v8::Function> _isInstance = v8::Local<v8::Function>::Cast(_constructor->Get(ctx, StringFromUtf8(isolate, "isInstance", -1)).ToLocalChecked());
                v8::Local<v8::Object> prototype = v8::Local<v8::Object>::Cast(_constructor->Get(ctx, StringFromUtf8(isolate, "prototype", -1)).ToLocalChecked());
                constructor.Reset(isolate, _constructor);
                isInstance.Reset(isolate, _isInstance);
                controller = static_cast<ConstructorController*>(prototype->GetAlignedPointerFromInternalField(0));
}
#line 33 "./src/util/integer.lzz"
Integer::Integer (char _)
#line 33 "./src/util/integer.lzz"
  : node::ObjectWrap ()
#line 33 "./src/util/integer.lzz"
                                                      { assert(false);
}
#line 40 "./src/util/integer.lzz"
v8::Persistent <v8::Function> Integer::constructor;
#line 41 "./src/util/integer.lzz"
v8::Persistent <v8::Function> Integer::isInstance;
#line 42 "./src/util/integer.lzz"
Integer::ConstructorController * Integer::controller;
#line 7 "./src/objects/database.lzz"
void Database::ThrowDatabaseError ()
#line 7 "./src/objects/database.lzz"
                                  {
                if (was_js_error) was_js_error = false;
                else ThrowSqliteError(db_handle);
}
#line 11 "./src/objects/database.lzz"
void Database::ThrowSqliteError (sqlite3 * db_handle)
#line 11 "./src/objects/database.lzz"
                                                         {
                assert(db_handle != NULL);
                ThrowSqliteError(sqlite3_errmsg(db_handle), sqlite3_extended_errcode(db_handle));
}
#line 15 "./src/objects/database.lzz"
void Database::ThrowSqliteError (char const * message, int code)
#line 15 "./src/objects/database.lzz"
                                                                    {
                assert(message != NULL);
                assert((code & 0xff) != SQLITE_OK);
                assert((code & 0xff) != SQLITE_ROW);
                assert((code & 0xff) != SQLITE_DONE);
                v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ;
                v8::Local<v8::Value> args[2] = { StringFromUtf8(isolate, message, -1), CS::Code(isolate, code) };
                isolate->ThrowException(v8::Local<v8::Function>::New(isolate, SqliteError)->NewInstance( isolate -> GetCurrentContext ( ) , 2, args).ToLocalChecked());
}
#line 50 "./src/objects/database.lzz"
Database::~ Database ()
#line 50 "./src/objects/database.lzz"
                    {
                if (open) dbs.erase(this);
                CloseHandles();
}
#line 58 "./src/objects/database.lzz"
bool Database::CompareDatabase::operator () (Database const * const a, Database const * const b) const
#line 58 "./src/objects/database.lzz"
                                                                                           {
                        return a < b;
}
#line 64 "./src/objects/database.lzz"
bool Database::CompareStatement::operator () (Statement const * const a, Statement const * const b) const
#line 64 "./src/objects/database.lzz"
                                                                                             {
                        return Statement::Compare(a, b);
}
#line 70 "./src/objects/database.lzz"
bool Database::CompareBackup::operator () (Backup const * const a, Backup const * const b) const
#line 70 "./src/objects/database.lzz"
                                                                                       {
                        return Backup::Compare(a, b);
}
#line 75 "./src/objects/database.lzz"
Database::Database (sqlite3 * _db_handle)
#line 75 "./src/objects/database.lzz"
  : node::ObjectWrap (), db_handle (_db_handle), open (true), busy (false), pragma_mode (false), safe_ints (false), was_js_error (false), stmts (), backups ()
#line 83 "./src/objects/database.lzz"
                          {
                assert(_db_handle != NULL);
                dbs.insert(this);
}
#line 88 "./src/objects/database.lzz"
void Database::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 88 "./src/objects/database.lzz"
                       {
                v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, JS_new);
                t->InstanceTemplate()->SetInternalFieldCount(1);
                t->SetClassName(StringFromUtf8(isolate, "Database", -1));

                NODE_SET_PROTOTYPE_METHOD(t, "prepare", JS_prepare);
                NODE_SET_PROTOTYPE_METHOD(t, "exec", JS_exec);
                NODE_SET_PROTOTYPE_METHOD(t, "pragma", JS_pragma);
                NODE_SET_PROTOTYPE_METHOD(t, "checkpoint", JS_checkpoint);
                NODE_SET_PROTOTYPE_METHOD(t, "backup", JS_backup);
                NODE_SET_PROTOTYPE_METHOD(t, "function", JS_function);
                NODE_SET_PROTOTYPE_METHOD(t, "aggregate", JS_aggregate);
                NODE_SET_PROTOTYPE_METHOD(t, "loadExtension", JS_loadExtension);
                NODE_SET_PROTOTYPE_METHOD(t, "close", JS_close);
                NODE_SET_PROTOTYPE_METHOD(t, "defaultSafeIntegers", JS_defaultSafeIntegers);
                NODE_SET_PROTOTYPE_GETTER(t, "open", JS_open);
                NODE_SET_PROTOTYPE_GETTER(t, "inTransaction", JS_inTransaction);

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                exports->Set(ctx, StringFromUtf8(isolate, "Database", -1), t->GetFunction(ctx).ToLocalChecked()).FromJust();
                SqliteError.Reset(isolate, v8::Local<v8::Function>::Cast(Require(module, "../lib/sqlite-error")));
                node::AtExit(Database::AtExit);
}
#line 112 "./src/objects/database.lzz"
void Database::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 112 "./src/objects/database.lzz"
                            {
                assert(info.IsConstructCall());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > filename = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > filenameGiven = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                if ( info . Length ( ) <= ( 2 ) || ! info [ 2 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "third" " argument to be " "a boolean" ) ; bool in_memory = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 2 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 3 ) || ! info [ 3 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fourth" " argument to be " "a boolean" ) ; bool readonly = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 3 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 4 ) || ! info [ 4 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fifth" " argument to be " "a boolean" ) ; bool must_exist = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 4 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 5 ) || ! info [ 5 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "sixth" " argument to be " "a 32-bit signed integer" ) ; int timeout = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 5 ] ) -> Value ( ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                sqlite3* db_handle;
                v8::String::Utf8Value utf8(EXTRACT_STRING(isolate, filename));
                int mask = readonly ? SQLITE_OPEN_READONLY
                        : must_exist ? SQLITE_OPEN_READWRITE
                        : (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

                if (sqlite3_open_v2(*utf8, &db_handle, mask, NULL) != SQLITE_OK) {
                        ThrowSqliteError(db_handle);
                        int status = sqlite3_close(db_handle);
                        assert(status == SQLITE_OK); ((void)status);
                        return;
                }

                assert(sqlite3_db_mutex(db_handle) == NULL);
                sqlite3_extended_result_codes(db_handle, 1);
                sqlite3_busy_timeout(db_handle, timeout);
                sqlite3_limit(db_handle, SQLITE_LIMIT_LENGTH, MAX_BUFFER_SIZE < MAX_STRING_SIZE ? MAX_BUFFER_SIZE : MAX_STRING_SIZE);
                sqlite3_limit(db_handle, SQLITE_LIMIT_SQL_LENGTH, MAX_STRING_SIZE);
                int status = sqlite3_db_config(db_handle, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL);
                assert(status == SQLITE_OK);
                status = sqlite3_db_config(db_handle, SQLITE_DBCONFIG_DEFENSIVE, 1, NULL);
                assert(status == SQLITE_OK);

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                Database* db = new Database(db_handle);
                db->Wrap(info.This());
                SetFrozen(isolate, ctx, info.This(), CS::memory, in_memory ? v8::True(isolate) : v8::False(isolate));
                SetFrozen(isolate, ctx, info.This(), CS::readonly, readonly ? v8::True(isolate) : v8::False(isolate));
                SetFrozen(isolate, ctx, info.This(), CS::name, filenameGiven);

                info.GetReturnValue().Set(info.This());
}
#line 155 "./src/objects/database.lzz"
void Database::JS_prepare (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 155 "./src/objects/database.lzz"
                                {
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > source = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                v8::MaybeLocal<v8::Object> maybe_statement = Statement::New( info . GetIsolate ( ) , info.This(), source);
                if (!maybe_statement.IsEmpty()) info.GetReturnValue().Set(maybe_statement.ToLocalChecked());
}
#line 161 "./src/objects/database.lzz"
void Database::JS_exec (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 161 "./src/objects/database.lzz"
                             {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > source = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                v8::String::Utf8Value sql(EXTRACT_STRING( info . GetIsolate ( ) , source));
                db->busy = true;
                int status = sqlite3_exec(db->db_handle, *sql, NULL, NULL, NULL);
                db->busy = false;
                if (status == SQLITE_OK) info.GetReturnValue().Set(info.This());
                else db->ThrowDatabaseError();
}
#line 174 "./src/objects/database.lzz"
void Database::JS_pragma (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 174 "./src/objects/database.lzz"
                               {
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; node :: ObjectWrap :: Unwrap < Database > ( info . This ( ) ) -> pragma_mode = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ;
}
#line 178 "./src/objects/database.lzz"
void Database::JS_checkpoint (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 178 "./src/objects/database.lzz"
                                   {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                sqlite3* db_handle = db->db_handle;

                if (info.Length()) {
                        if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > onlyDatabase = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                        v8::String::Utf8Value only_database(EXTRACT_STRING( info . GetIsolate ( ) , onlyDatabase));
                        if (only_database.length() == 0) {
                                return ThrowTypeError("Invalid database name (empty string)");
                        }
                        if (sqlite3_wal_checkpoint_v2(db_handle, *only_database, SQLITE_CHECKPOINT_RESTART, NULL, NULL) != SQLITE_OK) {
                                return db->ThrowDatabaseError();
                        }
                        return info.GetReturnValue().Set(info.This());
                }

                sqlite3_stmt* stmt;
                if (sqlite3_prepare_v2(db_handle, "PRAGMA database_list", -1, &stmt, NULL) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                std::vector<std::string> database_names;
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                        database_names.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)), sqlite3_column_bytes(stmt, 1));
                }
                if (sqlite3_finalize(stmt) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }

                bool threw_error = false;
                for (std::string const &name : database_names) {
                        if (sqlite3_wal_checkpoint_v2(db_handle, name.c_str(), SQLITE_CHECKPOINT_RESTART, NULL, NULL) != SQLITE_OK) {
                                if (!threw_error) {
                                        db->ThrowDatabaseError();
                                        threw_error = true;
                                }
                        }
                }
                if (!threw_error) info.GetReturnValue().Set(info.This());
}
#line 220 "./src/objects/database.lzz"
void Database::JS_backup (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 220 "./src/objects/database.lzz"
                               {
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > attachedName = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > destFile = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                v8::MaybeLocal<v8::Object> maybe_backup = Backup::New( info . GetIsolate ( ) , info.This(), attachedName, destFile);
                if (!maybe_backup.IsEmpty()) info.GetReturnValue().Set(maybe_backup.ToLocalChecked());
}
#line 227 "./src/objects/database.lzz"
void Database::JS_function (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 227 "./src/objects/database.lzz"
                                 {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsFunction ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a function" ) ; v8 :: Local < v8 :: Function > fn = v8 :: Local < v8 :: Function > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > nameString = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                if ( info . Length ( ) <= ( 2 ) || ! info [ 2 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "third" " argument to be " "a 32-bit signed integer" ) ; int argc = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 2 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 3 ) || ! info [ 3 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "fourth" " argument to be " "a 32-bit signed integer" ) ; int safe_ints = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 3 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 4 ) || ! info [ 4 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fifth" " argument to be " "a boolean" ) ; bool deterministic = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 4 ] ) -> Value ( ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                v8::String::Utf8Value name(EXTRACT_STRING(isolate, nameString));
                int mask = deterministic ? SQLITE_UTF8 | SQLITE_DETERMINISTIC : SQLITE_UTF8;
                safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(db->safe_ints);

                if (sqlite3_create_function_v2(db->db_handle, *name, argc, mask, new CustomFunction(isolate, db, fn, *name, safe_ints), CustomFunction::xFunc, NULL, NULL, CustomFunction::xDestroy) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                info.GetReturnValue().Set(info.This());
}
#line 248 "./src/objects/database.lzz"
void Database::JS_aggregate (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 248 "./src/objects/database.lzz"
                                  {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) ) return ThrowTypeError ( "Expected a " "first" " argument" ) ; v8 :: Local < v8 :: Value > start = info [ 0 ] ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsFunction ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a function" ) ; v8 :: Local < v8 :: Function > step = v8 :: Local < v8 :: Function > :: Cast ( info [ 1 ] ) ;
                if ( info . Length ( ) <= ( 2 ) ) return ThrowTypeError ( "Expected a " "third" " argument" ) ; v8 :: Local < v8 :: Value > inverse = info [ 2 ] ;
                if ( info . Length ( ) <= ( 3 ) ) return ThrowTypeError ( "Expected a " "fourth" " argument" ) ; v8 :: Local < v8 :: Value > result = info [ 3 ] ;
                if ( info . Length ( ) <= ( 4 ) || ! info [ 4 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "fifth" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > nameString = v8 :: Local < v8 :: String > :: Cast ( info [ 4 ] ) ;
                if ( info . Length ( ) <= ( 5 ) || ! info [ 5 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "sixth" " argument to be " "a 32-bit signed integer" ) ; int argc = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 5 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 6 ) || ! info [ 6 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "seventh" " argument to be " "a 32-bit signed integer" ) ; int safe_ints = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 6 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 7 ) || ! info [ 7 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "eighth" " argument to be " "a boolean" ) ; bool deterministic = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 7 ] ) -> Value ( ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                v8::String::Utf8Value name(EXTRACT_STRING(isolate, nameString));
                auto xInverse = inverse->IsFunction() ? CustomAggregate::xInverse : NULL;
                auto xValue = xInverse ? CustomAggregate::xValue : NULL;
                int mask = deterministic ? SQLITE_UTF8 | SQLITE_DETERMINISTIC : SQLITE_UTF8;
                safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(db->safe_ints);

                if (sqlite3_create_window_function(db->db_handle, *name, argc, mask, new CustomAggregate(isolate, db, start, step, inverse, result, *name, safe_ints), CustomAggregate::xStep, CustomAggregate::xFinal, xValue, xInverse, CustomAggregate::xDestroy) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                info.GetReturnValue().Set(info.This());
}
#line 274 "./src/objects/database.lzz"
void Database::JS_loadExtension (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 274 "./src/objects/database.lzz"
                                      {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > filenameString = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                v8::String::Utf8Value filename(EXTRACT_STRING( info . GetIsolate ( ) , filenameString));
                char* error;
                int status = sqlite3_load_extension(db->db_handle, *filename, NULL, &error);
                if (status == SQLITE_OK) info.GetReturnValue().Set(info.This());
                else ThrowSqliteError(error, status);
                sqlite3_free(error);
}
#line 287 "./src/objects/database.lzz"
void Database::JS_close (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 287 "./src/objects/database.lzz"
                              {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if (db->open) {
                        if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                        dbs.erase(db);
                        db->CloseHandles();
                }
                info.GetReturnValue().Set(info.This());
}
#line 297 "./src/objects/database.lzz"
void Database::JS_defaultSafeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 297 "./src/objects/database.lzz"
                                            {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) db->safe_ints = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; db -> safe_ints = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                info.GetReturnValue().Set(info.This());
}
#line 305 "./src/objects/database.lzz"
void Database::JS_open (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info)
#line 305 "./src/objects/database.lzz"
                             {
                info.GetReturnValue().Set( node :: ObjectWrap :: Unwrap <Database>(info.This())->open);
}
#line 309 "./src/objects/database.lzz"
void Database::JS_inTransaction (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info)
#line 309 "./src/objects/database.lzz"
                                      {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                info.GetReturnValue().Set(db->open && !static_cast<bool>(sqlite3_get_autocommit(db->db_handle)));
}
#line 314 "./src/objects/database.lzz"
void Database::CloseHandles ()
#line 314 "./src/objects/database.lzz"
                            {
                if (open) {
                        open = false;
                        for (Statement* stmt : stmts) stmt->CloseHandles();
                        for (Backup* backup : backups) backup->CloseHandles();
                        stmts.clear();
                        backups.clear();
                        int status = sqlite3_close(db_handle);
                        assert(status == SQLITE_OK); ((void)status);
                }
}
#line 326 "./src/objects/database.lzz"
void Database::AtExit (void * _)
#line 326 "./src/objects/database.lzz"
                                    {
                for (Database* db : dbs) db->CloseHandles();
                dbs.clear();
}
#line 331 "./src/objects/database.lzz"
std::set <Database*, Database::CompareDatabase> Database::dbs;
#line 332 "./src/objects/database.lzz"
v8::Persistent <v8::Function> Database::SqliteError;
#line 333 "./src/objects/database.lzz"
int const Database::MAX_BUFFER_SIZE;
#line 334 "./src/objects/database.lzz"
int const Database::MAX_STRING_SIZE;
#line 6 "./src/objects/statement.lzz"
v8::MaybeLocal <v8::Object> Statement::New (v8::Isolate * isolate, v8::Local <v8::Object> database, v8::Local <v8::String> source)
#line 6 "./src/objects/statement.lzz"
                                                                                                                                  {
                v8::Local<v8::Function> c = v8::Local<v8::Function>::New(isolate, constructor);
                v8::Local<v8::Value> args[2] = { database, source };
                constructing_privileges = true;
                v8::MaybeLocal<v8::Object> maybe_statement = c->NewInstance( isolate -> GetCurrentContext ( ) , 2, args);
                constructing_privileges = false;
                return maybe_statement;
}
#line 21 "./src/objects/statement.lzz"
BindMap * Statement::GetBindMap (v8::Isolate * isolate)
#line 21 "./src/objects/statement.lzz"
                                                  {
                if (has_bind_map) return &extras->bind_map;
                BindMap* bind_map = &extras->bind_map;
                int param_count = sqlite3_bind_parameter_count(handle);
                for (int i=1; i<=param_count; ++i) {
                        const char* name = sqlite3_bind_parameter_name(handle, i);
                        if (name != NULL) bind_map->Add(isolate, name + 1, i);
                }
                has_bind_map = true;
                return bind_map;
}
#line 34 "./src/objects/statement.lzz"
void Statement::CloseHandles ()
#line 34 "./src/objects/statement.lzz"
                            {
                if (alive) {
                        alive = false;
                        sqlite3_finalize(handle);
                }
}
#line 41 "./src/objects/statement.lzz"
Statement::~ Statement ()
#line 41 "./src/objects/statement.lzz"
                     {
                if (alive) db->RemoveStatement(this);
                CloseHandles();
                delete extras;
}
#line 51 "./src/objects/statement.lzz"
Statement::Extras::Extras (sqlite3_uint64 _id)
#line 51 "./src/objects/statement.lzz"
  : bind_map (0), id (_id)
#line 51 "./src/objects/statement.lzz"
                                                                           {}
#line 56 "./src/objects/statement.lzz"
Statement::Statement (Database * _db, sqlite3_stmt * _handle, bool _returns_data)
#line 56 "./src/objects/statement.lzz"
  : node::ObjectWrap (), db (_db), handle (_handle), extras (new Extras(next_id++)), alive (true), bound (false), has_bind_map (false), safe_ints (_db->GetState()->safe_ints), pluck (false), expand (false), raw (false), returns_data (_returns_data)
#line 67 "./src/objects/statement.lzz"
                                            {
                assert(db != NULL);
                assert(handle != NULL);
                assert(db->GetState()->open);
                assert(!db->GetState()->busy);
                db->AddStatement(this);
}
#line 75 "./src/objects/statement.lzz"
void Statement::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 75 "./src/objects/statement.lzz"
                       {
                v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, JS_new);
                t->InstanceTemplate()->SetInternalFieldCount(1);
                t->SetClassName(StringFromUtf8(isolate, "Statement", -1));

                NODE_SET_PROTOTYPE_METHOD(t, "run", JS_run);
                NODE_SET_PROTOTYPE_METHOD(t, "get", JS_get);
                NODE_SET_PROTOTYPE_METHOD(t, "all", JS_all);
                NODE_SET_PROTOTYPE_METHOD(t, "iterate", JS_iterate);
                NODE_SET_PROTOTYPE_METHOD(t, "bind", JS_bind);
                NODE_SET_PROTOTYPE_METHOD(t, "pluck", JS_pluck);
                NODE_SET_PROTOTYPE_METHOD(t, "expand", JS_expand);
                NODE_SET_PROTOTYPE_METHOD(t, "raw", JS_raw);
                NODE_SET_PROTOTYPE_METHOD(t, "safeIntegers", JS_safeIntegers);
                NODE_SET_PROTOTYPE_METHOD(t, "columns", JS_columns);

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                exports->Set(ctx, StringFromUtf8(isolate, "Statement", -1), t->GetFunction(ctx).ToLocalChecked()).FromJust();
                constructor.Reset(isolate, t->GetFunction( isolate -> GetCurrentContext ( ) ).ToLocalChecked());
                next_id = 0;
                constructing_privileges = false;
}
#line 98 "./src/objects/statement.lzz"
void Statement::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 98 "./src/objects/statement.lzz"
                            {
                if (!constructing_privileges) {
                        return ThrowTypeError("Statements can only be constructed by the db.prepare() method");
                }
                assert(info.IsConstructCall());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsObject ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "an object" ) ; v8 :: Local < v8 :: Object > database = v8 :: Local < v8 :: Object > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > source = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                Database* db = node :: ObjectWrap :: Unwrap <Database>(database);
                if ( ! db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                v8::String::Value sql(EXTRACT_STRING(isolate, source));
                const uint16_t* tail;
                sqlite3_stmt* handle;

                if (sqlite3_prepare16_v3(db->GetHandle(), *sql, sql.length() * sizeof(uint16_t) + 1, SQLITE_PREPARE_PERSISTENT, &handle, reinterpret_cast<const void**>(&tail)) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                if (handle == NULL) {
                        return ThrowRangeError("The supplied SQL string contains no statements");
                }
                for (uint16_t const * const end = *sql + sql.length(); tail < end; ++tail) {
                        const uint16_t c = *tail;
                        if (c != '\n' && c != '\t' && c != ' ' && c != '\r') {
                                sqlite3_finalize(handle);
                                return ThrowRangeError("The supplied SQL string contains more than one statement");
                        }
                }
                bool returns_data = (sqlite3_stmt_readonly(handle) && sqlite3_column_count(handle) >= 1) || db->GetState()->pragma_mode;

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                Statement* stmt = new Statement(db, handle, returns_data);
                stmt->Wrap(info.This());
                SetFrozen(isolate, ctx, info.This(), CS::reader, v8::Boolean::New(isolate, returns_data));
                SetFrozen(isolate, ctx, info.This(), CS::source, source);
                SetFrozen(isolate, ctx, info.This(), CS::database, database);

                info.GetReturnValue().Set(info.This());
}
#line 139 "./src/objects/statement.lzz"
void Statement::JS_run (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 139 "./src/objects/statement.lzz"
                            {
                Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( stmt -> returns_data ) return ThrowTypeError ( "This statement returns data. Use get(), all(), or iterate() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; if ( ! db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( ! bound ) { Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } else if ( info . Length ( ) > 0 ) return ThrowTypeError ( "This statement already has bound parameters" ) ; db -> GetState ( ) -> busy = true ;
                sqlite3* db_handle = db->GetHandle();
                int total_changes_before = sqlite3_total_changes(db_handle);

                sqlite3_step(handle);
                if (sqlite3_reset(handle) == SQLITE_OK) {
                        int changes = sqlite3_total_changes(db_handle) == total_changes_before ? 0 : sqlite3_changes(db_handle);
                        sqlite3_int64 id = sqlite3_last_insert_rowid(db_handle);
                        v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                        v8::Local<v8::Object> result = v8::Object::New(isolate);
                        result->Set(ctx, CS::Get(isolate, CS::changes), v8::Int32::New(isolate, changes)).FromJust();
                        result->Set(ctx, CS::Get(isolate, CS::lastInsertRowid), Integer::New(isolate, id, stmt->safe_ints)).FromJust();
                        db -> GetState ( ) -> busy = false ; info . GetReturnValue ( ) . Set ( result ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                }
                db -> GetState ( ) -> busy = false ; db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 157 "./src/objects/statement.lzz"
void Statement::JS_get (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 157 "./src/objects/statement.lzz"
                            {
                Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( ! stmt -> returns_data ) return ThrowTypeError ( "This statement does not return data. Use run() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; if ( ! db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( ! bound ) { Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } else if ( info . Length ( ) > 0 ) return ThrowTypeError ( "This statement already has bound parameters" ) ; db -> GetState ( ) -> busy = true ;
                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                int status = sqlite3_step(handle);
                if (status == SQLITE_ROW) {
                        v8::Local<v8::Value> result =
                                stmt->pluck ? Data::GetValueJS(isolate, handle, 0, stmt->safe_ints) :
                                stmt->expand ? Data::GetExpandedRowJS(isolate, isolate -> GetCurrentContext ( ) , handle, stmt->safe_ints) :
                                stmt->raw ? Data::GetRawRowJS(isolate, isolate -> GetCurrentContext ( ) , handle, stmt->safe_ints)
                                : Data::GetRowJS(isolate, isolate -> GetCurrentContext ( ) , handle, stmt->safe_ints);
                        sqlite3_reset(handle);
                        db -> GetState ( ) -> busy = false ; info . GetReturnValue ( ) . Set ( result ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                } else if (status == SQLITE_DONE) {
                        sqlite3_reset(handle);
                        db -> GetState ( ) -> busy = false ; info . GetReturnValue ( ) . Set ( v8 :: Undefined ( isolate ) ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                }
                sqlite3_reset(handle);
                db -> GetState ( ) -> busy = false ; db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 177 "./src/objects/statement.lzz"
void Statement::JS_all (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 177 "./src/objects/statement.lzz"
                            {
                Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( ! stmt -> returns_data ) return ThrowTypeError ( "This statement does not return data. Use run() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; if ( ! db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( ! bound ) { Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } else if ( info . Length ( ) > 0 ) return ThrowTypeError ( "This statement already has bound parameters" ) ; db -> GetState ( ) -> busy = true ;
                v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                v8::Local<v8::Array> result = v8::Array::New(isolate, 0);
                uint32_t row_count = 0;
                const bool safe_ints = stmt->safe_ints;
                const bool pluck = stmt->pluck;
                const bool expand = stmt->expand;
                const bool raw = stmt->raw;
                bool js_error = false;

                while (sqlite3_step(handle) == SQLITE_ROW) {
                        if (row_count == 0xffffffff) { ThrowRangeError("Array overflow (too many rows returned)"); js_error = true; break; }
                        result->Set(ctx, row_count++,
                                pluck ? Data::GetValueJS(isolate, handle, 0, safe_ints) :
                                expand ? Data::GetExpandedRowJS(isolate, ctx, handle, safe_ints) :
                                raw ? Data::GetRawRowJS(isolate, ctx, handle, safe_ints)
                                : Data::GetRowJS(isolate, ctx, handle, safe_ints)
                        ).FromJust();
                }

                if (sqlite3_reset(handle) == SQLITE_OK && !js_error) {
                        db -> GetState ( ) -> busy = false ; info . GetReturnValue ( ) . Set ( result ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                }
                if (js_error) db->GetState()->was_js_error = true;
                db -> GetState ( ) -> busy = false ; db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 205 "./src/objects/statement.lzz"
void Statement::JS_iterate (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 205 "./src/objects/statement.lzz"
                                {
                v8::MaybeLocal<v8::Object> maybe_iter = StatementIterator::New( info . GetIsolate ( ) , info);
                if (!maybe_iter.IsEmpty()) info.GetReturnValue().Set(maybe_iter.ToLocalChecked());
}
#line 210 "./src/objects/statement.lzz"
void Statement::JS_bind (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 210 "./src/objects/statement.lzz"
                             {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (stmt->bound) return ThrowTypeError("The bind() method can only be invoked once per statement object");
                if ( ! stmt -> db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                Binder binder ( stmt -> handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( stmt -> handle ) ; return ; } ( ( void ) 0 ) ;
                stmt->bound = true;
                info.GetReturnValue().Set(info.This());
}
#line 220 "./src/objects/statement.lzz"
void Statement::JS_pluck (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 220 "./src/objects/statement.lzz"
                              {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (!stmt->returns_data) return ThrowTypeError("The pluck() method is only for statements that return data");
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) stmt->pluck = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; stmt -> pluck = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                if (stmt->pluck) stmt->expand = stmt->raw = false;
                info.GetReturnValue().Set(info.This());
}
#line 230 "./src/objects/statement.lzz"
void Statement::JS_expand (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 230 "./src/objects/statement.lzz"
                               {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (!stmt->returns_data) return ThrowTypeError("The expand() method is only for statements that return data");
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) stmt->expand = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; stmt -> expand = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                if (stmt->expand) stmt->pluck = stmt->raw = false;
                info.GetReturnValue().Set(info.This());
}
#line 240 "./src/objects/statement.lzz"
void Statement::JS_raw (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 240 "./src/objects/statement.lzz"
                            {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (!stmt->returns_data) return ThrowTypeError("The raw() method is only for statements that return data");
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) stmt->raw = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; stmt -> raw = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                if (stmt->raw) stmt->pluck = stmt->expand = false;
                info.GetReturnValue().Set(info.This());
}
#line 250 "./src/objects/statement.lzz"
void Statement::JS_safeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 250 "./src/objects/statement.lzz"
                                     {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) stmt->safe_ints = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; stmt -> safe_ints = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                info.GetReturnValue().Set(info.This());
}
#line 258 "./src/objects/statement.lzz"
void Statement::JS_columns (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 258 "./src/objects/statement.lzz"
                                {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (!stmt->returns_data) return ThrowTypeError("The columns() method is only for statements that return data");
                if ( ! stmt -> db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;

                int column_count = sqlite3_column_count(stmt->handle);
                v8::Local<v8::Array> columns = v8::Array::New(isolate);

                v8::Local<v8::String> name = CS::Get(isolate, CS::name);
                v8::Local<v8::String> columnName = CS::Get(isolate, CS::column);
                v8::Local<v8::String> tableName = CS::Get(isolate, CS::table);
                v8::Local<v8::String> databaseName = CS::Get(isolate, CS::database);
                v8::Local<v8::String> typeName = CS::Get(isolate, CS::type);

                for (int i=0; i<column_count; ++i) {
                        v8::Local<v8::Object> column = v8::Object::New(isolate);

                        column->Set(ctx, name,
                                InternalizedFromUtf8OrNull(isolate, sqlite3_column_name(stmt->handle, i), -1)
                        ).FromJust();
                        column->Set(ctx, columnName,
                                InternalizedFromUtf8OrNull(isolate, sqlite3_column_origin_name(stmt->handle, i), -1)
                        ).FromJust();
                        column->Set(ctx, tableName,
                                InternalizedFromUtf8OrNull(isolate, sqlite3_column_table_name(stmt->handle, i), -1)
                        ).FromJust();
                        column->Set(ctx, databaseName,
                                InternalizedFromUtf8OrNull(isolate, sqlite3_column_database_name(stmt->handle, i), -1)
                        ).FromJust();
                        column->Set(ctx, typeName,
                                InternalizedFromUtf8OrNull(isolate, sqlite3_column_decltype(stmt->handle, i), -1)
                        ).FromJust();

                        columns->Set(ctx, i, column).FromJust();
                }

                info.GetReturnValue().Set(columns);
}
#line 299 "./src/objects/statement.lzz"
v8::Persistent <v8::Function> Statement::constructor;
#line 300 "./src/objects/statement.lzz"
sqlite3_uint64 Statement::next_id;
#line 301 "./src/objects/statement.lzz"
bool Statement::constructing_privileges;
#line 5 "./src/objects/statement-iterator.lzz"
v8::MaybeLocal <v8::Object> StatementIterator::New (v8::Isolate * isolate, v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 5 "./src/objects/statement-iterator.lzz"
                                                                                         {
                v8::Local<v8::Function> c = v8::Local<v8::Function>::New(isolate, constructor);
                caller_info = &info;
                v8::MaybeLocal<v8::Object> maybe_iter = c->NewInstance( isolate -> GetCurrentContext ( ) , 0, NULL);
                caller_info = NULL;
                return maybe_iter;
}
#line 16 "./src/objects/statement-iterator.lzz"
StatementIterator::~ StatementIterator ()
#line 16 "./src/objects/statement-iterator.lzz"
                             {}
#line 20 "./src/objects/statement-iterator.lzz"
StatementIterator::StatementIterator (Statement * _stmt, bool _bound)
#line 20 "./src/objects/statement-iterator.lzz"
  : node::ObjectWrap (), stmt (_stmt), handle (_stmt->handle), safe_ints (_stmt->safe_ints), pluck (_stmt->pluck), expand (_stmt->expand), raw (_stmt->raw), bound (_bound), alive (true)
#line 28 "./src/objects/statement-iterator.lzz"
                            {
                assert(stmt != NULL);
                assert(handle != NULL);
                assert(stmt->bound == bound);
                assert(stmt->alive == true);
}
#line 35 "./src/objects/statement-iterator.lzz"
void StatementIterator::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 35 "./src/objects/statement-iterator.lzz"
                       {
                v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, JS_new);
                t->InstanceTemplate()->SetInternalFieldCount(1);
                t->SetClassName(StringFromUtf8(isolate, "StatementIterator", -1));

                NODE_SET_PROTOTYPE_METHOD(t, "next", JS_next);
                NODE_SET_PROTOTYPE_METHOD(t, "return", JS_return);
                NODE_SET_PROTOTYPE_SYMBOL_METHOD(t, v8::Symbol::GetIterator(isolate), JS_symbolIterator);

                constructor.Reset(isolate, t->GetFunction( isolate -> GetCurrentContext ( ) ).ToLocalChecked());
                caller_info = NULL;
}
#line 48 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 48 "./src/objects/statement-iterator.lzz"
                            {
                if (caller_info == NULL) return ThrowTypeError("Disabled constructor");
                assert(info.IsConstructCall());

                StatementIterator* iter;
                {
                        const v8 :: FunctionCallbackInfo < v8 :: Value > & info = *caller_info;
                        Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( ! stmt -> returns_data ) return ThrowTypeError ( "This statement does not return data. Use run() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; if ( ! db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( ! bound ) { Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } else if ( info . Length ( ) > 0 ) return ThrowTypeError ( "This statement already has bound parameters" ) ; db -> GetState ( ) -> busy = true ;
                        iter = new StatementIterator(stmt, bound);
                }
                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                iter->Wrap(info.This());
                SetFrozen(isolate, isolate -> GetCurrentContext ( ) , info.This(), CS::statement, caller_info->This());

                info.GetReturnValue().Set(info.This());
}
#line 65 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_next (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 65 "./src/objects/statement-iterator.lzz"
                             {
                StatementIterator* iter = node :: ObjectWrap :: Unwrap <StatementIterator>(info.This());
                if (iter->alive) iter->Next(info);
                else info.GetReturnValue().Set(DoneRecord( info . GetIsolate ( ) ));
}
#line 71 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_return (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 71 "./src/objects/statement-iterator.lzz"
                               {
                StatementIterator* iter = node :: ObjectWrap :: Unwrap <StatementIterator>(info.This());
                if (iter->alive) iter->Return(info);
                else info.GetReturnValue().Set(DoneRecord( info . GetIsolate ( ) ));
}
#line 77 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_symbolIterator (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 77 "./src/objects/statement-iterator.lzz"
                                       {
                info.GetReturnValue().Set(info.This());
}
#line 81 "./src/objects/statement-iterator.lzz"
void StatementIterator::Next (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 81 "./src/objects/statement-iterator.lzz"
                                       {
                assert(alive == true);
                int status = sqlite3_step(handle);
                if (status == SQLITE_ROW) {
                        v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                        info.GetReturnValue().Set(NewRecord(isolate, ctx,
                                pluck ? Data::GetValueJS(isolate, handle, 0, safe_ints) :
                                expand ? Data::GetExpandedRowJS(isolate, ctx, handle, safe_ints) :
                                raw ? Data::GetRawRowJS(isolate, ctx, handle, safe_ints)
                                : Data::GetRowJS(isolate, ctx, handle, safe_ints)
                        ));
                } else {
                        if (status == SQLITE_DONE) Return(info);
                        else Throw();
                }
}
#line 98 "./src/objects/statement-iterator.lzz"
void StatementIterator::Return (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 98 "./src/objects/statement-iterator.lzz"
                                         {
                Cleanup();
                Database* db = stmt->db;
                db -> GetState ( ) -> busy = false ; info . GetReturnValue ( ) . Set ( DoneRecord ( info . GetIsolate ( ) ) ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 104 "./src/objects/statement-iterator.lzz"
void StatementIterator::Throw ()
#line 104 "./src/objects/statement-iterator.lzz"
                     {
                Cleanup();
                Database* db = stmt->db;
                db -> GetState ( ) -> busy = false ; db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 110 "./src/objects/statement-iterator.lzz"
void StatementIterator::Cleanup ()
#line 110 "./src/objects/statement-iterator.lzz"
                       {
                assert(alive == true);
                alive = false;
                sqlite3_reset(handle);
}
#line 116 "./src/objects/statement-iterator.lzz"
v8::Local <v8::Object> StatementIterator::NewRecord (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Value> value, bool done)
#line 116 "./src/objects/statement-iterator.lzz"
                                                                                                                                                {
                v8::Local<v8::Object> record = v8::Object::New(isolate);
                record->Set(ctx, CS::Get(isolate, CS::value), value).FromJust();
                record->Set(ctx, CS::Get(isolate, CS::done), done ? v8::True(isolate) : v8::False(isolate)).FromJust();
                return record;
}
#line 123 "./src/objects/statement-iterator.lzz"
v8::Local <v8::Object> StatementIterator::DoneRecord (v8::Isolate * isolate)
#line 123 "./src/objects/statement-iterator.lzz"
                                                                      {
                return NewRecord(isolate, isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), true);
}
#line 127 "./src/objects/statement-iterator.lzz"
v8::Persistent <v8::Function> StatementIterator::constructor;
#line 128 "./src/objects/statement-iterator.lzz"
v8::FunctionCallbackInfo <v8 :: Value> const * StatementIterator::caller_info;
#line 5 "./src/objects/backup.lzz"
v8::MaybeLocal <v8::Object> Backup::New (v8::Isolate * isolate, v8::Local <v8::Object> database, v8::Local <v8::String> attachedName, v8::Local <v8::String> destFile)
#line 5 "./src/objects/backup.lzz"
                                                                                                                                                                        {
                v8::Local<v8::Function> c = v8::Local<v8::Function>::New(isolate, constructor);
                v8::Local<v8::Value> args[3] = { database, attachedName, destFile };
                constructing_privileges = true;
                v8::MaybeLocal<v8::Object> maybe_backup = c->NewInstance( isolate -> GetCurrentContext ( ) , 3, args);
                constructing_privileges = false;
                return maybe_backup;
}
#line 20 "./src/objects/backup.lzz"
void Backup::CloseHandles ()
#line 20 "./src/objects/backup.lzz"
                            {
                if (alive) {
                        alive = false;
                        sqlite3_backup_finish(backup_handle);
                        int status = sqlite3_close(dest_handle);
                        assert(status == SQLITE_OK); ((void)status);
                }
}
#line 29 "./src/objects/backup.lzz"
Backup::~ Backup ()
#line 29 "./src/objects/backup.lzz"
                  {
                if (alive) db->RemoveBackup(this);
                CloseHandles();
}
#line 36 "./src/objects/backup.lzz"
Backup::Backup (Database * _db, sqlite3 * _dest_handle, sqlite3_backup * _backup_handle)
#line 36 "./src/objects/backup.lzz"
  : node::ObjectWrap (), db (_db), dest_handle (_dest_handle), backup_handle (_backup_handle), id (next_id++), alive (true)
#line 41 "./src/objects/backup.lzz"
                            {
                assert(db != NULL);
                assert(dest_handle != NULL);
                assert(backup_handle != NULL);
                db->AddBackup(this);
}
#line 48 "./src/objects/backup.lzz"
void Backup::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 48 "./src/objects/backup.lzz"
                       {
                v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, JS_new);
                t->InstanceTemplate()->SetInternalFieldCount(1);
                t->SetClassName(StringFromUtf8(isolate, "Backup", -1));

                NODE_SET_PROTOTYPE_METHOD(t, "transfer", JS_transfer);
                NODE_SET_PROTOTYPE_METHOD(t, "close", JS_close);

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                exports->Set(ctx, StringFromUtf8(isolate, "Backup", -1), t->GetFunction(ctx).ToLocalChecked()).FromJust();
                constructor.Reset(isolate, t->GetFunction( isolate -> GetCurrentContext ( ) ).ToLocalChecked());
                next_id = 0;
                constructing_privileges = false;
}
#line 63 "./src/objects/backup.lzz"
void Backup::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 63 "./src/objects/backup.lzz"
                            {
                if (!constructing_privileges) return ThrowTypeError("Disabled constructor");
                assert(info.IsConstructCall());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsObject ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "an object" ) ; v8 :: Local < v8 :: Object > database = v8 :: Local < v8 :: Object > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > attachedName = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                if ( info . Length ( ) <= ( 2 ) || ! info [ 2 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "third" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > destFile = v8 :: Local < v8 :: String > :: Cast ( info [ 2 ] ) ;
                Database* db = node :: ObjectWrap :: Unwrap <Database>(database);
                if ( ! db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                sqlite3* dest_handle;
                v8::String::Utf8Value dest_file(EXTRACT_STRING(isolate, destFile));
                v8::String::Utf8Value attached_name(EXTRACT_STRING(isolate, attachedName));
                int mask = (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

                if (sqlite3_open_v2(*dest_file, &dest_handle, mask, NULL) != SQLITE_OK) {
                        Database::ThrowSqliteError(dest_handle);
                        int status = sqlite3_close(dest_handle);
                        assert(status == SQLITE_OK); ((void)status);
                        return;
                }

                sqlite3_extended_result_codes(dest_handle, 1);
                sqlite3_limit(dest_handle, SQLITE_LIMIT_LENGTH, INT_MAX);
                sqlite3_backup* backup_handle = sqlite3_backup_init(dest_handle, "main", db->GetHandle(), *attached_name);
                if (backup_handle == NULL) {
                        Database::ThrowSqliteError(dest_handle);
                        int status = sqlite3_close(dest_handle);
                        assert(status == SQLITE_OK); ((void)status);
                        return;
                }

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                Backup* backup = new Backup(db, dest_handle, backup_handle);
                backup->Wrap(info.This());
                SetFrozen(isolate, ctx, info.This(), CS::filename, destFile);
                SetFrozen(isolate, ctx, info.This(), CS::database, database);

                info.GetReturnValue().Set(info.This());
}
#line 105 "./src/objects/backup.lzz"
void Backup::JS_transfer (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 105 "./src/objects/backup.lzz"
                                 {
                Backup* backup = node :: ObjectWrap :: Unwrap <Backup>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a 32-bit signed integer" ) ; int pages = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 0 ] ) -> Value ( ) ;
                if ( ! backup -> db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                assert(backup->db->GetState()->busy == false);
                assert(backup->alive == true);

                sqlite3_backup* backup_handle = backup->backup_handle;
                int status = sqlite3_backup_step(backup_handle, pages) & 0xff;

                if (status == SQLITE_OK || status == SQLITE_DONE || status == SQLITE_BUSY) {
                        int total_pages = sqlite3_backup_pagecount(backup_handle);
                        int remaining_pages = sqlite3_backup_remaining(backup_handle);
                        v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                        v8::Local<v8::Object> result = v8::Object::New(isolate);
                        result->Set(ctx, CS::Get(isolate, CS::totalPages), v8::Int32::New(isolate, total_pages)).FromJust();
                        result->Set(ctx, CS::Get(isolate, CS::remainingPages), v8::Int32::New(isolate, remaining_pages)).FromJust();
                        info.GetReturnValue().Set(result);
                } else {
                        Database::ThrowSqliteError(sqlite3_errstr(status), status);
                }
}
#line 128 "./src/objects/backup.lzz"
void Backup::JS_close (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 128 "./src/objects/backup.lzz"
                              {
                Backup* backup = node :: ObjectWrap :: Unwrap <Backup>(info.This());
                assert(backup->db->GetState()->busy == false);
                if (backup->alive) backup->db->RemoveBackup(backup);
                backup->CloseHandles();
                info.GetReturnValue().Set(info.This());
}
#line 136 "./src/objects/backup.lzz"
v8::Persistent <v8::Function> Backup::constructor;
#line 137 "./src/objects/backup.lzz"
sqlite3_uint64 Backup::next_id;
#line 138 "./src/objects/backup.lzz"
bool Backup::constructing_privileges;
#line 4 "./src/util/custom-function.lzz"
CustomFunction::CustomFunction (v8::Isolate * _isolate, Database * _db, v8::Local <v8::Function> _fn, char const * _name, bool _safe_ints)
#line 5 "./src/util/custom-function.lzz"
  : name (COPY(_name)), db (_db), isolate (_isolate), fn (_isolate, _fn), safe_ints (_safe_ints)
#line 5 "./src/util/custom-function.lzz"
                                                                                                          {}
#line 6 "./src/util/custom-function.lzz"
CustomFunction::~ CustomFunction ()
#line 6 "./src/util/custom-function.lzz"
                                  { delete[] name;
}
#line 8 "./src/util/custom-function.lzz"
void CustomFunction::xDestroy (void * self)
#line 8 "./src/util/custom-function.lzz"
                                         {
                delete static_cast<CustomFunction*>(self);
}
#line 12 "./src/util/custom-function.lzz"
void CustomFunction::xFunc (sqlite3_context * invocation, int argc, sqlite3_value * * argv)
#line 12 "./src/util/custom-function.lzz"
                                                                                       {
                CustomFunction * self = static_cast < CustomFunction * > ( sqlite3_user_data ( invocation ) ) ; v8 :: Isolate * isolate = self -> isolate ; v8 :: HandleScope scope ( isolate ) ;

                v8::Local<v8::Value> args_fast[4];
                v8::Local<v8::Value>* args = NULL;
                if (argc != 0) {
                        args = argc <= 4 ? args_fast : ALLOC_ARRAY<v8::Local<v8::Value>>(argc);
                        Data::GetArgumentsJS(isolate, args, argv, argc, self->safe_ints);
                }

                v8::MaybeLocal<v8::Value> maybe_return_value = v8::Local<v8::Function>::New(isolate, self->fn)->Call( isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), argc, args);
                if (args != args_fast) delete[] args;

                if (maybe_return_value.IsEmpty()) self->PropagateJSError(invocation);
                else Data::ResultValueFromJS(isolate, invocation, maybe_return_value.ToLocalChecked(), self);
}
#line 29 "./src/util/custom-function.lzz"
void CustomFunction::ThrowResultValueError (sqlite3_context * invocation)
#line 29 "./src/util/custom-function.lzz"
                                                                {
                ThrowTypeError(CONCAT("User-defined function ", name, "() returned an invalid value").c_str());
                PropagateJSError(invocation);
}
#line 35 "./src/util/custom-function.lzz"
void CustomFunction::PropagateJSError (sqlite3_context * invocation)
#line 35 "./src/util/custom-function.lzz"
                                                                   {
                assert(db->GetState()->was_js_error == false);
                db->GetState()->was_js_error = true;
                sqlite3_result_error(invocation, "", 0);
}
#line 4 "./src/util/custom-aggregate.lzz"
CustomAggregate::CustomAggregate (v8::Isolate * _isolate, Database * _db, v8::Local <v8::Value> _start, v8::Local <v8::Function> _step, v8::Local <v8::Value> _inverse, v8::Local <v8::Value> _result, char const * _name, bool _safe_ints)
#line 5 "./src/util/custom-aggregate.lzz"
  : CustomFunction (_isolate, _db, _step, _name, _safe_ints), invoke_result (_result->IsFunction()), invoke_start (_start->IsFunction()), inverse (_isolate, _inverse->IsFunction() ? v8::Local<v8::Function>::Cast(_inverse) : v8::Local<v8::Function>()), result (_isolate, _result->IsFunction() ? v8::Local<v8::Function>::Cast(_result) : v8::Local<v8::Function>()), start (_isolate, _start)
#line 5 "./src/util/custom-aggregate.lzz"
                                                                                                                                                                                                                                                                                                                                                                                                            {}
#line 7 "./src/util/custom-aggregate.lzz"
void CustomAggregate::xStep (sqlite3_context * invocation, int argc, sqlite3_value * * argv)
#line 7 "./src/util/custom-aggregate.lzz"
                                                                                       {
                xStepBase(invocation, argc, argv, &CustomAggregate::fn);
}
#line 11 "./src/util/custom-aggregate.lzz"
void CustomAggregate::xInverse (sqlite3_context * invocation, int argc, sqlite3_value * * argv)
#line 11 "./src/util/custom-aggregate.lzz"
                                                                                          {
                xStepBase(invocation, argc, argv, &CustomAggregate::inverse);
}
#line 15 "./src/util/custom-aggregate.lzz"
void CustomAggregate::xValue (sqlite3_context * invocation)
#line 15 "./src/util/custom-aggregate.lzz"
                                                        {
                xValueBase(invocation, false);
}
#line 19 "./src/util/custom-aggregate.lzz"
void CustomAggregate::xFinal (sqlite3_context * invocation)
#line 19 "./src/util/custom-aggregate.lzz"
                                                        {
                xValueBase(invocation, true);
}
#line 73 "./src/util/custom-aggregate.lzz"
CustomAggregate::Accumulator * CustomAggregate::GetAccumulator (sqlite3_context * invocation)
#line 73 "./src/util/custom-aggregate.lzz"
                                                                 {
                Accumulator* acc = static_cast<Accumulator*>(sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
                if (!acc->initialized) {
                        assert(acc->value.IsEmpty());
                        acc->initialized = true;
                        if (invoke_start) {
                                v8::MaybeLocal<v8::Value> maybe_seed = v8::Local<v8::Function>::Cast(v8::Local<v8::Value>::New(isolate, start))->Call( isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), 0, NULL);
                                if (maybe_seed.IsEmpty()) PropagateJSError(invocation);
                                else acc->value.Reset(isolate, maybe_seed.ToLocalChecked());
                        } else {
                                assert(!start.IsEmpty());
                                acc->value.Reset(isolate, start);
                        }
                }
                return acc;
}
#line 90 "./src/util/custom-aggregate.lzz"
void CustomAggregate::DestroyAccumulator (sqlite3_context * invocation)
#line 90 "./src/util/custom-aggregate.lzz"
                                                                    {
                Accumulator* acc = static_cast<Accumulator*>(sqlite3_aggregate_context(invocation, sizeof(Accumulator)));
                assert(acc->initialized);
                acc->value.Reset();
}
#line 96 "./src/util/custom-aggregate.lzz"
void CustomAggregate::PropagateJSError (sqlite3_context * invocation)
#line 96 "./src/util/custom-aggregate.lzz"
                                                           {
                DestroyAccumulator(invocation);
                CustomFunction::PropagateJSError(invocation);
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 56 "./src/util/data.lzz"
  v8::Local <v8::Value> GetValueJS (v8::Isolate * isolate, sqlite3_stmt * handle, int column, bool safe_ints)
#line 56 "./src/util/data.lzz"
                                                                                                                {
                switch ( sqlite3_column_type ( handle , column ) ) { case SQLITE_INTEGER : return Integer :: New ( isolate , sqlite3_column_int64 ( handle , column ) , safe_ints ) ; case SQLITE_FLOAT : return v8 :: Number :: New ( isolate , sqlite3_column_double ( handle , column ) ) ; case SQLITE_TEXT : return StringFromUtf8 ( isolate , reinterpret_cast < const char * > ( sqlite3_column_text ( handle , column ) ) , sqlite3_column_bytes ( handle , column ) ) ; case SQLITE_BLOB : return node :: Buffer :: Copy ( isolate , static_cast < const char * > ( sqlite3_column_blob ( handle , column ) ) , sqlite3_column_bytes ( handle , column ) ) . ToLocalChecked ( ) ; default : assert ( sqlite3_column_type ( handle , column ) == SQLITE_NULL ) ; return v8 :: Null ( isolate ) ; } assert ( false ) ; ;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 60 "./src/util/data.lzz"
  v8::Local <v8::Value> GetValueJS (v8::Isolate * isolate, sqlite3_value * value, bool safe_ints)
#line 60 "./src/util/data.lzz"
                                                                                                    {
                switch ( sqlite3_value_type ( value ) ) { case SQLITE_INTEGER : return Integer :: New ( isolate , sqlite3_value_int64 ( value ) , safe_ints ) ; case SQLITE_FLOAT : return v8 :: Number :: New ( isolate , sqlite3_value_double ( value ) ) ; case SQLITE_TEXT : return StringFromUtf8 ( isolate , reinterpret_cast < const char * > ( sqlite3_value_text ( value ) ) , sqlite3_value_bytes ( value ) ) ; case SQLITE_BLOB : return node :: Buffer :: Copy ( isolate , static_cast < const char * > ( sqlite3_value_blob ( value ) ) , sqlite3_value_bytes ( value ) ) . ToLocalChecked ( ) ; default : assert ( sqlite3_value_type ( value ) == SQLITE_NULL ) ; return v8 :: Null ( isolate ) ; } assert ( false ) ; ;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 64 "./src/util/data.lzz"
  v8::Local <v8::Value> GetRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints)
#line 64 "./src/util/data.lzz"
                                                                                                                              {
                v8::Local<v8::Object> row = v8::Object::New(isolate);
                int column_count = sqlite3_column_count(handle);
                for (int i=0; i<column_count; ++i) {
                        row->Set(ctx,
                                InternalizedFromUtf8(isolate, sqlite3_column_name(handle, i), -1),
                                Data::GetValueJS(isolate, handle, i, safe_ints)).FromJust();
                }
                return row;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 75 "./src/util/data.lzz"
  v8::Local <v8::Value> GetExpandedRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints)
#line 75 "./src/util/data.lzz"
                                                                                                                                      {
                v8::Local<v8::Object> row = v8::Object::New(isolate);
                int column_count = sqlite3_column_count(handle);
                for (int i=0; i<column_count; ++i) {
                        const char* table_raw = sqlite3_column_table_name(handle, i);
                        v8::Local<v8::String> table = InternalizedFromUtf8(isolate, table_raw == NULL ? "$" : table_raw, -1);
                        v8::Local<v8::String> column = InternalizedFromUtf8(isolate, sqlite3_column_name(handle, i), -1);
                        v8::Local<v8::Value> value = Data::GetValueJS(isolate, handle, i, safe_ints);
                        if (row->HasOwnProperty(ctx, table).FromJust()) {
                                v8::Local<v8::Object>::Cast(row->Get(ctx, table).ToLocalChecked())->Set(ctx, column, value).FromJust();
                        } else {
                                v8::Local<v8::Object> nested = v8::Object::New(isolate);
                                row->Set(ctx, table, nested).FromJust();
                                nested->Set(ctx, column, value).FromJust();
                        }
                }
                return row;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 94 "./src/util/data.lzz"
  v8::Local <v8::Value> GetRawRowJS (v8::Isolate * isolate, v8::Local <v8::Context> ctx, sqlite3_stmt * handle, bool safe_ints)
#line 94 "./src/util/data.lzz"
                                                                                                                                 {
                v8::Local<v8::Array> row = v8::Array::New(isolate);
                int column_count = sqlite3_column_count(handle);
                for (int i=0; i<column_count; ++i) {
                        row->Set(ctx, i, Data::GetValueJS(isolate, handle, i, safe_ints)).FromJust();
                }
                return row;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 103 "./src/util/data.lzz"
  void GetArgumentsJS (v8::Isolate * isolate, v8::Local <v8::Value> * out, sqlite3_value * * values, int argument_count, bool safe_ints)
#line 103 "./src/util/data.lzz"
                                                                                                                                         {
                assert(argument_count > 0);
                for (int i=0; i<argument_count; ++i) {
                        out[i] = Data::GetValueJS(isolate, values[i], safe_ints);
                }
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 110 "./src/util/data.lzz"
  int BindValueFromJS (v8::Isolate * isolate, sqlite3_stmt * handle, int index, v8::Local <v8::Value> value)
#line 110 "./src/util/data.lzz"
                                                                                                               {
                if ( value -> IsNumber ( ) ) { return sqlite3_bind_double ( handle , index , v8 :: Local < v8 :: Number > :: Cast ( value ) -> Value ( ) ) ; } else if ( value -> IsString ( ) ) { v8 :: String :: Utf8Value utf8 ( EXTRACT_STRING ( isolate , v8 :: Local < v8 :: String > :: Cast ( value ) ) ) ; return sqlite3_bind_text ( handle , index , * utf8 , utf8 . length ( ) , SQLITE_TRANSIENT ) ; } else if ( value -> IsNull ( ) || value -> IsUndefined ( ) ) { return sqlite3_bind_null ( handle , index ) ; } else if ( node :: Buffer :: HasInstance ( value ) ) { return sqlite3_bind_blob ( handle , index , node :: Buffer :: Data ( value ) , node :: Buffer :: Length ( value ) , SQLITE_TRANSIENT ) ; } else if ( Integer :: HasInstance ( isolate , value ) ) { return sqlite3_bind_int64 ( handle , index , Integer :: GetValue ( v8 :: Local < v8 :: Object > :: Cast ( value ) ) ) ; } ;
                return -1;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 115 "./src/util/data.lzz"
  void ResultValueFromJS (v8::Isolate * isolate, sqlite3_context * invocation, v8::Local <v8::Value> value, CustomFunction * function)
#line 115 "./src/util/data.lzz"
                                                                                                                                        {
                if ( value -> IsNumber ( ) ) { return sqlite3_result_double ( invocation , v8 :: Local < v8 :: Number > :: Cast ( value ) -> Value ( ) ) ; } else if ( value -> IsString ( ) ) { v8 :: String :: Utf8Value utf8 ( EXTRACT_STRING ( isolate , v8 :: Local < v8 :: String > :: Cast ( value ) ) ) ; return sqlite3_result_text ( invocation , * utf8 , utf8 . length ( ) , SQLITE_TRANSIENT ) ; } else if ( value -> IsNull ( ) || value -> IsUndefined ( ) ) { return sqlite3_result_null ( invocation ) ; } else if ( node :: Buffer :: HasInstance ( value ) ) { return sqlite3_result_blob ( invocation , node :: Buffer :: Data ( value ) , node :: Buffer :: Length ( value ) , SQLITE_TRANSIENT ) ; } else if ( Integer :: HasInstance ( isolate , value ) ) { return sqlite3_result_int64 ( invocation , Integer :: GetValue ( v8 :: Local < v8 :: Object > :: Cast ( value ) ) ) ; } ;
                function->ThrowResultValueError(invocation);
  }
}
#line 4 "./src/util/binder.lzz"
Binder::Binder (sqlite3_stmt * _handle)
#line 4 "./src/util/binder.lzz"
                                               {
                handle = _handle;
                param_count = sqlite3_bind_parameter_count(_handle);
                anon_index = 0;
                success = true;
}
#line 11 "./src/util/binder.lzz"
bool Binder::Bind (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Statement * stmt)
#line 11 "./src/util/binder.lzz"
                                                                  {
                assert(anon_index == 0);
                Result result = BindArgs(info, argc, stmt);
                if (success && result.count != param_count) {
                        if (result.count < param_count) {
                                if (!result.bound_object && stmt->GetBindMap( info . GetIsolate ( ) )->GetSize()) {
                                        Fail(ThrowTypeError, "Missing named parameters");
                                } else {
                                        Fail(ThrowRangeError, "Too few parameter values were provided");
                                }
                        } else {
                                Fail(ThrowRangeError, "Too many parameter values were provided");
                        }
                }
                return success;
}
#line 34 "./src/util/binder.lzz"
bool Binder::IsPlainObject (v8::Isolate * isolate, v8::Local <v8::Object> obj)
#line 34 "./src/util/binder.lzz"
                                                                                   {
                v8::Local<v8::Value> proto = obj->GetPrototype();
                v8::Local<v8::Context> ctx = obj->CreationContext();
                ctx->Enter();
                v8::Local<v8::Value> baseProto = v8::Object::New(isolate)->GetPrototype();
                ctx->Exit();
                return proto->StrictEquals(baseProto) || proto->StrictEquals(v8::Null(isolate));
}
#line 43 "./src/util/binder.lzz"
void Binder::Fail (void (* Throw) (char const *), char const * message)
#line 43 "./src/util/binder.lzz"
                                                                     {
                assert(success == true);
                assert((Throw == NULL) == (message == NULL));
                assert(Throw == ThrowError || Throw == ThrowTypeError || Throw == ThrowRangeError || Throw == NULL);
                if (Throw) Throw(message);
                success = false;
}
#line 51 "./src/util/binder.lzz"
int Binder::NextAnonIndex ()
#line 51 "./src/util/binder.lzz"
                            {
                while (sqlite3_bind_parameter_name(handle, ++anon_index) != NULL) {}
                return anon_index;
}
#line 57 "./src/util/binder.lzz"
void Binder::BindValue (v8::Isolate * isolate, v8::Local <v8::Value> value, int index)
#line 57 "./src/util/binder.lzz"
                                                                                    {
                int status = Data::BindValueFromJS(isolate, handle, index, value);
                if (status != SQLITE_OK) {
                        switch (status) {
                                case -1:
                                        return Fail(ThrowTypeError, "SQLite3 can only bind numbers, strings, Buffers, and null");
                                case SQLITE_RANGE:
                                        return Fail(ThrowRangeError, "Too many parameter values were provided");
                                case SQLITE_TOOBIG:
                                        return Fail(ThrowRangeError, "The bound string or Buffer is too big");
                                case SQLITE_NOMEM:
                                        return Fail(ThrowError, "Out of memory");
                                default:
                                        return Fail(ThrowError, "An unexpected error occured while trying to bind parameters");
                        }
                        assert(false);
                }
}
#line 78 "./src/util/binder.lzz"
int Binder::BindArray (v8::Isolate * isolate, v8::Local <v8::Array> arr)
#line 78 "./src/util/binder.lzz"
                                                                      {
                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                uint32_t length = arr->Length();
                if (length > INT_MAX) {
                        Fail(ThrowRangeError, "Too many parameter values were provided");
                        return 0;
                }
                int len = static_cast<int>(length);
                for (int i=0; i<len; ++i) {
                        v8::MaybeLocal<v8::Value> maybeValue = arr->Get(ctx, i);
                        if (maybeValue.IsEmpty()) {
                                Fail(NULL, NULL);
                                return i;
                        }
                        BindValue(isolate, maybeValue.ToLocalChecked(), NextAnonIndex());
                        if (!success) {
                                return i;
                        }
                }
                return len;
}
#line 104 "./src/util/binder.lzz"
int Binder::BindObject (v8::Isolate * isolate, v8::Local <v8::Object> obj, Statement * stmt)
#line 104 "./src/util/binder.lzz"
                                                                                         {
                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                BindMap* bind_map = stmt->GetBindMap(isolate);
                BindMap::Pair* pairs = bind_map->GetPairs();
                int len = bind_map->GetSize();

                for (int i=0; i<len; ++i) {
                        v8::Local<v8::String> key = pairs[i].GetName(isolate);


                        v8::Maybe<bool> has_property = obj->HasOwnProperty(ctx, key);
                        if (has_property.IsNothing()) {
                                Fail(NULL, NULL);
                                return i;
                        }
                        if (!has_property.FromJust()) {
                                v8::String::Utf8Value param_name(EXTRACT_STRING(isolate, key));
                                Fail(ThrowRangeError, CONCAT("Missing named parameter \"", *param_name, "\"").c_str());
                                return i;
                        }


                        v8::MaybeLocal<v8::Value> maybeValue = obj->Get(ctx, key);
                        if (maybeValue.IsEmpty()) {
                                Fail(NULL, NULL);
                                return i;
                        }

                        BindValue(isolate, maybeValue.ToLocalChecked(), pairs[i].GetIndex());
                        if (!success) {
                                return i;
                        }
                }

                return len;
}
#line 148 "./src/util/binder.lzz"
Binder::Result Binder::BindArgs (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Statement * stmt)
#line 148 "./src/util/binder.lzz"
                                                                        {
                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                int count = 0;
                bool bound_object = false;

                for (int i=0; i<argc; ++i) {
                        v8::Local<v8::Value> arg = info[i];

                        if (arg->IsArray()) {
                                count += BindArray(isolate, v8::Local<v8::Array>::Cast(arg));
                                if (!success) break;
                                continue;
                        }

                        if (arg->IsObject() && !node::Buffer::HasInstance(arg)) {
                                v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(arg);
                                if (IsPlainObject(isolate, obj)) {
                                        if (bound_object) {
                                                Fail(ThrowTypeError, "You cannot specify named parameters in two different objects");
                                                break;
                                        }
                                        bound_object = true;

                                        count += BindObject(isolate, obj, stmt);
                                        if (!success) break;
                                        continue;
                                }
                        }

                        BindValue(isolate, arg, NextAnonIndex());
                        if (!success) break;
                        count += 1;
                }

                return { count, bound_object };
}
#line 31 "./src/better_sqlite3.lzz"
void RegisterModule (v8::Local <v8::Object> exports, v8::Local <v8::Object> module)
#line 31 "./src/better_sqlite3.lzz"
                                                                                 {
        v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ;
        v8 :: HandleScope scope ( isolate ) ;
        CS::Init(isolate, exports, module);
        Integer::Init(isolate, exports, module);
        Database::Init(isolate, exports, module);
        Statement::Init(isolate, exports, module);
        StatementIterator::Init(isolate, exports, module);
        Backup::Init(isolate, exports, module);
}
#undef LZZ_INLINE
