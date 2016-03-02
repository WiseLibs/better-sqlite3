#include <cstdlib>
#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "database.h"

namespace DATABASE {
    int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX;
    int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX;
    
    class Database : public Nan::ObjectWrap {
        public:
            Database(char*);
            ~Database();
            static NAN_MODULE_INIT(Init);
            static CONSTRUCTOR(constructor);
            
            friend class OpenWorker;
            friend class CloseWorker;
            
        private:
            static NAN_METHOD(New);
            static NAN_GETTER(OpenGetter);
            static NAN_METHOD(Close);
            
            char* filename;
            sqlite3* readHandle;
            sqlite3* writeHandle;
            bool open;
            bool closed;
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
            bool actuallyClose;
    };
    
    
    
    
    
    Database::Database(char* filename) : Nan::ObjectWrap(),
        filename(filename),
        readHandle(NULL),
        writeHandle(NULL),
        open(false),
        closed(false) {}
    Database::~Database() {
        open = false;
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
        info.GetReturnValue().Set(db->open);
    }
    NAN_METHOD(Database::Close) {
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        
        if (!db->closed) {
            db->closed = true;
            // This should wait in queue for all pending transactions to finish. (writes AND reads)
            db->Ref();
            AsyncQueueWorker(new CloseWorker(db, db->open));
            db->open = false;
        }
        
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
        if (db->closed) {
            sqlite3_close(db->writeHandle);
            sqlite3_close(db->readHandle);
            db->writeHandle = NULL;
            db->readHandle = NULL;
        } else {
            db->open = true;
            v8::Local<v8::Value> args[1] = {Nan::New("connect").ToLocalChecked()};
            EMIT_EVENT(db->handle(), 1, args);
        }
        db->Unref();
    }
    void OpenWorker::HandleErrorCallback() {
        Nan::HandleScope scope;
        if (!db->closed) {
            db->closed = true;
            v8::Local<v8::Value> args[2] = {
                Nan::New("disconnect").ToLocalChecked(),
                v8::Exception::Error(Nan::New<v8::String>(ErrorMessage()).ToLocalChecked())
            };
            EMIT_EVENT(db->handle(), 2, args);
        }
        db->Unref();
    }
    
    
    
    
    
    CloseWorker::CloseWorker(Database* db, bool actuallyClose)
        : Nan::AsyncWorker(NULL), db(db), actuallyClose(actuallyClose) {}
    CloseWorker::~CloseWorker() {}
    void CloseWorker::Execute() {
        if (actuallyClose) {
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
    }
}
