#include <nan.h>
#include "database.h"

namespace NODE_SQLITE3_PLUS {
    NAN_MODULE_INIT(RegisterModule) {
        Nan::HandleScope scope;
        NODE_SQLITE3_PLUS_DATABASE::InitDatabase(target);
    }
    NODE_MODULE(sqlite3_plus, RegisterModule);
}
