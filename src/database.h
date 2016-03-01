#ifndef NODE_SQLITE3_PLUS_DATABASE_H
#define NODE_SQLITE3_PLUS_DATABASE_H

#include <sqlite3.h>
#include <nan.h>
#include "macros.h"

class Database : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);
        
    private:
        Database() : Nan::ObjectWrap(),
            readHandle(NULL),
            writeHandle(NULL),
            open(false) {
        }
        
        ~Database() {
            sqlite3_close(readHandle);
            sqlite3_close(writeHandle);
            readHandle = NULL;
            writeHandle = NULL;
            open = false;
        }
        
        static Nan::Persistent<v8::Function> constructor;
        
        static NAN_GETTER(OpenGetter);
        
        static NAN_METHOD(New);
        // static void Work_BeginOpen(Baton* baton);
        // static void Work_Open(uv_work_t* req);
        // static void Work_AfterOpen(uv_work_t* req);
        
        static NAN_METHOD(Close);
        // static void Work_BeginClose(Baton* baton);
        // static void Work_Close(uv_work_t* req);
        // static void Work_AfterClose(uv_work_t* req);
        
        sqlite3* readHandle;
        sqlite3* writeHandle;
        bool open;
};

#endif
