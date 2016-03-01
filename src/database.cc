#include "database.h"

static int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX;
static int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX;

NAN_MODULE_INIT(Database::Init) {
    Nan::HandleScope scope;
    
    v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
    
    t->InstanceTemplate()->SetInternalFieldCount(1);
    t->SetClassName(Nan::New("Database").ToLocalChecked());
    
    Nan::SetPrototypeMethod(t, "close", Close);
    
    Nan::SetAccessor(t->InstanceTemplate(),
        Nan::New("open").ToLocalChecked(), OpenGetter);
    
    v8::Local<v8::Function> fn = Nan::GetFunction(t).ToLocalChecked();
    constructor.Reset(fn);
    Nan::Set(target, Nan::New("Database").ToLocalChecked(), fn);
}

NAN_METHOD(Database::New) {
    if (!info.IsConstructCall()) {
        v8::Local<v8::Value> argv[1] = {info[0]};
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        info.GetReturnValue().Set(cons->NewInstance(1, argv));
    } else {
        REQUIRE_ARGUMENT_STRING(0, filename);
        OPTIONAL_ARGUMENT_CALLBACK(1, callback);
        
        v8::Local<v8::Value> args[] = {info[0]};
        callback.Call(1, args);
        
        Database* db = new Database();
        db->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    
    // info.This()->ForceSet(Nan::New("filename").ToLocalChecked(), info[0].As<String>(), ReadOnly);
    // info.This()->ForceSet(Nan::New("mode").ToLocalChecked(), Nan::New(mode), ReadOnly);
    
    // // Start opening the database.
    // OpenBaton* baton = new OpenBaton(db, callback, *filename, mode);
    // Work_BeginOpen(baton);
}

NAN_GETTER(Database::OpenGetter) {
    Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
    info.GetReturnValue().Set(db->open);
}

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

NAN_METHOD(Database::Close) {
    // Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
    
    OPTIONAL_ARGUMENT_CALLBACK(0, callback);
    callback.Call(0, NULL);
    
    info.GetReturnValue().Set(info.This());
}

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

