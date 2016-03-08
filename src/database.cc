#include <cstdlib>
#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "database.h"

namespace NODE_SQLITE3_PLUS_DATABASE {
    int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX;
    int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX;
    v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
    enum STATE {CONNECTING, READY, DONE};
    bool CONSTRUCTING_PRIVILEGES = false;
    
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
            static NAN_METHOD(PrepareWriteQuery);
            static NAN_METHOD(PrepareReadQuery);
            
            char* filename;
            sqlite3* readHandle;
            sqlite3* writeHandle;
            STATE state;
            unsigned int pendings;
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
    
    class WriteQuery : public Nan::ObjectWrap {
        public:
            WriteQuery();
            ~WriteQuery();
            static void Init();
            
            friend class Database;
            
        private:
            static CONSTRUCTOR(constructor);
            static NAN_METHOD(New);
            
            sqlite3_stmt* handle;
            bool dead;
    };
    
    class ReadQuery : public Nan::ObjectWrap {
        public:
            ReadQuery();
            ~ReadQuery();
            static void Init();
            
            friend class Database;
            
        private:
            static CONSTRUCTOR(constructor);
            static NAN_METHOD(New);
            
            sqlite3_stmt* handle;
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
        Nan::SetPrototypeMethod(t, "begin", PrepareTransaction);
        Nan::SetPrototypeMethod(t, "write", PrepareWriteQuery);
        Nan::SetPrototypeMethod(t, "read", PrepareReadQuery);
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
    NAN_METHOD(Database::PrepareTransaction) {
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(Transaction::constructor);
        
        CONSTRUCTING_PRIVILEGES = true;
        v8::Local<v8::Object> transaction = cons->NewInstance(0, NULL);
        CONSTRUCTING_PRIVILEGES = false;
        
        Nan::ForceSet(transaction, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
        
        info.GetReturnValue().Set(transaction);
    }
    NAN_METHOD(Database::PrepareWriteQuery) {
        REQUIRE_ARGUMENT_STRING(0, source);
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(WriteQuery::constructor);
        
        CONSTRUCTING_PRIVILEGES = true;
        v8::Local<v8::Object> writeQuery = cons->NewInstance(0, NULL);
        CONSTRUCTING_PRIVILEGES = false;
        
        Nan::ForceSet(writeQuery, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
        Nan::ForceSet(writeQuery, Nan::New("source").ToLocalChecked(), source, FROZEN);
        
        v8::String::Utf8Value utf8(source);
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        WriteQuery* wquery = Nan::ObjectWrap::Unwrap<WriteQuery>(writeQuery);
        int status = sqlite3_prepare_v2(db->writeHandle, *utf8, utf8.length(), &wquery->handle, NULL);
        
        if (status != SQLITE_OK) {
            wquery->handle = NULL;
            wquery->dead = true;
            CONCAT3(message, "Failed to construct the SQL statement. (", sqlite3_errmsg(db->writeHandle), ")");
            return Nan::ThrowError(message);
        }
        if (wquery->handle == NULL) {
            wquery->dead = true;
            return Nan::ThrowError("The supplied SQL query contains no statements.");
        }
        
        info.GetReturnValue().Set(writeQuery);
    }
    NAN_METHOD(Database::PrepareReadQuery) {
        REQUIRE_ARGUMENT_STRING(0, source);
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(ReadQuery::constructor);
        
        CONSTRUCTING_PRIVILEGES = true;
        v8::Local<v8::Object> readQuery = cons->NewInstance(0, NULL);
        CONSTRUCTING_PRIVILEGES = false;
        
        Nan::ForceSet(readQuery, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
        Nan::ForceSet(readQuery, Nan::New("source").ToLocalChecked(), source, FROZEN);
        
        v8::String::Utf8Value utf8(source);
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        ReadQuery* rquery = Nan::ObjectWrap::Unwrap<ReadQuery>(readQuery);
        int status = sqlite3_prepare_v2(db->readHandle, *utf8, utf8.length(), &rquery->handle, NULL);
        
        if (status != SQLITE_OK) {
            rquery->handle = NULL;
            rquery->dead = true;
            CONCAT3(message, "Failed to construct the SQL statement. (", sqlite3_errmsg(db->readHandle), ")");
            return Nan::ThrowError(message);
        }
        if (rquery->handle == NULL) {
            rquery->dead = true;
            return Nan::ThrowError("The supplied SQL query contains no statements.");
        }
        
        info.GetReturnValue().Set(readQuery);
    }
    
    
    
    
    
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
            return Nan::ThrowSyntaxError("Transactions can only be constructed by the db.begin() method.");
        }
        Transaction* trans = new Transaction();
        trans->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    
    
    
    
    
    WriteQuery::WriteQuery() : Nan::ObjectWrap(),
        dead(false) {}
    WriteQuery::~WriteQuery() {
        dead = true;
        sqlite3_finalize(handle);
        handle = NULL;
    }
    void WriteQuery::Init() {
        Nan::HandleScope scope;
        
        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(Nan::New("WriteQuery").ToLocalChecked());
        
        constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
    }
    CONSTRUCTOR(WriteQuery::constructor);
    NAN_METHOD(WriteQuery::New) {
        if (!CONSTRUCTING_PRIVILEGES) {
            return Nan::ThrowSyntaxError("WriteQuerys can only be constructed by the db.write() method.");
        }
        WriteQuery* writeQuery = new WriteQuery();
        writeQuery->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    
    
    
    
    
    ReadQuery::ReadQuery() : Nan::ObjectWrap(),
        dead(false) {}
    ReadQuery::~ReadQuery() {
        dead = true;
        sqlite3_finalize(handle);
        handle = NULL;
    }
    void ReadQuery::Init() {
        Nan::HandleScope scope;
        
        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(Nan::New("ReadQuery").ToLocalChecked());
        
        constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
    }
    CONSTRUCTOR(ReadQuery::constructor);
    NAN_METHOD(ReadQuery::New) {
        if (!CONSTRUCTING_PRIVILEGES) {
            return Nan::ThrowSyntaxError("ReadQuerys can only be constructed by the db.read() method.");
        }
        ReadQuery* readQuery = new ReadQuery();
        readQuery->Wrap(info.This());
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
    
    
    
    
    
    NAN_MODULE_INIT(InitDatabase) {
        Database::Init(target);
        Transaction::Init();
        ReadQuery::Init();
        WriteQuery::Init();
    }
}
