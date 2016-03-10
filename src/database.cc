#include <cstdlib>
#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "database.h"

namespace NODE_SQLITE3_PLUS_DATABASE {
    const int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_SHAREDCACHE;
    const int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_SHAREDCACHE;
    const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
    enum STATE {CONNECTING, READY, DONE};
    bool CONSTRUCTING_PRIVILEGES = false;
    
    typedef struct StatementBlueprint {
        char* source;
        int length;
        sqlite3* db;
    } StatementBlueprint;
    
    class Database : public Nan::ObjectWrap {
        public:
            Database(char*);
            ~Database();
            static NAN_MODULE_INIT(Init);
            
            friend class OpenWorker;
            friend class CloseWorker;
            
        private:
            static CONSTRUCTOR(constructor);
            static NAN_METHOD(New);
            static NAN_GETTER(OpenGetter);
            static NAN_METHOD(Close);
            static NAN_METHOD(PrepareTransaction);
            static NAN_METHOD(PrepareStatement);
            
            char* filename;
            sqlite3* readHandle;
            sqlite3* writeHandle;
            STATE state;
            unsigned int pendings;
    };
    
    class Statement : public Nan::ObjectWrap {
        public:
            Statement();
            ~Statement();
            static void Init();
            
            friend class Database;
            friend class RunWorker;
            
        private:
            static CONSTRUCTOR(constructor);
            static NAN_METHOD(New);
            static NAN_METHOD(Run);
            
            sqlite3_stmt* handle;
            StatementBlueprint blueprint;
            bool readonly;
            bool running;
            // int bound;
            bool dead;
    };
    
    class Transaction : public Nan::ObjectWrap {
        public:
            Transaction();
            ~Transaction();
            static void Init();
            
            friend class Database;
            
        private:
            static CONSTRUCTOR(constructor);
            static NAN_METHOD(New);
            
            bool dead;
    };
    
    class OpenWorker : public Nan::AsyncWorker {
        public:
            OpenWorker(Database*);
            ~OpenWorker();
            void Execute();
            void HandleOKCallback();
            void HandleErrorCallback();
        private:
            Database* db;
    };
    
    class CloseWorker : public Nan::AsyncWorker {
        public:
            CloseWorker(Database*, bool);
            ~CloseWorker();
            void Execute();
            void HandleOKCallback();
            void HandleErrorCallback();
        private:
            Database* db;
            bool doNothing;
    };
    
