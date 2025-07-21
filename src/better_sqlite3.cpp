#include <climits>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <mutex>
#include <sqlite3.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_buffer.h>

struct Addon;
class Database;
class Statement;
class StatementIterator;
class Backup;

#include "util/macros.cpp"
#include "util/helpers.cpp"
#include "util/constants.cpp"
#include "util/bind-map.cpp"
#include "util/data-converter.cpp"
#include "util/data.cpp"
#if defined(NODE_MODULE_VERSION) && NODE_MODULE_VERSION >= 127
#include "util/row-builder.cpp"
#endif

#include "objects/backup.hpp"
#include "objects/statement.hpp"
#include "objects/database.hpp"
#include "addon.cpp"
#include "objects/statement-iterator.hpp"

#include "util/query-macros.cpp"
#include "util/custom-function.cpp"
#include "util/custom-aggregate.cpp"
#include "util/custom-table.cpp"
#include "util/binder.cpp"

#include "objects/backup.cpp"
#include "objects/statement.cpp"
#include "objects/database.cpp"
#include "objects/statement-iterator.cpp"

NODE_MODULE_INIT(/* exports, context */) {
	v8::Isolate* isolate = context->GetIsolate();
	v8::HandleScope scope(isolate);
	Addon::ConfigureURI();

	// Initialize addon instance.
	Addon* addon = new Addon(isolate);
	v8::Local<v8::External> data = v8::External::New(isolate, addon);
	node::AddEnvironmentCleanupHook(isolate, Addon::Cleanup, addon);

	// Create and export native-backed classes and functions.
	exports->Set(context, InternalizedFromLatin1(isolate, "Database"), Database::Init(isolate, data)).FromJust();
	exports->Set(context, InternalizedFromLatin1(isolate, "Statement"), Statement::Init(isolate, data)).FromJust();
	exports->Set(context, InternalizedFromLatin1(isolate, "StatementIterator"), StatementIterator::Init(isolate, data)).FromJust();
	exports->Set(context, InternalizedFromLatin1(isolate, "Backup"), Backup::Init(isolate, data)).FromJust();
	exports->Set(context, InternalizedFromLatin1(isolate, "setErrorConstructor"), v8::FunctionTemplate::New(isolate, Addon::JS_setErrorConstructor, data)->GetFunction(context).ToLocalChecked()).FromJust();

	// Store addon instance data.
	addon->Statement.Reset(isolate, exports->Get(context, InternalizedFromLatin1(isolate, "Statement")).ToLocalChecked().As<v8::Function>());
	addon->StatementIterator.Reset(isolate, exports->Get(context, InternalizedFromLatin1(isolate, "StatementIterator")).ToLocalChecked().As<v8::Function>());
	addon->Backup.Reset(isolate, exports->Get(context, InternalizedFromLatin1(isolate, "Backup")).ToLocalChecked().As<v8::Function>());
}
