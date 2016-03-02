#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "database.h"

namespace DATABASE {
    int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX;
    int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX;
    
    class Database : public Nan::ObjectWrap {
        public:
            Database() : Nan::ObjectWrap(),
                readHandle(NULL),
                writeHandle(NULL),
                open(false) {}
            ~Database() {
                sqlite3_close(readHandle);
                sqlite3_close(writeHandle);
                readHandle = NULL;
                writeHandle = NULL;
                open = false;
            }
            static NAN_MODULE_INIT(Init) {
                Nan::HandleScope scope;
                
                v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
                t->InstanceTemplate()->SetInternalFieldCount(1);
                t->SetClassName(Nan::New("Database").ToLocalChecked());
                
                Nan::SetPrototypeMethod(t, "close", Close);
                Nan::SetAccessor(t->InstanceTemplate(), Nan::New("open").ToLocalChecked(), OpenGetter);
                
                constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
                Nan::Set(target, Nan::New("Database").ToLocalChecked(),
                    Nan::GetFunction(t).ToLocalChecked());
            }
            static CONSTRUCTOR(constructor);
            
        private:
            static NAN_METHOD(New) {
                REQUIRE_ARGUMENTS(1);
                if (!info.IsConstructCall()) {
                    v8::Local<v8::Value> args[] = {info[0], Nan::Undefined()};
                    if (info.Length() > 1) {args[1] = info[1];}
                    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
                    info.GetReturnValue().Set(cons->NewInstance(2, args));
                } else {
                    REQUIRE_ARGUMENT_STRING(0, filename);
                    OPTIONAL_ARGUMENT_FUNCTION(1, callback);
                    
                    Database* db = new Database();
                    db->Wrap(info.This());
                    
                    v8::Local<v8::Value> args[] = {info[0]};
                    // Use Nan::MakeCallback() for I/O based callbacks (i.e., not synchronous from JS code)
                    if (!callback.IsEmpty()) {
                        callback->Call(info.This(), 1, args);
                    }
                    
                    info.GetReturnValue().Set(info.This());
                }
            }
            
            static NAN_GETTER(OpenGetter) {
                Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
                info.GetReturnValue().Set(db->open);
            }
            static NAN_METHOD(Close) {
                // Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
                
                OPTIONAL_ARGUMENT_FUNCTION(0, callback);
                if (!callback.IsEmpty()) {
                    callback->Call(info.This(), 0, NULL);
                }
                
                info.GetReturnValue().Set(info.This());
            }
            
            sqlite3* readHandle;
            sqlite3* writeHandle;
            bool open;
    };
    CONSTRUCTOR(Database::constructor);
    
    // void Database::Work_BeginOpen(Baton* baton) {
    //     int status = uv_queue_work(uv_default_loop(),
    //         &baton->request, Work_Open, (uv_after_work_cb)Work_AfterOpen);
    //     assert(status == 0);
    // }
    
    // void Database::Work_Open(uv_work_t* req) {
    //     OpenBaton* baton = static_cast<OpenBaton*>(req->data);
    //     Database* db = baton->db;

    //     baton->status = sqlite3_open_v2(
    //         baton->filename.c_str(),
    //         &db->_handle,
    //         baton->mode,
    //         NULL
    //     );

    //     if (baton->status != SQLITE_OK) {
    //         baton->message = std::string(sqlite3_errmsg(db->_handle));
    //         sqlite3_close(db->_handle);
    //         db->_handle = NULL;
    //     }
    //     else {
    //         // Set default database handle values.
    //         sqlite3_busy_timeout(db->_handle, 1000);
    //     }
    // }

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
