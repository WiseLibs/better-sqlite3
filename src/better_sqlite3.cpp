#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <random>
#include <unordered_map>
#include <algorithm>
#include <mutex>
#include <sqlite3.h>
#include <napi.h>

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

#include "util/row-builder.hpp"
#include "objects/backup.hpp"
#include "objects/statement.hpp"
#include "objects/database.hpp"
#include "addon.cpp"
#include "objects/statement-iterator.hpp"

#include "util/data.cpp"
#include "util/row-builder.cpp"
#include "util/query-macros.cpp"
#include "util/custom-function.cpp"
#include "util/custom-aggregate.cpp"
#include "util/custom-table.cpp"
#include "util/binder.cpp"

#include "objects/backup.cpp"
#include "objects/statement.cpp"
#include "objects/database.cpp"
#include "objects/statement-iterator.cpp"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	Napi::HandleScope scope(env);
	Addon::ConfigureURI();

	// Initialize addon instance. The addon is bound to each native-backed class
	// as callback data (rather than per-environment instance data) so that
	// multiple copies of the addon can be loaded into a single environment.
	Addon* addon = new Addon(env);
	env.AddCleanupHook(Addon::Cleanup, addon);

	// Create and export native-backed classes and functions.
	exports.Set("Database", Database::Init(env, addon));
	exports.Set("Statement", Statement::Init(env, addon));
	exports.Set("StatementIterator", StatementIterator::Init(env, addon));
	exports.Set("Backup", Backup::Init(env, addon));
	exports.Set("initialize", Napi::Function::New(env, Addon::JS_initialize, "initialize", addon));

	// Store addon instance data.
	addon->Statement = Napi::Persistent(exports.Get("Statement").As<Napi::Function>());
	addon->StatementIterator = Napi::Persistent(exports.Get("StatementIterator").As<Napi::Function>());
	addon->Backup = Napi::Persistent(exports.Get("Backup").As<Napi::Function>());

	return exports;
}

NODE_API_MODULE(better_sqlite3, InitAll)
