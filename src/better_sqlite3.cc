#include <nan.h>
#include "objects/int64/int64.h"
#include "objects/database/database.h"
#include "objects/statement/statement.h"
#include "objects/transaction/transaction.h"

void RegisterModule(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
	v8HandleScope;
	
	Int64::Init(exports, module);
	Database::Init(exports, module);
	Statement::Init();
	Transaction::Init();
}
NODE_MODULE(better_sqlite3, RegisterModule);
