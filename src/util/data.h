#ifndef BETTER_SQLITE3_DATA_H
#define BETTER_SQLITE3_DATA_H

#include <sqlite3.h>
class Functor;

namespace Data {

v8::Local<v8::Value> GetValueJS(sqlite3_stmt*, int, bool);
v8::Local<v8::Value> GetRowJS(sqlite3_stmt*, bool);
v8::Local<v8::Value>* GetArgumentsJS(sqlite3_value**, int, bool);
int BindValueFromJS(sqlite3_stmt*, int, v8::Local<v8::Value>);
void ResultValueFromJS(sqlite3_context*, v8::Local<v8::Value>, Functor*);

}

#endif