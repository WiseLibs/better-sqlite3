#include <nan.h>
#include "objects/database/database.h"
#include "objects/statement/statement.h"
#include "objects/transaction/transaction.h"

void RegisterModule(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
	Nan::HandleScope scope;
	
	Database::Init(exports, module);
	Statement::Init();
	Transaction::Init();
}
NODE_MODULE(better_sqlite3, RegisterModule);
