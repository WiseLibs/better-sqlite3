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
            
        private:
            static NAN_METHOD(New);
            static NAN_GETTER(OpenGetter);
            static NAN_METHOD(Close);
            
            char* filename;
            sqlite3* readHandle;
            sqlite3* writeHandle;
            bool open;
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
    
    
    
    
    
    Database::Database(char* filename) : Nan::ObjectWrap(),
        filename(filename),
        readHandle(NULL),
        writeHandle(NULL),
        open(false) {}
    Database::~Database() {
        sqlite3_close(readHandle);
        sqlite3_close(writeHandle);
        readHandle = NULL;
        writeHandle = NULL;
        open = false;
        delete filename;
        filename = NULL;
    }
    NAN_MODULE_INIT(Database::Init) {
        Nan::HandleScope scope;
        
        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(Nan::New("Database").ToLocalChecked());
        
        Nan::SetPrototypeMethod(t, "close", Close);
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
            
            Database* db = new Database(*filename);
            db->Wrap(info.This());
            
            AsyncQueueWorker(new OpenWorker(db));
            
            info.GetReturnValue().Set(info.This());
        }
    }
    NAN_GETTER(Database::OpenGetter) {
        Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        info.GetReturnValue().Set(db->open);
    }
    NAN_METHOD(Database::Close) {
        // Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
        
        OPTIONAL_ARGUMENT_FUNCTION(0, callback);
        if (!callback.IsEmpty()) {
            callback->Call(info.This(), 0, NULL);
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
        
        sqlite3_busy_timeout(db->writeHandle, 5000);
        sqlite3_busy_timeout(db->readHandle, 5000);
    }
    void OpenWorker::HandleOKCallback() {
        Nan::HandleScope scope;
        db->open = true;
        v8::Local<v8::Value> args[1] = {Nan::New("connect").ToLocalChecked()};
        EMIT_EVENT(db->handle(), 1, args);
    }
    void OpenWorker::HandleErrorCallback() {
        Nan::HandleScope scope;
        v8::Local<v8::Value> args[2] = {
            Nan::New("disconnect").ToLocalChecked(),
            v8::Exception::Error(Nan::New<v8::String>(ErrorMessage()).ToLocalChecked())
        };
        EMIT_EVENT(db->handle(), 2, args);
    }
    
    
    
    
    
    
    
    
    
    
    
    
    

    // void Database::Work_AfterOpen(uv_work_t* req) {
    //     Nan::HandleScope scope;

    //     OpenBaton* baton = static_cast<OpenBaton*>(req->data);
    //     Database* db = baton->db;

    //     Local<Value> argv[1];
    //     if (baton->status != SQLITE_OK) {
    //         EXCEPTION(Nan::New(baton->message.c_str()).ToLocalChecked(), baton->status, exception);
    //         argv[0] = exception;
    //     }
    //     else {
    //         db->open = true;
    //         argv[0] = Nan::Null();
    //     }

    //     Local<Function> cb = Nan::New(baton->callback);

    //     if (!cb.IsEmpty() && cb->IsFunction()) {
    //         Nan::MakeCallback(db->handle(), cb, 1, argv);
    //     }
    //     else if (!db->open) {
    //         Local<Value> info[] = { Nan::New("error").ToLocalChecked(), argv[0] };
    //         EMIT_EVENT(db->handle(), 2, info);
    //     }

    //     if (db->open) {
    //         Local<Value> info[] = { Nan::New("open").ToLocalChecked() };
    //         EMIT_EVENT(db->handle(), 1, info);
    //         db->Process();
    //     }

    //     delete baton;
    // }
    
    
    
    // void Database::Work_BeginClose(Baton* baton) {
    //     assert(baton->db->locked);
    //     assert(baton->db->open);
    //     assert(baton->db->_handle);
    //     assert(baton->db->pending == 0);

    //     baton->db->RemoveCallbacks();
    //     int status = uv_queue_work(uv_default_loop(),
    //         &baton->request, Work_Close, (uv_after_work_cb)Work_AfterClose);
    //     assert(status == 0);
    // }
    
    // void Database::Work_Close(uv_work_t* req) {
    //     Baton* baton = static_cast<Baton*>(req->data);
    //     Database* db = baton->db;

    //     baton->status = sqlite3_close(db->_handle);

    //     if (baton->status != SQLITE_OK) {
    //         baton->message = std::string(sqlite3_errmsg(db->_handle));
    //     }
    //     else {
    //         db->_handle = NULL;
    //     }
    // }
    
    // void Database::Work_AfterClose(uv_work_t* req) {
    //     Nan::HandleScope scope;

    //     Baton* baton = static_cast<Baton*>(req->data);
    //     Database* db = baton->db;

    //     Local<Value> argv[1];
    //     if (baton->status != SQLITE_OK) {
    //         EXCEPTION(Nan::New(baton->message.c_str()).ToLocalChecked(), baton->status, exception);
    //         argv[0] = exception;
    //     }
    //     else {
    //         db->open = false;
    //         // Leave db->locked to indicate that this db object has reached
    //         // the end of its life.
    //         argv[0] = Nan::Null();
    //     }
    
    //     Local<Function> cb = Nan::New(baton->callback);
    
    //     // Fire callbacks.
    //     if (!cb.IsEmpty() && cb->IsFunction()) {
    //         Nan::MakeCallback(db->handle(), cb, 1, argv);
    //     }
    //     else if (db->open) {
    //         Local<Value> info[] = { Nan::New("error").ToLocalChecked(), argv[0] };
    //         EMIT_EVENT(db->handle(), 2, info);
    //     }
    
    //     if (!db->open) {
    //         Local<Value> info[] = { Nan::New("close").ToLocalChecked(), argv[0] };
    //         EMIT_EVENT(db->handle(), 1, info);
    //         db->Process();
    //     }
    
    //     delete baton;
    // }
    
    NAN_MODULE_INIT(InitDatabase) {
        Database::Init(target);
    }
}
