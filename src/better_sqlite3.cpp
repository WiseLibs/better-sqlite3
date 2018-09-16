// better_sqlite3.cpp
//

#include "better_sqlite3.hpp"
#line 14 "./src/better_sqlite3.lzz"
NODE_MODULE(better_sqlite3, RegisterModule);
#define LZZ_INLINE inline
#line 30 "./src/util/macros.lzz"
void ThrowError (char const * message)
#line 30 "./src/util/macros.lzz"
                                     { v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ; isolate->ThrowException(v8::Exception::Error(StringFromUtf8(isolate, message, -1)));
}
#line 31 "./src/util/macros.lzz"
void ThrowTypeError (char const * message)
#line 31 "./src/util/macros.lzz"
                                         { v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ; isolate->ThrowException(v8::Exception::TypeError(StringFromUtf8(isolate, message, -1)));
}
#line 32 "./src/util/macros.lzz"
void ThrowRangeError (char const * message)
#line 32 "./src/util/macros.lzz"
                                          { v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ; isolate->ThrowException(v8::Exception::RangeError(StringFromUtf8(isolate, message, -1)));
}
#line 69 "./src/util/macros.lzz"
std::string CONCAT (char const * a, char const * b, char const * c)
#line 69 "./src/util/macros.lzz"
                                                                {
        std::string result(a);
        result += b;
        result += c;
        return result;
}
#line 86 "./src/util/macros.lzz"
v8::Local <v8::Value> Require (v8::Local <v8::Object> module, char const * path)
#line 86 "./src/util/macros.lzz"
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
ConstantString CS::source;
#line 14 "./src/util/constants.lzz"
ConstantString CS::memory;
#line 15 "./src/util/constants.lzz"
ConstantString CS::readonly;
#line 16 "./src/util/constants.lzz"
ConstantString CS::name;
#line 17 "./src/util/constants.lzz"
ConstantString CS::next;
#line 18 "./src/util/constants.lzz"
ConstantString CS::length;
#line 19 "./src/util/constants.lzz"
ConstantString CS::done;
#line 20 "./src/util/constants.lzz"
ConstantString CS::value;
#line 21 "./src/util/constants.lzz"
ConstantString CS::changes;
#line 22 "./src/util/constants.lzz"
ConstantString CS::lastInsertRowid;
#line 23 "./src/util/constants.lzz"
ConstantString CS::code;
#line 24 "./src/util/constants.lzz"
ConstantString CS::statement;
#line 27 "./src/util/constants.lzz"
void CS::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 27 "./src/util/constants.lzz"
                       {
                AddString(isolate, CS::database, "database");
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
#line 131 "./src/util/constants.lzz"
v8::Local <v8::String> CS::InternalizedFromLatin1 (v8::Isolate * isolate, char const * str)
#line 131 "./src/util/constants.lzz"
                                                                                                   {
                return v8::String::NewFromOneByte(isolate, reinterpret_cast<const uint8_t*>(str), v8::NewStringType::kInternalized).ToLocalChecked();
}
#line 134 "./src/util/constants.lzz"
void CS::AddString (v8::Isolate * isolate, ConstantString & constant, char const * str)
#line 134 "./src/util/constants.lzz"
                                                                                               {
                constant.Reset(isolate, InternalizedFromLatin1(isolate, str));
}
#line 137 "./src/util/constants.lzz"
void CS::AddCode (v8::Isolate * isolate, int code, char const * str)
#line 137 "./src/util/constants.lzz"
                                                                             {
                codes.emplace(std::piecewise_construct, std::forward_as_tuple(code), std::forward_as_tuple(isolate, InternalizedFromLatin1(isolate, str)));
}
#line 140 "./src/util/constants.lzz"
CS::CS (char _)
#line 140 "./src/util/constants.lzz"
                            { assert(false);
}
#line 142 "./src/util/constants.lzz"
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
#line 15 "./src/objects/query.lzz"
Query::QueryExtras::QueryExtras (sqlite3_uint64 _id)
#line 15 "./src/objects/query.lzz"
  : bind_map (0), id (_id)
#line 15 "./src/objects/query.lzz"
                                                                                {}
#line 21 "./src/objects/query.lzz"
Query::Query (sqlite3_uint64 id)
#line 21 "./src/objects/query.lzz"
  : extras (new QueryExtras(id))
#line 21 "./src/objects/query.lzz"
                                                                        {}
#line 22 "./src/objects/query.lzz"
Query::~ Query ()
#line 22 "./src/objects/query.lzz"
                 { delete extras;
}
#line 6 "./src/objects/database.lzz"
void Database::ThrowDatabaseError ()
#line 6 "./src/objects/database.lzz"
                                  {
                if (was_js_error) was_js_error = false;
                else ThrowSqliteError(db_handle);
}
#line 32 "./src/objects/database.lzz"
Database::~ Database ()
#line 32 "./src/objects/database.lzz"
                    {
                CloseHandles();
}
#line 38 "./src/objects/database.lzz"
Database::Database (sqlite3 * _db_handle)
#line 38 "./src/objects/database.lzz"
  : node::ObjectWrap (), db_handle (_db_handle), open (true), busy (false), pragma_mode (false), safe_ints (false), was_js_error (false), stmts ()
#line 45 "./src/objects/database.lzz"
                        {
                assert(_db_handle != NULL);
}
#line 49 "./src/objects/database.lzz"
void Database::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 49 "./src/objects/database.lzz"
                       {
                v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, JS_new);
                t->InstanceTemplate()->SetInternalFieldCount(1);
                t->SetClassName(StringFromUtf8(isolate, "Database", -1));

                NODE_SET_PROTOTYPE_METHOD(t, "prepare", JS_prepare);
                NODE_SET_PROTOTYPE_METHOD(t, "exec", JS_exec);
                NODE_SET_PROTOTYPE_METHOD(t, "pragma", JS_pragma);
                NODE_SET_PROTOTYPE_METHOD(t, "checkpoint", JS_checkpoint);
                NODE_SET_PROTOTYPE_METHOD(t, "register", JS_register);
                NODE_SET_PROTOTYPE_METHOD(t, "loadExtension", JS_loadExtension);
                NODE_SET_PROTOTYPE_METHOD(t, "close", JS_close);
                NODE_SET_PROTOTYPE_METHOD(t, "defaultSafeIntegers", JS_defaultSafeIntegers);
                NODE_SET_PROTOTYPE_GETTER(t, "open", JS_open);
                NODE_SET_PROTOTYPE_GETTER(t, "inTransaction", JS_inTransaction);

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                exports->Set(ctx, StringFromUtf8(isolate, "Database", -1), t->GetFunction(ctx).ToLocalChecked()).FromJust();
                SqliteError.Reset(isolate, v8::Local<v8::Function>::Cast(Require(module, "../../lib/sqlite-error")));
}
#line 70 "./src/objects/database.lzz"
void Database::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 70 "./src/objects/database.lzz"
                            {
                assert(info.IsConstructCall());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > filename = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > filenameGiven = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                if ( info . Length ( ) <= ( 2 ) || ! info [ 2 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "third" " argument to be " "a boolean" ) ; bool in_memory = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 2 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 3 ) || ! info [ 3 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fourth" " argument to be " "a boolean" ) ; bool readonly = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 3 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 4 ) || ! info [ 4 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fifth" " argument to be " "a boolean" ) ; bool must_exist = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 4 ] ) -> Value ( ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                sqlite3* db_handle;
                v8::String::Utf8Value utf8(isolate, filename);
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
                sqlite3_busy_timeout(db_handle, 5000);
                sqlite3_limit(db_handle, SQLITE_LIMIT_LENGTH, MAX_BUFFER_SIZE < MAX_STRING_SIZE ? MAX_BUFFER_SIZE : MAX_STRING_SIZE);
                sqlite3_limit(db_handle, SQLITE_LIMIT_SQL_LENGTH, MAX_STRING_SIZE);
                sqlite3_limit(db_handle, SQLITE_LIMIT_COLUMN, INT_MAX);
                sqlite3_limit(db_handle, SQLITE_LIMIT_COMPOUND_SELECT, INT_MAX);
                sqlite3_limit(db_handle, SQLITE_LIMIT_VARIABLE_NUMBER, 999);

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                Database* db = new Database(db_handle);
                db->Wrap(info.This());
                SetFrozen(isolate, ctx, info.This(), CS::memory, in_memory ? v8::True(isolate) : v8::False(isolate));
                SetFrozen(isolate, ctx, info.This(), CS::readonly, readonly ? v8::True(isolate) : v8::False(isolate));
                SetFrozen(isolate, ctx, info.This(), CS::name, filenameGiven);

                info.GetReturnValue().Set(info.This());
}
#line 110 "./src/objects/database.lzz"
void Database::JS_prepare (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 110 "./src/objects/database.lzz"
                                {
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > source = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                v8::MaybeLocal<v8::Object> maybe_statement = Statement::New( info . GetIsolate ( ) , info.This(), source);
                if (!maybe_statement.IsEmpty()) info.GetReturnValue().Set(maybe_statement.ToLocalChecked());
}
#line 116 "./src/objects/database.lzz"
void Database::JS_exec (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 116 "./src/objects/database.lzz"
                             {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > source = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                v8::String::Utf8Value sql( info . GetIsolate ( ) , source);
                if (sqlite3_exec(db->db_handle, *sql, NULL, NULL, NULL) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                info.GetReturnValue().Set(info.This());
}
#line 128 "./src/objects/database.lzz"
void Database::JS_pragma (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 128 "./src/objects/database.lzz"
                               {
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; node :: ObjectWrap :: Unwrap < Database > ( info . This ( ) ) -> pragma_mode = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ;
}
#line 132 "./src/objects/database.lzz"
void Database::JS_checkpoint (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 132 "./src/objects/database.lzz"
                                   {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                sqlite3* db_handle = db->db_handle;

                if (info.Length()) {
                        if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > onlyDatabase = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                        v8::String::Utf8Value only_database( info . GetIsolate ( ) , onlyDatabase);
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
#line 174 "./src/objects/database.lzz"
void Database::JS_register (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 174 "./src/objects/database.lzz"
                                 {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsFunction ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a function" ) ; v8 :: Local < v8 :: Function > fn = v8 :: Local < v8 :: Function > :: Cast ( info [ 0 ] ) ;
                if ( info . Length ( ) <= ( 1 ) || ! info [ 1 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "second" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > nameString = v8 :: Local < v8 :: String > :: Cast ( info [ 1 ] ) ;
                if ( info . Length ( ) <= ( 2 ) || ! info [ 2 ] -> IsInt32 ( ) ) return ThrowTypeError ( "Expected " "third" " argument to be " "a 32-bit signed integer" ) ; int argc = v8 :: Local < v8 :: Int32 > :: Cast ( info [ 2 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 3 ) || ! info [ 3 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fourth" " argument to be " "a boolean" ) ; bool aggregate = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 3 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 4 ) || ! info [ 4 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "fifth" " argument to be " "a boolean" ) ; bool deterministic = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 4 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 5 ) || ! info [ 5 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "sixth" " argument to be " "a boolean" ) ; bool default_safe_ints = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 5 ] ) -> Value ( ) ;
                if ( info . Length ( ) <= ( 6 ) || ! info [ 6 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "seventh" " argument to be " "a boolean" ) ; bool safe_ints = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 6 ] ) -> Value ( ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;

                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                v8::String::Utf8Value name(isolate, nameString);
                int mask = deterministic ? SQLITE_UTF8 | SQLITE_DETERMINISTIC : SQLITE_UTF8;
                auto xFunc = aggregate ? NULL : CustomFunction::xFunc;
                auto xStep = aggregate ? CustomFunction::xStep : NULL;
                auto xFinal = aggregate ? CustomFunction::xFinal : NULL;
                if (default_safe_ints) safe_ints = db->safe_ints;
                assert(name.length() > 0);

                if (sqlite3_create_function_v2(db->db_handle, *name, argc, mask, new CustomFunction(fn, isolate, db, *name, argc, safe_ints), xFunc, xStep, xFinal, CustomFunction::xDestroy) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                info.GetReturnValue().Set(info.This());
}
#line 201 "./src/objects/database.lzz"
void Database::JS_loadExtension (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 201 "./src/objects/database.lzz"
                                      {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsString ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a string" ) ; v8 :: Local < v8 :: String > filenameString = v8 :: Local < v8 :: String > :: Cast ( info [ 0 ] ) ;
                if ( ! db -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                v8::String::Utf8Value filename( info . GetIsolate ( ) , filenameString);
                sqlite3_enable_load_extension(db->db_handle, 1);
                char* error;
                int status = sqlite3_load_extension(db->db_handle, *filename, NULL, &error);
                sqlite3_enable_load_extension(db->db_handle, 0);
                if (status == SQLITE_OK) info.GetReturnValue().Set(info.This());
                else ThrowSqliteError(db->db_handle, error, status);
                sqlite3_free(error);
}
#line 216 "./src/objects/database.lzz"
void Database::JS_close (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 216 "./src/objects/database.lzz"
                              {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if (db->open) {
                        if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                        db->CloseHandles();
                }
                info.GetReturnValue().Set(info.This());
}
#line 225 "./src/objects/database.lzz"
void Database::JS_defaultSafeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 225 "./src/objects/database.lzz"
                                            {
                Database* db = node :: ObjectWrap :: Unwrap <Database>(info.This());
                if ( db -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) db->safe_ints = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; db -> safe_ints = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                info.GetReturnValue().Set(info.This());
}
#line 233 "./src/objects/database.lzz"
void Database::JS_open (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info)
#line 233 "./src/objects/database.lzz"
                             {
                info.GetReturnValue().Set( node :: ObjectWrap :: Unwrap <Database>(info.This())->open);
}
#line 237 "./src/objects/database.lzz"
void Database::JS_inTransaction (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info)
#line 237 "./src/objects/database.lzz"
                                      {
                info.GetReturnValue().Set(
                        !static_cast<bool>(sqlite3_get_autocommit( node :: ObjectWrap :: Unwrap <Database>(info.This())->db_handle))
                );
}
#line 243 "./src/objects/database.lzz"
void Database::CloseHandles ()
#line 243 "./src/objects/database.lzz"
                            {
                if (open) {
                        open = false;
                        for (Statement* stmt : stmts) stmt->CloseHandles();
                        stmts.clear();
                        int status = sqlite3_close(db_handle);
                        assert(status == SQLITE_OK); ((void)status);
                }
}
#line 253 "./src/objects/database.lzz"
void Database::ThrowSqliteError (sqlite3 * db_handle)
#line 253 "./src/objects/database.lzz"
                                                         {
                assert(db_handle != NULL);
                ThrowSqliteError(db_handle, sqlite3_errmsg(db_handle), sqlite3_extended_errcode(db_handle));
}
#line 257 "./src/objects/database.lzz"
void Database::ThrowSqliteError (sqlite3 * db_handle, char const * message, int code)
#line 257 "./src/objects/database.lzz"
                                                                                        {
                assert(db_handle != NULL);
                assert(message != NULL);
                assert((code & 0xff) != SQLITE_OK);
                v8 :: Isolate * isolate = v8 :: Isolate :: GetCurrent ( ) ;
                v8::Local<v8::Value> args[2] = { StringFromUtf8(isolate, message, -1), CS::Code(isolate, code) };
                isolate->ThrowException(v8::Local<v8::Function>::New(isolate, SqliteError)->NewInstance( isolate -> GetCurrentContext ( ) , 2, args).ToLocalChecked());
}
#line 266 "./src/objects/database.lzz"
v8::Persistent <v8::Function> Database::SqliteError;
#line 267 "./src/objects/database.lzz"
int const Database::MAX_BUFFER_SIZE;
#line 268 "./src/objects/database.lzz"
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
#line 16 "./src/objects/statement.lzz"
BindMap * Statement::GetBindMap (v8::Isolate * isolate)
#line 16 "./src/objects/statement.lzz"
                                                  {
                if (has_bind_map) return BindMapPointer();
                BindMap* bind_map = BindMapPointer();
                int param_count = sqlite3_bind_parameter_count(handle);
                for (int i=1; i<=param_count; ++i) {
                        const char* name = sqlite3_bind_parameter_name(handle, i);
                        if (name != NULL) bind_map->Add(isolate, name + 1, i);
                }
                has_bind_map = true;
                return bind_map;
}
#line 29 "./src/objects/statement.lzz"
void Statement::CloseHandles ()
#line 29 "./src/objects/statement.lzz"
                            {
                if (alive) {
                        alive = false;
                        sqlite3_finalize(handle);
                }
}
#line 36 "./src/objects/statement.lzz"
Statement::~ Statement ()
#line 36 "./src/objects/statement.lzz"
                     {
                if (alive) db->RemoveStatement(this);
                CloseHandles();
}
#line 43 "./src/objects/statement.lzz"
Statement::Statement (Database * _db, sqlite3_stmt * _handle, bool _returns_data)
#line 43 "./src/objects/statement.lzz"
  : node::ObjectWrap (), Query (next_id++), db (_db), handle (_handle), alive (true), bound (false), has_bind_map (false), safe_ints (_db->GetState()->safe_ints), pluck (false), returns_data (_returns_data)
#line 51 "./src/objects/statement.lzz"
                                            {
                assert(db != NULL);
                assert(handle != NULL);
                assert(db->GetState()->open);
                assert(!db->GetState()->busy);
                db->AddStatement(this);
}
#line 59 "./src/objects/statement.lzz"
void Statement::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 59 "./src/objects/statement.lzz"
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
                NODE_SET_PROTOTYPE_METHOD(t, "safeIntegers", JS_safeIntegers);
                NODE_SET_PROTOTYPE_GETTER(t, "returnsData", JS_returnsData);

                constructor.Reset(isolate, t->GetFunction( isolate -> GetCurrentContext ( ) ).ToLocalChecked());
                next_id = 0;
                constructing_privileges = false;
}
#line 78 "./src/objects/statement.lzz"
void Statement::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 78 "./src/objects/statement.lzz"
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
                v8::String::Value sql(isolate, source);
                const void* tail;
                sqlite3_stmt* handle;

                if (sqlite3_prepare16_v2(db->GetHandle(), *sql, sql.length() * sizeof(uint16_t) + 1, &handle, &tail) != SQLITE_OK) {
                        return db->ThrowDatabaseError();
                }
                if (handle == NULL) {
                        return ThrowRangeError("The supplied SQL string contains no statements");
                }
                if (tail != (const void*)(*sql + sql.length())) {
                        sqlite3_finalize(handle);
                        return ThrowRangeError("The supplied SQL string contains more than one statement");
                }
                bool returns_data = (sqlite3_stmt_readonly(handle) && sqlite3_column_count(handle) >= 1) || db->GetState()->pragma_mode;

                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                Statement* stmt = new Statement(db, handle, returns_data);
                stmt->Wrap(info.This());
                SetFrozen(isolate, ctx, info.This(), CS::source, source);
                SetFrozen(isolate, ctx, info.This(), CS::database, database);

                info.GetReturnValue().Set(info.This());
}
#line 115 "./src/objects/statement.lzz"
void Statement::JS_run (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 115 "./src/objects/statement.lzz"
                            {
                Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( stmt -> returns_data ) return ThrowTypeError ( "This statement returns data. Use get(), all(), or iterate() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; Database :: State * db_state = db -> GetState ( ) ; if ( ! db_state -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db_state -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( info . Length ( ) > 0 ) { if ( bound ) return ThrowTypeError ( "This statement already has bound parameters" ) ; Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } ( ( void ) 0 ) ;
                sqlite3* db_handle = db->GetHandle();
                int total_changes_before = sqlite3_total_changes(db_handle);

                sqlite3_step(handle);
                if (sqlite3_reset(handle) == SQLITE_OK) {
                        int changes = sqlite3_total_changes(db_handle) == total_changes_before ? 0 : sqlite3_changes(db_handle);
                        sqlite3_int64 id = sqlite3_last_insert_rowid(db_handle);
                        v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                        v8::Local<v8::Object> result = v8::Object::New(isolate);
                        result->Set(ctx, CS::Get(isolate, CS::changes), v8::Number::New(isolate, static_cast<double>(changes))).FromJust();
                        result->Set(ctx, CS::Get(isolate, CS::lastInsertRowid), Integer::New(isolate, id, stmt->safe_ints)).FromJust();
                        info . GetReturnValue ( ) . Set ( result ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                }
                db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 133 "./src/objects/statement.lzz"
void Statement::JS_get (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 133 "./src/objects/statement.lzz"
                            {
                Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( ! stmt -> returns_data ) return ThrowTypeError ( "This statement does not return data. Use run() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; Database :: State * db_state = db -> GetState ( ) ; if ( ! db_state -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db_state -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( info . Length ( ) > 0 ) { if ( bound ) return ThrowTypeError ( "This statement already has bound parameters" ) ; Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } ( ( void ) 0 ) ;
                v8 :: Isolate * isolate = info . GetIsolate ( ) ;
                int status = sqlite3_step(handle);
                if (status == SQLITE_ROW) {
                        v8::Local<v8::Value> result = stmt->pluck
                                ? Data::GetValueJS(isolate, handle, 0, stmt->safe_ints)
                                : Data::GetRowJS(isolate, isolate -> GetCurrentContext ( ) , handle, stmt->safe_ints);
                        sqlite3_reset(handle);
                        info . GetReturnValue ( ) . Set ( result ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                } else if (status == SQLITE_DONE) {
                        sqlite3_reset(handle);
                        info . GetReturnValue ( ) . Set ( v8 :: Undefined ( isolate ) ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                }
                sqlite3_reset(handle);
                db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 151 "./src/objects/statement.lzz"
void Statement::JS_all (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 151 "./src/objects/statement.lzz"
                            {
                Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( ! stmt -> returns_data ) return ThrowTypeError ( "This statement does not return data. Use run() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; Database :: State * db_state = db -> GetState ( ) ; if ( ! db_state -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db_state -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( info . Length ( ) > 0 ) { if ( bound ) return ThrowTypeError ( "This statement already has bound parameters" ) ; Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } ( ( void ) 0 ) ;
                v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                v8::Local<v8::Array> result = v8::Array::New(isolate, 0);
                uint32_t row_count = 0;
                const bool safe_ints = stmt->safe_ints;
                const bool pluck = stmt->pluck;
                bool js_error = false;

                while (sqlite3_step(handle) == SQLITE_ROW) {
                        if (row_count == 0xffffffff) { ThrowRangeError("Array overflow (too many rows returned)"); js_error = true; break; }
                        result->Set(ctx, row_count++, pluck
                                ? Data::GetValueJS(isolate, handle, 0, safe_ints)
                                : Data::GetRowJS(isolate, ctx, handle, safe_ints)
                        ).FromJust();
                }

                if (sqlite3_reset(handle) == SQLITE_OK && !js_error) {
                        info . GetReturnValue ( ) . Set ( result ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
                }
                if (js_error) db_state->was_js_error = true;
                db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 175 "./src/objects/statement.lzz"
void Statement::JS_iterate (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 175 "./src/objects/statement.lzz"
                                {
                v8::MaybeLocal<v8::Object> maybe_iter = StatementIterator::New( info . GetIsolate ( ) , info);
                if (!maybe_iter.IsEmpty()) info.GetReturnValue().Set(maybe_iter.ToLocalChecked());
}
#line 180 "./src/objects/statement.lzz"
void Statement::JS_bind (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 180 "./src/objects/statement.lzz"
                             {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (stmt->bound) return ThrowTypeError("The bind() method can only be invoked once per statement object");
                if ( ! stmt -> db -> GetState ( ) -> open ) return ThrowTypeError ( "The database connection is not open" ) ;
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                Binder binder ( stmt -> handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( stmt -> handle ) ; return ; } ( ( void ) 0 ) ;
                stmt->bound = true;
                info.GetReturnValue().Set(info.This());
}
#line 190 "./src/objects/statement.lzz"
void Statement::JS_pluck (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 190 "./src/objects/statement.lzz"
                              {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if (!stmt->returns_data) return ThrowTypeError("The pluck() method is only for statements that return data");
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) stmt->pluck = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; stmt -> pluck = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                info.GetReturnValue().Set(info.This());
}
#line 199 "./src/objects/statement.lzz"
void Statement::JS_safeIntegers (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 199 "./src/objects/statement.lzz"
                                     {
                Statement* stmt = node :: ObjectWrap :: Unwrap <Statement>(info.This());
                if ( stmt -> db -> GetState ( ) -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ;
                if (info.Length() == 0) stmt->safe_ints = true;
                else { if ( info . Length ( ) <= ( 0 ) || ! info [ 0 ] -> IsBoolean ( ) ) return ThrowTypeError ( "Expected " "first" " argument to be " "a boolean" ) ; stmt -> safe_ints = v8 :: Local < v8 :: Boolean > :: Cast ( info [ 0 ] ) -> Value ( ) ; }
                info.GetReturnValue().Set(info.This());
}
#line 207 "./src/objects/statement.lzz"
void Statement::JS_returnsData (v8::Local <v8 :: String> _, v8::PropertyCallbackInfo <v8 :: Value> const & info)
#line 207 "./src/objects/statement.lzz"
                                    {
                info.GetReturnValue().Set( node :: ObjectWrap :: Unwrap <Statement>(info.This())->returns_data);
}
#line 211 "./src/objects/statement.lzz"
v8::Persistent <v8::Function> Statement::constructor;
#line 212 "./src/objects/statement.lzz"
sqlite3_uint64 Statement::next_id;
#line 213 "./src/objects/statement.lzz"
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
  : node::ObjectWrap (), stmt (_stmt), handle (_stmt->handle), safe_ints (_stmt->safe_ints), pluck (_stmt->pluck), bound (_bound), alive (true)
#line 26 "./src/objects/statement-iterator.lzz"
                            {
                assert(stmt != NULL);
                assert(handle != NULL);
                assert(stmt->bound == bound);
                assert(stmt->alive == true);
}
#line 33 "./src/objects/statement-iterator.lzz"
void StatementIterator::Init (v8::Isolate * isolate, v8::Local <v8 :: Object> exports, v8::Local <v8 :: Object> module)
#line 33 "./src/objects/statement-iterator.lzz"
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
#line 46 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_new (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 46 "./src/objects/statement-iterator.lzz"
                            {
                if (caller_info == NULL) return ThrowTypeError("Disabled constructor");
                assert(info.IsConstructCall());

                StatementIterator* iter;
                {
                        const v8 :: FunctionCallbackInfo < v8 :: Value > & info = *caller_info;
                        Statement * stmt = node :: ObjectWrap :: Unwrap < Statement > ( info . This ( ) ) ; if ( ! stmt -> returns_data ) return ThrowTypeError ( "This statement does not return data. Use run() instead" ) ; sqlite3_stmt * handle = stmt -> handle ; Database * db = stmt -> db ; Database :: State * db_state = db -> GetState ( ) ; if ( ! db_state -> open ) return ThrowTypeError ( "The database connection is not open" ) ; if ( db_state -> busy ) return ThrowTypeError ( "This database connection is busy executing a query" ) ; const bool bound = stmt -> bound ; if ( info . Length ( ) > 0 ) { if ( bound ) return ThrowTypeError ( "This statement already has bound parameters" ) ; Binder binder ( handle ) ; if ( ! binder . Bind ( info , info . Length ( ) , stmt ) ) { sqlite3_clear_bindings ( handle ) ; return ; } ( ( void ) 0 ) ; } ( ( void ) 0 ) ;
                        iter = new StatementIterator(stmt, bound);
                        db_state->busy = true;
                }
                v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                iter->Wrap(info.This());
                SetFrozen(isolate, ctx, info.This(), CS::statement, caller_info->This());

                info.GetReturnValue().Set(info.This());
}
#line 64 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_next (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 64 "./src/objects/statement-iterator.lzz"
                             {
                StatementIterator* iter = node :: ObjectWrap :: Unwrap <StatementIterator>(info.This());
                if (iter->alive) iter->Next(info);
                else info.GetReturnValue().Set(DoneRecord( info . GetIsolate ( ) ));
}
#line 70 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_return (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 70 "./src/objects/statement-iterator.lzz"
                               {
                StatementIterator* iter = node :: ObjectWrap :: Unwrap <StatementIterator>(info.This());
                if (iter->alive) iter->Return(info);
                else info.GetReturnValue().Set(DoneRecord( info . GetIsolate ( ) ));
}
#line 76 "./src/objects/statement-iterator.lzz"
void StatementIterator::JS_symbolIterator (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 76 "./src/objects/statement-iterator.lzz"
                                       {
                info.GetReturnValue().Set(info.This());
}
#line 80 "./src/objects/statement-iterator.lzz"
void StatementIterator::Next (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 80 "./src/objects/statement-iterator.lzz"
                                       {
                assert(alive == true);
                int status = sqlite3_step(handle);
                if (status == SQLITE_ROW) {
                        v8 :: Isolate * isolate = info . GetIsolate ( ) ; v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                        info.GetReturnValue().Set(
                                NewRecord(isolate, ctx, pluck
                                        ? Data::GetValueJS(isolate, handle, 0, safe_ints)
                                        : Data::GetRowJS(isolate, ctx, handle, safe_ints))
                        );
                } else {
                        if (status == SQLITE_DONE) Return(info);
                        else Throw();
                }
}
#line 96 "./src/objects/statement-iterator.lzz"
void StatementIterator::Return (v8::FunctionCallbackInfo <v8 :: Value> const & info)
#line 96 "./src/objects/statement-iterator.lzz"
                                         {
                Cleanup();
                info . GetReturnValue ( ) . Set ( DoneRecord ( info . GetIsolate ( ) ) ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 101 "./src/objects/statement-iterator.lzz"
void StatementIterator::Throw ()
#line 101 "./src/objects/statement-iterator.lzz"
                     {
                Cleanup();
                Database* db = stmt->db;
                db -> ThrowDatabaseError ( ) ; if ( ! bound ) { sqlite3_clear_bindings ( handle ) ; } return ;
}
#line 107 "./src/objects/statement-iterator.lzz"
void StatementIterator::Cleanup ()
#line 107 "./src/objects/statement-iterator.lzz"
                       {
                assert(alive == true);
                alive = false;
                sqlite3_reset(handle);
                stmt->db->GetState()->busy = false;
}
#line 114 "./src/objects/statement-iterator.lzz"
v8::Local <v8::Object> StatementIterator::NewRecord (v8::Isolate * isolate, v8::Local <v8::Context> ctx, v8::Local <v8::Value> value, bool done)
#line 114 "./src/objects/statement-iterator.lzz"
                                                                                                                                                {
                v8::Local<v8::Object> record = v8::Object::New(isolate);
                record->Set(ctx, CS::Get(isolate, CS::value), value).FromJust();
                record->Set(ctx, CS::Get(isolate, CS::done), done ? v8::True(isolate) : v8::False(isolate)).FromJust();
                return record;
}
#line 121 "./src/objects/statement-iterator.lzz"
v8::Local <v8::Object> StatementIterator::DoneRecord (v8::Isolate * isolate)
#line 121 "./src/objects/statement-iterator.lzz"
                                                                      {
                return NewRecord(isolate, isolate -> GetCurrentContext ( ) , v8::Undefined(isolate), true);
}
#line 125 "./src/objects/statement-iterator.lzz"
v8::Persistent <v8::Function> StatementIterator::constructor;
#line 126 "./src/objects/statement-iterator.lzz"
v8::FunctionCallbackInfo <v8 :: Value> const * StatementIterator::caller_info;
#line 5 "./src/util/custom-function.lzz"
CustomFunction::CustomFunction (v8::Local <v8::Function> _fn, v8::Isolate * _isolate, Database * _db, char const * _name, int _argc, bool _safe_ints)
#line 6 "./src/util/custom-function.lzz"
  : fn (_isolate, _fn), isolate (_isolate), db (_db), name (CopyString(_name)), argc (_argc), safe_ints (_safe_ints)
#line 6 "./src/util/custom-function.lzz"
                                                                                                                             {}
#line 7 "./src/util/custom-function.lzz"
CustomFunction::~ CustomFunction ()
#line 7 "./src/util/custom-function.lzz"
                          { delete[] name;
}
#line 9 "./src/util/custom-function.lzz"
void CustomFunction::xDestroy (void * instance)
#line 9 "./src/util/custom-function.lzz"
                                             {
                CustomFunction * cf = static_cast < CustomFunction * > ( instance ) ; v8 :: Isolate * isolate = cf -> isolate ; v8 :: HandleScope scope ( isolate ) ;
                delete cf;
}
#line 13 "./src/util/custom-function.lzz"
void CustomFunction::xFunc (sqlite3_context * ctx, int argc, sqlite3_value * * argv)
#line 13 "./src/util/custom-function.lzz"
                                                                                {
                CustomFunction * cf = static_cast < CustomFunction * > ( sqlite3_user_data ( ctx ) ) ; v8 :: Isolate * isolate = cf -> isolate ; v8 :: HandleScope scope ( isolate ) ;
                Database :: State * db_state = cf -> db -> GetState ( ) ; v8 :: Local < v8 :: Value > * args = Data :: GetArgumentsJS ( isolate , argv , argc , cf -> safe_ints ) ; bool was_busy = db_state -> busy ; db_state -> busy = true ; v8 :: MaybeLocal < v8 :: Value > maybe_return_value = v8 :: Local < v8 :: Function > :: New ( isolate , cf -> fn ) -> Call ( isolate -> GetCurrentContext ( ) , v8 :: Undefined ( isolate ) , argc , args ) ; db_state -> busy = was_busy ; delete [ ] args ; if ( maybe_return_value . IsEmpty ( ) ) { ; return cf -> PropagateJSError ( ctx ) ; } ( ( void ) 0 ) ;
                Data::ResultValueFromJS(isolate, ctx, maybe_return_value.ToLocalChecked(), cf);
}
#line 18 "./src/util/custom-function.lzz"
void CustomFunction::xStep (sqlite3_context * ctx, int argc, sqlite3_value * * argv)
#line 18 "./src/util/custom-function.lzz"
                                                                                {
                CustomFunction * cf = static_cast < CustomFunction * > ( sqlite3_user_data ( ctx ) ) ; v8 :: Isolate * isolate = cf -> isolate ; v8 :: HandleScope scope ( isolate ) ; CustomAggregate * ca = static_cast < CustomAggregate * > ( sqlite3_aggregate_context ( ctx , sizeof ( CustomAggregate ) ) ) ; if ( ca -> IsUninitialized ( ) ) { ca -> Activate ( isolate , cf ) ; if ( ! ca -> IsActive ( ) ) return cf -> PropagateJSError ( ctx ) ; } ;
                assert(ca->IsActive());


                Database :: State * db_state = cf -> db -> GetState ( ) ; v8 :: Local < v8 :: Value > * args = Data :: GetArgumentsJS ( isolate , argv , argc , cf -> safe_ints ) ; bool was_busy = db_state -> busy ; db_state -> busy = true ; v8 :: MaybeLocal < v8 :: Value > _ = ca -> GetFn ( isolate ) -> Call ( isolate -> GetCurrentContext ( ) , v8 :: Undefined ( isolate ) , argc , args ) ; db_state -> busy = was_busy ; delete [ ] args ; if ( _ . IsEmpty ( ) ) { ca -> Destroy ( ) ; return cf -> PropagateJSError ( ctx ) ; } ( ( void ) 0 ) ;
}
#line 25 "./src/util/custom-function.lzz"
void CustomFunction::xFinal (sqlite3_context * ctx)
#line 25 "./src/util/custom-function.lzz"
                                                 {
                CustomFunction * cf = static_cast < CustomFunction * > ( sqlite3_user_data ( ctx ) ) ; v8 :: Isolate * isolate = cf -> isolate ; v8 :: HandleScope scope ( isolate ) ; CustomAggregate * ca = static_cast < CustomAggregate * > ( sqlite3_aggregate_context ( ctx , sizeof ( CustomAggregate ) ) ) ; if ( ca -> IsUninitialized ( ) ) { ca -> Activate ( isolate , cf ) ; if ( ! ca -> IsActive ( ) ) return cf -> PropagateJSError ( ctx ) ; } else if (!ca->IsActive()) return;
                assert(ca->IsActive());

                CustomAggregate::Entry entry = ca->ProgressGenerator(isolate, isolate -> GetCurrentContext ( ) );
                ca->Destroy();

                if (entry.threw) return cf->PropagateJSError(ctx);
                if (!entry.done) {
                        ThrowTypeError(CONCAT("Custom aggregate ", cf->name, "() should only yield once").c_str());
                        return cf->PropagateJSError(ctx);
                }
                Data::ResultValueFromJS(isolate, ctx, entry.value, cf);
}
#line 40 "./src/util/custom-function.lzz"
void CustomFunction::ThrowResultValueError (sqlite3_context * ctx)
#line 40 "./src/util/custom-function.lzz"
                                                         {
                ThrowTypeError(CONCAT("Custom function ", name, "() returned an invalid value").c_str());
                PropagateJSError(ctx);
}
#line 46 "./src/util/custom-function.lzz"
void CustomFunction::PropagateJSError (sqlite3_context * ctx)
#line 46 "./src/util/custom-function.lzz"
                                                    {
                assert(db->GetState()->was_js_error == false);
                db->GetState()->was_js_error = true;
                sqlite3_result_error(ctx, "", 0);
}
#line 52 "./src/util/custom-function.lzz"
char const * CustomFunction::CopyString (char const * source)
#line 52 "./src/util/custom-function.lzz"
                                                          {
                size_t bytes = strlen(source) + 1;
                char* dest = new char[bytes];
                memcpy(dest, source, bytes);
                return dest;
}
#line 12 "./src/util/custom-aggregate.lzz"
void CustomAggregate::Activate (v8::Isolate * isolate, CustomFunction * cf)
#line 12 "./src/util/custom-aggregate.lzz"
                                                                {
                assert(state == uninitialized);
                v8 :: HandleScope scope ( isolate ) ;
                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                v8::Local<v8::Object> _generator = v8::Local<v8::Object>::Cast(v8::Local<v8::Function>::New(isolate, cf->fn)->Call(ctx, v8::Undefined(isolate), 0, NULL).ToLocalChecked());
                v8::Local<v8::Function> _next = v8::Local<v8::Function>::Cast(_generator->Get(ctx, CS::Get(isolate, CS::next)).ToLocalChecked());
                generator.Reset(isolate, _generator);
                next.Reset(isolate, _next);
                state = active;

                Entry entry = ProgressGenerator(isolate, ctx);
                if (entry.threw) return Destroy();
                if (entry.done || !entry.value->IsFunction()) {
                        ThrowTypeError(CONCAT("Custom aggregate ", cf->name, "() did not yield a function").c_str());
                        return Destroy();
                }
                v8::Local<v8::Function> _fn = v8::Local<v8::Function>::Cast(entry.value);

                int argc = cf->argc;
                if (argc >= 0) {
                        v8::MaybeLocal<v8::Value> maybe_length = _fn->Get(ctx, CS::Get(isolate, CS::length));
                        if (maybe_length.IsEmpty()) return Destroy();

                        v8::Local<v8::Value> lengthValue = maybe_length.ToLocalChecked();
                        if (!lengthValue->IsInt32() || argc != v8::Local<v8::Int32>::Cast(lengthValue)->Value()) {
                                ThrowTypeError(CONCAT("Custom aggregate ", cf->name, "() has an inconsistent function.length").c_str());
                                return Destroy();
                        }
                }
                fn.Reset(isolate, _fn);
}
#line 60 "./src/util/custom-aggregate.lzz"
CustomAggregate::Entry CustomAggregate::ProgressGenerator (v8::Isolate * isolate, v8::Local <v8::Context> ctx)
#line 60 "./src/util/custom-aggregate.lzz"
                                                                                  {
                assert(state == active);
                v8::MaybeLocal<v8::Value> maybe_entry = v8::Local<v8::Function>::New(isolate, next)->Call(ctx, v8::Local<v8::Object>::New(isolate, generator), 0, NULL);
                if (maybe_entry.IsEmpty()) return { v8::Local<v8::Value>(), true, true };
                v8::Local<v8::Object> entry = v8::Local<v8::Object>::Cast(maybe_entry.ToLocalChecked());
                return {
                        entry->Get(ctx, CS::Get(isolate, CS::value)).ToLocalChecked(),
                        entry->Get(ctx, CS::Get(isolate, CS::done)).ToLocalChecked()->BooleanValue(),
                        false
                };
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
  v8::Local <v8::Value> * GetArgumentsJS (v8::Isolate * isolate, sqlite3_value * * values, int argument_count, bool safe_ints)
#line 75 "./src/util/data.lzz"
                                                                                                                               {
                if (argument_count == 0) {
                        return NULL;
                }
                v8::Local<v8::Value>* args = ALLOC_ARRAY<v8::Local<v8::Value>>(argument_count);
                for (int i=0; i<argument_count; ++i) {
                        args[i] = Data::GetValueJS(isolate, values[i], safe_ints);
                }
                return args;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 86 "./src/util/data.lzz"
  int BindValueFromJS (v8::Isolate * isolate, sqlite3_stmt * handle, int index, v8::Local <v8::Value> value)
#line 86 "./src/util/data.lzz"
                                                                                                               {
                if ( value -> IsNumber ( ) ) { return sqlite3_bind_double ( handle , index , v8 :: Local < v8 :: Number > :: Cast ( value ) -> Value ( ) ) ; } else if ( value -> IsString ( ) ) { v8 :: String :: Utf8Value utf8 ( isolate , v8 :: Local < v8 :: String > :: Cast ( value ) ) ; return sqlite3_bind_text ( handle , index , * utf8 , utf8 . length ( ) , SQLITE_TRANSIENT ) ; } else if ( value -> IsNull ( ) || value -> IsUndefined ( ) ) { return sqlite3_bind_null ( handle , index ) ; } else if ( node :: Buffer :: HasInstance ( value ) ) { return sqlite3_bind_blob ( handle , index , node :: Buffer :: Data ( value ) , node :: Buffer :: Length ( value ) , SQLITE_TRANSIENT ) ; } else if ( Integer :: HasInstance ( isolate , value ) ) { return sqlite3_bind_int64 ( handle , index , Integer :: GetValue ( v8 :: Local < v8 :: Object > :: Cast ( value ) ) ) ; } ;
                return -1;
  }
}
#line 54 "./src/util/data.lzz"
namespace Data
{
#line 91 "./src/util/data.lzz"
  void ResultValueFromJS (v8::Isolate * isolate, sqlite3_context * ctx, v8::Local <v8::Value> value, CustomFunction * function)
#line 91 "./src/util/data.lzz"
                                                                                                                                 {
                if ( value -> IsNumber ( ) ) { return sqlite3_result_double ( ctx , v8 :: Local < v8 :: Number > :: Cast ( value ) -> Value ( ) ) ; } else if ( value -> IsString ( ) ) { v8 :: String :: Utf8Value utf8 ( isolate , v8 :: Local < v8 :: String > :: Cast ( value ) ) ; return sqlite3_result_text ( ctx , * utf8 , utf8 . length ( ) , SQLITE_TRANSIENT ) ; } else if ( value -> IsNull ( ) || value -> IsUndefined ( ) ) { return sqlite3_result_null ( ctx ) ; } else if ( node :: Buffer :: HasInstance ( value ) ) { return sqlite3_result_blob ( ctx , node :: Buffer :: Data ( value ) , node :: Buffer :: Length ( value ) , SQLITE_TRANSIENT ) ; } else if ( Integer :: HasInstance ( isolate , value ) ) { return sqlite3_result_int64 ( ctx , Integer :: GetValue ( v8 :: Local < v8 :: Object > :: Cast ( value ) ) ) ; } ;
                function->ThrowResultValueError(ctx);
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
bool Binder::Bind (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Statement * query)
#line 11 "./src/util/binder.lzz"
                                                                   {
                assert(anon_index == 0);
                Result result = BindArgs(info, argc, query);
                if (success && result.count != param_count) {
                        if (result.count < param_count) {
                                if (!result.bound_object && query->GetBindMap( info . GetIsolate ( ) )->GetSize()) {
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
int Binder::BindObject (v8::Isolate * isolate, v8::Local <v8::Object> obj, Query * query)
#line 104 "./src/util/binder.lzz"
                                                                                      {
                v8 :: Local < v8 :: Context > ctx = isolate -> GetCurrentContext ( ) ;
                BindMap* bind_map = static_cast<Statement*>(query)->GetBindMap(isolate);
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
                                v8::String::Utf8Value param_name(isolate, key);
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
Binder::Result Binder::BindArgs (v8::FunctionCallbackInfo <v8 :: Value> const & info, int argc, Query * query)
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

                                        count += BindObject(isolate, obj, query);
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
}
#undef LZZ_INLINE
