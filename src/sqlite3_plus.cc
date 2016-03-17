#include <nan.h>
#include "objects/database/database.h"
#include "objects/statement/statement.h"
#include "objects/transaction/transaction.h"

NAN_MODULE_INIT(RegisterModule) {
	Nan::HandleScope scope;
	
	Database::Init(target);
	Statement::Init();
	Transaction::Init();
}
NODE_MODULE(sqlite3_plus, RegisterModule);