    class RunWorker : public Nan::AsyncWorker {
        public:
            RunWorker(Statement*);
            ~RunWorker();
            void Execute();
            void HandleOKCallback();
            void HandleErrorCallback();
        private:
            Statement* stmt;
            int changes;
            sqlite3_int64 id;
    };
    
    
    
    
    Database::Database(char* filename) : Nan::ObjectWrap(),
        filename(filename),
        readHandle(NULL),
        writeHandle(NULL),
        state(CONNECTING),
        pendings(0) {}
    Database::~Database() {
        state = DONE;
        sqlite3_close(readHandle);
        sqlite3_close(writeHandle);
        readHandle = NULL;
        writeHandle = NULL;
        free(filename);
        filename = NULL;
    }
    NAN_MODULE_INIT(Database::Init) {
        Nan::HandleScope scope;
        
        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(Nan::New("Database").ToLocalChecked());
        
        Nan::SetPrototypeMethod(t, "disconnect", Close);
        Nan::SetPrototypeMethod(t, "prepare", PrepareStatement);
        Nan::SetPrototypeMethod(t, "begin", PrepareTransaction);
        Nan::SetAccessor(t->InstanceTemplate(), Nan::New("connected").ToLocalChecked(), OpenGetter);
        
        constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
        Nan::Set(target, Nan::New("Database").ToLocalChecked(),
            Nan::GetFunction(t).ToLocalChecked());
    }
    CONSTRUCTOR(Database::constructor);
    NAN_METHOD(Database::New) {
        REQUIRE_ARGUMENTS(1);
        if (!info.IsConstructCall()) {
            v8::Local<v8::Value> args[1] = {info[0]};
            v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
            info.GetReturnValue().Set(cons->NewInstance(1, args));
        } else {
            REQUIRE_ARGUMENT_STRING(0, filename);
            
            Database* db = new Database(RAW_STRING(filename));
            db->Wrap(info.This());
            
            db->Ref();
            AsyncQueueWorker(new OpenWorker(db));
            
            info.GetReturnValue().Set(info.This());
        }
    }
    NAN_GETTER(Database::OpenGetter) {
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        info.GetReturnValue().Set(db->state == READY);
    }
    NAN_METHOD(Database::Close) {
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        
        if (db->state != DONE) {
            db->Ref();
            // --
            // This should wait in queue for all pending transactions to finish. (writes AND reads).
            // This should be invoked right away if there are no pending transactions (which will
            // always be the case if it's still connecting). db->state == DONE simply means that it
            // was READY when Close was invoked, and therefore should be treated equally, as shown
            // below.
            AsyncQueueWorker(new CloseWorker(db, db->state == CONNECTING));
            // --
            db->state = DONE;
        }
        
        info.GetReturnValue().Set(info.This());
    }
    NAN_METHOD(Database::PrepareStatement) {
        REQUIRE_ARGUMENT_STRING(0, source);
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(Statement::constructor);
        
        CONSTRUCTING_PRIVILEGES = true;
        v8::Local<v8::Object> statement = cons->NewInstance(0, NULL);
        CONSTRUCTING_PRIVILEGES = false;
        
        // Invokes String.prototype.trim on the input string.
        v8::Local<v8::StringObject> str = Nan::New<v8::StringObject>(source);
        INVOKE_METHOD(trimmedSource, str, "trim", 0, NULL);
        if (!trimmedSource->IsString()) {
            return Nan::ThrowTypeError("Expected String.prototype.trim to return a string.");
        } else {
            source = v8::Local<v8::String>::Cast(trimmedSource);
        }
        
        // Exposes public properties.
        Nan::ForceSet(statement, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
        Nan::ForceSet(statement, Nan::New("source").ToLocalChecked(), source, FROZEN);
        
        // Builds actual sqlite3_stmt.
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(statement);
        
        Nan::Utf8String utf8(source);
        const char* utf8_value = *utf8;
        const int utf8_len = utf8.length();
        
        const char* tail;
        int status = sqlite3_prepare_v2(db->readHandle, utf8_value, utf8_len, &stmt->handle, &tail);
        
        // Validates the sqlite3_stmt.
        if (status != SQLITE_OK) {
            CONCAT3(message, "Failed to construct the SQL statement. (", sqlite3_errmsg(db->readHandle), ")");
            return Nan::ThrowError(message);
        }
        if (stmt->handle == NULL) {
            return Nan::ThrowError("The supplied SQL query contains no statements.");
        }
        if (tail != utf8_value + utf8_len) {
            return Nan::ThrowError("The db.prepare() method only accepts a single SQL statement.");
        }
        
        // Stores a blueprint of the sqlite3_stmt.
        stmt->blueprint = (StatementBlueprint) {
            .source = const_cast<char*>(utf8_value),
            .length = utf8_len,
            .db = db->readHandle
        };
        
        // If the sqlite3_stmt is not read-only, replaces the handle with a proper one.
        if (!sqlite3_stmt_readonly(stmt->handle)) {
            sqlite3_finalize(stmt->handle);
            status = sqlite3_prepare_v2(db->writeHandle, utf8_value, utf8_len, &stmt->handle, NULL);
            if (status != SQLITE_OK) {
                CONCAT3(message, "Failed to construct the SQL statement. (", sqlite3_errmsg(db->writeHandle), ")");
                return Nan::ThrowError(message);
            }
            stmt->blueprint.db = db->writeHandle;
            
            // Exposes whether the statement is read-only or not.
            stmt->readonly = false;
            Nan::ForceSet(statement, Nan::New("readonly").ToLocalChecked(), Nan::False(), FROZEN);
        } else {
            stmt->readonly = true;
            Nan::ForceSet(statement, Nan::New("readonly").ToLocalChecked(), Nan::True(), FROZEN);
        }
        
        info.GetReturnValue().Set(statement);
    }
    NAN_METHOD(Database::PrepareTransaction) {
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(Transaction::constructor);
        
        CONSTRUCTING_PRIVILEGES = true;
        v8::Local<v8::Object> transaction = cons->NewInstance(0, NULL);
        CONSTRUCTING_PRIVILEGES = false;
        
        Nan::ForceSet(transaction, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
        
        info.GetReturnValue().Set(transaction);
    }
    
    
    
    
    
    Statement::Statement() : Nan::ObjectWrap(),
        running(false),
        // bound(0),
        dead(false) {}
    Statement::~Statement() {
        dead = true;
        sqlite3_finalize(handle);
        handle = NULL;
    }
    void Statement::Init() {
        Nan::HandleScope scope;
        
        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(Nan::New("Statement").ToLocalChecked());
        
        Nan::SetPrototypeMethod(t, "run", Run);
        
        constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
    }
    CONSTRUCTOR(Statement::constructor);
    NAN_METHOD(Statement::New) {
        if (!CONSTRUCTING_PRIVILEGES) {
            return Nan::ThrowTypeError("Statements can only be constructed by the db.prepare() method.");
        }
        Statement* statement = new Statement();
        statement->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    NAN_METHOD(Statement::Run) {
        Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
        if (stmt->readonly) {
            return Nan::ThrowTypeError("This Statement is readonly. Use get(), all(), or forEach() instead.");
        }
        if (stmt->running) {
            return Nan::ThrowError("This statement is already running.");
        }
        
        v8::MaybeLocal<v8::Promise::Resolver> maybeResolver = v8::Promise::Resolver::New(Nan::GetCurrentContext());
        if (maybeResolver.IsEmpty()) {
            return Nan::ThrowError("Failed to create a Promise.");
        }
        v8::Local<v8::Promise::Resolver> resolver = maybeResolver.ToLocalChecked();
        
        RunWorker* worker = new RunWorker(stmt);
        worker->SaveToPersistent((uint32_t)0, resolver);
        
        stmt->running = true;
        stmt->Ref();
        AsyncQueueWorker(worker);
        
        info.GetReturnValue().Set(resolver->GetPromise());
    }
    // bool Statement::Bind(int argc, v8::Local<v8::Value>* argv[]) {
    //     Nan::HandleScope scope;
    //     if (argc == 0) {
    //         return true;
    //     }
    //     if (bound == 2) {
    //         Nan::ThrowTypeError("Cannot pass parameters to a statement that was constructed with bound parameters.");
    //         return false;
    //     }
    //     if (bound == 1) {
    //         // Is this safe for statements that are being run?
    //         sqlite3_reset(handle);
    //         sqlite3_clear_bindings(handle);
    //     }
        
    //     // bind here
    //     // return false if throwing an error
        
    //     if (bound == 0) {
    //         bound = 1;
    //     }
    //     return true;
    // }
    
    
    
    
    
    Transaction::Transaction() : Nan::ObjectWrap(),
        dead(false) {}
    Transaction::~Transaction() {
        dead = true;
    }
    void Transaction::Init() {
        Nan::HandleScope scope;
        
        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(Nan::New("Transaction").ToLocalChecked());
        
        constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
    }
    CONSTRUCTOR(Transaction::constructor);
    NAN_METHOD(Transaction::New) {
        if (!CONSTRUCTING_PRIVILEGES) {
            return Nan::ThrowTypeError("Transactions can only be constructed by the db.begin() method.");
        }
        Transaction* trans = new Transaction();
        trans->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    
    
    
    
    
    OpenWorker::OpenWorker(Database* db)
        : Nan::AsyncWorker(NULL), db(db) {}
    OpenWorker::~OpenWorker() {}
    void OpenWorker::Execute() {
        int status;
        
        status = sqlite3_open_v2(db->filename, &db->writeHandle, WRITE_MODE, NULL);
        if (status != SQLITE_OK) {
            SetErrorMessage(sqlite3_errmsg(db->writeHandle));
            sqlite3_close(db->writeHandle);
            db->writeHandle = NULL;
            return;
        }
        
        status = sqlite3_open_v2(db->filename, &db->readHandle, READ_MODE, NULL);
        if (status != SQLITE_OK) {
            SetErrorMessage(sqlite3_errmsg(db->readHandle));
            sqlite3_close(db->writeHandle);
            sqlite3_close(db->readHandle);
            db->writeHandle = NULL;
            db->readHandle = NULL;
            return;
        }
        
        sqlite3_busy_timeout(db->writeHandle, 30000);
        sqlite3_busy_timeout(db->readHandle, 30000);
    }
    void OpenWorker::HandleOKCallback() {
        Nan::HandleScope scope;
        if (db->state == DONE) {
            sqlite3_close(db->writeHandle);
            sqlite3_close(db->readHandle);
            db->writeHandle = NULL;
            db->readHandle = NULL;
        } else {
            db->state = READY;
            v8::Local<v8::Value> args[1] = {Nan::New("connect").ToLocalChecked()};
            EMIT_EVENT(db->handle(), 1, args);
        }
        db->Unref();
    }
    void OpenWorker::HandleErrorCallback() {
        Nan::HandleScope scope;
        if (db->state != DONE) {
            db->state = DONE;
            v8::Local<v8::Value> args[2] = {
                Nan::New("disconnect").ToLocalChecked(),
                v8::Exception::Error(Nan::New<v8::String>(ErrorMessage()).ToLocalChecked())
            };
            EMIT_EVENT(db->handle(), 2, args);
        }
        db->Unref();
    }
    
    
    
    
    
    CloseWorker::CloseWorker(Database* db, bool doNothing)
        : Nan::AsyncWorker(NULL), db(db), doNothing(doNothing) {}
    CloseWorker::~CloseWorker() {}
    void CloseWorker::Execute() {
        if (!doNothing) {
            // Finalize all statements (sqlite3_next_stmt?)
            int status1 = sqlite3_close(db->writeHandle);
            int status2 = sqlite3_close(db->readHandle);
            db->writeHandle = NULL;
            db->readHandle = NULL;
            if (status1 != SQLITE_OK) {
                SetErrorMessage(sqlite3_errmsg(db->writeHandle));
            } else if (status2 != SQLITE_OK) {
                SetErrorMessage(sqlite3_errmsg(db->readHandle));
            }
        }
    }
    void CloseWorker::HandleOKCallback() {
        Nan::HandleScope scope;
        v8::Local<v8::Value> args[2] = {Nan::New("disconnect").ToLocalChecked(), Nan::Null()};
        EMIT_EVENT(db->handle(), 2, args);
        db->Unref();
    }
    void CloseWorker::HandleErrorCallback() {
        Nan::HandleScope scope;
        v8::Local<v8::Value> args[2] = {
            Nan::New("disconnect").ToLocalChecked(),
            v8::Exception::Error(Nan::New<v8::String>(ErrorMessage()).ToLocalChecked())
        };
        EMIT_EVENT(db->handle(), 2, args);
        db->Unref();
    }
    
    
    
    
    
    RunWorker::RunWorker(Statement* stmt)
        : Nan::AsyncWorker(NULL), stmt(stmt) {}
    RunWorker::~RunWorker() {}
    void RunWorker::Execute() {
        int status = sqlite3_step(stmt->handle);
        if (status == SQLITE_DONE) {
            changes = sqlite3_changes(stmt->blueprint.db);
            id = sqlite3_last_insert_rowid(stmt->blueprint.db);
        } else {
            SetErrorMessage(sqlite3_errmsg(stmt->blueprint.db));
        }
        sqlite3_reset(stmt->handle);
    }
    void RunWorker::HandleOKCallback() {
        Nan::HandleScope scope;
        stmt->running = false;
        
        v8::Local<v8::Object> obj = Nan::New<v8::Object>();
        Nan::ForceSet(obj, Nan::New("changes").ToLocalChecked(), Nan::New<v8::Number>((double)changes));
        Nan::ForceSet(obj, Nan::New("id").ToLocalChecked(), Nan::New<v8::Number>((double)id));
        
        v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(GetFromPersistent((uint32_t)0));
        resolver->Resolve(Nan::GetCurrentContext(), obj);
        stmt->Unref();
    }
    void RunWorker::HandleErrorCallback() {
        Nan::HandleScope scope;
        stmt->running = false;
        
        CONCAT2(message, "SQLite: ", ErrorMessage());
        
        v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(GetFromPersistent((uint32_t)0));
        resolver->Reject(Nan::GetCurrentContext(), v8::Exception::Error(message));
        stmt->Unref();
    }
    
    
    
    
    
    NAN_MODULE_INIT(InitDatabase) {
        Database::Init(target);
        Statement::Init();
        Transaction::Init();
    }
}
