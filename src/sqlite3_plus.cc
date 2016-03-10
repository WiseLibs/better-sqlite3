#include <nan.h>
#include "database.h"
#include "statement.h"
#include "transaction.h"

NAN_MODULE_INIT(RegisterModule) {
    Nan::HandleScope scope;
    
    Database::Init(target);
    Statement::Init();
    Transaction::Init();
}
NODE_MODULE(sqlite3_plus, RegisterModule);
