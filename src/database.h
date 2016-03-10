#ifndef NODE_SQLITE3_PLUS_DATABASE_H
#define NODE_SQLITE3_PLUS_DATABASE_H

#include <sqlite3.h>
#include <nan.h>
#include "macros.h"

extern bool CONSTRUCTING_PRIVILEGES;

enum DB_STATE {DB_CONNECTING, DB_READY, DB_DONE};

class Database : public Nan::ObjectWrap {
    public:
        Database();
        ~Database();
        static NAN_MODULE_INIT(Init);
        
        friend class OpenWorker;
        friend class CloseWorker;
        friend class Statement;
        friend class RunWorker;
        
    private:
        static CONSTRUCTOR(constructor);
        static NAN_METHOD(New);
        static NAN_GETTER(OpenGetter);
        static NAN_METHOD(Close);
        static NAN_METHOD(PrepareStatement);
        static NAN_METHOD(PrepareTransaction);
        void ActuallyClose();
        
        sqlite3* readHandle;
        sqlite3* writeHandle;
        DB_STATE state;
        unsigned int requests;
        unsigned int workers;
};

#endif