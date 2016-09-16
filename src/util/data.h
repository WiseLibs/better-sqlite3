#ifndef BETTER_SQLITE3_DATA_H
#define BETTER_SQLITE3_DATA_H

#include <sqlite3.h>

namespace Data {

v8::Local<v8::Value> GetIntegerJS(sqlite3_stmt*, int);
v8::Local<v8::Value> GetFloatJS(sqlite3_stmt*, int);
v8::Local<v8::Value> GetTextJS(sqlite3_stmt*, int);
v8::Local<v8::Value> GetBlobJS(sqlite3_stmt*, int);
v8::Local<v8::Value> GetValueJS(sqlite3_stmt*, int);
v8::Local<v8::Value> GetRowJS(sqlite3_stmt*, int);

}

#endif