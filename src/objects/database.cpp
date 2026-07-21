// Node-API does not expose the engine's maximum Buffer/String sizes, so we
// hardcode V8's known limits: Buffers are larger than what sqlite3_limit can
// express (INT_MAX), and strings are limited to v8::String::kMaxLength, which
// is (1 << 29) - 24 bytes on 64-bit platforms (as of Node.js 22). Keeping
// these limits ensures that oversized values fail cleanly inside SQLite with
// SQLITE_TOOBIG, instead of failing during data conversion.
const int Database::MAX_BUFFER_SIZE = INT_MAX;
const int Database::MAX_STRING_SIZE = (1 << 29) - 24;

const napi_type_tag Database::TYPE_TAG = RandomTypeTag();

Database::Database(const Napi::CallbackInfo& info) :
	Napi::ObjectWrap<Database>(info),
	db_handle(NULL),
	open(false),
	busy(false),
	safe_ints(false),
	unsafe_mode(false),
	was_js_error(false),
	has_logger(false),
	iterators(0),
	addon(static_cast<Addon*>(info.Data())),
	logger(),
	stmts(),
	backups() {
	napi_status status = napi_type_tag_object(info.Env(), info.This(), &TYPE_TAG);
	assert(status == napi_ok); ((void)status);
	JS_new(info);
}

Database::~Database() {
	if (open) addon->dbs.erase(this);
	CloseHandles();
}

// Whenever this is used, addon->dbs.erase() must be invoked beforehand.
void Database::CloseHandles() {
	if (open) {
		open = false;
		for (Statement* stmt : stmts) stmt->CloseHandles();
		for (Backup* backup : backups) backup->CloseHandles();
		stmts.clear();
		backups.clear();
		int status = sqlite3_close(db_handle);
		assert(status == SQLITE_OK); ((void)status);
	}
}

void Database::ThrowDatabaseError(Napi::Env env) {
	if (was_js_error) was_js_error = false;
	else ThrowSqliteError(env, addon, db_handle);
}

void Database::ThrowSqliteError(Napi::Env env, Addon* addon, sqlite3* db_handle) {
	assert(db_handle != NULL);
	ThrowSqliteError(env, addon, sqlite3_errmsg(db_handle), sqlite3_extended_errcode(db_handle));
}

void Database::ThrowSqliteError(Napi::Env env, Addon* addon, const char* message, int code) {
	assert(message != NULL);
	assert((code & 0xff) != SQLITE_OK);
	assert((code & 0xff) != SQLITE_ROW);
	assert((code & 0xff) != SQLITE_DONE);
	Napi::Object error = addon->SqliteError.New({
		StringFromUtf8(env, message, -1),
		addon->cs.Code(env, code)
	});
	// Constructing the SqliteError can itself throw (e.g., if the user's error
	// constructor throws); in that case, let that exception propagate instead
	// of trying to throw a second time.
	if (!env.IsExceptionPending()) {
		Napi::Error(env, error).ThrowAsJavaScriptException();
	}
}

// Allows Statements to log their executed SQL.
bool Database::Log(Napi::Env env, sqlite3_stmt* handle) {
	assert(was_js_error == false);
	if (!has_logger) return false;
	char* expanded = sqlite3_expanded_sql(handle);
	napi_value arg = StringFromUtf8(env, expanded ? expanded : sqlite3_sql(handle), -1);
	SafeCall(env, logger.Value().As<Napi::Function>(), env.Undefined(), 1, &arg);
	was_js_error = env.IsExceptionPending();
	if (expanded) sqlite3_free(expanded);
	return was_js_error;
}

bool Database::Deserialize(
	Napi::Env env,
	Napi::Object buffer,
	Addon* addon,
	sqlite3* db_handle,
	bool readonly
) {
	Napi::Buffer<char> buf = buffer.As<Napi::Buffer<char>>();
	size_t length = buf.Length();
	unsigned char* data = (unsigned char*)sqlite3_malloc64(length);
	unsigned int flags = SQLITE_DESERIALIZE_FREEONCLOSE | SQLITE_DESERIALIZE_RESIZEABLE;

	if (readonly) {
		flags |= SQLITE_DESERIALIZE_READONLY;
	}
	if (length) {
		if (!data) {
			ThrowError(env, "Out of memory");
			return false;
		}
		memcpy(data, buf.Data(), length);
	}

	int status = sqlite3_deserialize(db_handle, "main", data, length, length, flags);
	if (status != SQLITE_OK) {
		ThrowSqliteError(env, addon, status == SQLITE_ERROR ? "unable to deserialize database" : sqlite3_errstr(status), status);
		return false;
	}

	return true;
}

void Database::FreeSerialization(Napi::Env env, char* data) {
	sqlite3_free(data);
}

INIT(Database::Init) {
	return DefineClass(env, "Database", {
		PrototypeMethod<Database, &Database::JS_prepare>("prepare", addon),
		PrototypeMethod<Database, &Database::JS_exec>("exec", addon),
		PrototypeMethod<Database, &Database::JS_backup>("backup", addon),
		PrototypeMethod<Database, &Database::JS_serialize>("serialize", addon),
		PrototypeMethod<Database, &Database::JS_function>("function", addon),
		PrototypeMethod<Database, &Database::JS_aggregate>("aggregate", addon),
		PrototypeMethod<Database, &Database::JS_table>("table", addon),
		PrototypeMethod<Database, &Database::JS_loadExtension>("loadExtension", addon),
		PrototypeMethod<Database, &Database::JS_close>("close", addon),
		PrototypeMethod<Database, &Database::JS_defaultSafeIntegers>("defaultSafeIntegers", addon),
		PrototypeMethod<Database, &Database::JS_unsafeMode>("unsafeMode", addon),
	}, addon);
}

NODE_METHOD(Database::JS_new) {
	assert(info.IsConstructCall());
	REQUIRE_ARGUMENT_STRING(first, Napi::String filename);
	REQUIRE_ARGUMENT_STRING(second, Napi::String filenameGiven);
	REQUIRE_ARGUMENT_BOOLEAN(third, bool in_memory);
	REQUIRE_ARGUMENT_BOOLEAN(fourth, bool readonly);
	REQUIRE_ARGUMENT_BOOLEAN(fifth, bool must_exist);
	REQUIRE_ARGUMENT_INT32(sixth, int timeout);
	REQUIRE_ARGUMENT_ANY(seventh, Napi::Value logger);
	REQUIRE_ARGUMENT_ANY(eighth, Napi::Value buffer);

	UseAddon;
	UseIsolate;
	sqlite3* db_handle;
	std::string utf8 = filename.Utf8Value();
	int mask = readonly ? SQLITE_OPEN_READONLY
		: must_exist ? SQLITE_OPEN_READWRITE
		: (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	if (sqlite3_open_v2(utf8.c_str(), &db_handle, mask, NULL) != SQLITE_OK) {
		ThrowSqliteError(env, addon, db_handle);
		int status = sqlite3_close(db_handle);
		assert(status == SQLITE_OK); ((void)status);
		return env.Undefined();
	}

	assert(sqlite3_db_mutex(db_handle) == NULL);
	sqlite3_extended_result_codes(db_handle, 1);
	sqlite3_busy_timeout(db_handle, timeout);
	sqlite3_limit(db_handle, SQLITE_LIMIT_LENGTH, MAX_BUFFER_SIZE < MAX_STRING_SIZE ? MAX_BUFFER_SIZE : MAX_STRING_SIZE);
	sqlite3_limit(db_handle, SQLITE_LIMIT_SQL_LENGTH, MAX_STRING_SIZE);
	int status = sqlite3_db_config(db_handle, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL);
	assert(status == SQLITE_OK); ((void)status);
	status = sqlite3_db_config(db_handle, SQLITE_DBCONFIG_DEFENSIVE, 1, NULL);
	assert(status == SQLITE_OK); ((void)status);

	if (buffer.IsBuffer() && !Deserialize(env, buffer.As<Napi::Object>(), addon, db_handle, readonly)) {
		int status = sqlite3_close(db_handle);
		assert(status == SQLITE_OK); ((void)status);
		return env.Undefined();
	}

	this->db_handle = db_handle;
	open = true;
	has_logger = logger.IsFunction();
	if (has_logger) this->logger.Reset(logger, 1);
	addon->dbs.insert(this);

	Napi::Object _this = info.This().As<Napi::Object>();
	SetFrozen(env, _this, addon->cs.memory, Napi::Boolean::New(env, in_memory));
	SetFrozen(env, _this, addon->cs.readonly, Napi::Boolean::New(env, readonly));
	SetFrozen(env, _this, addon->cs.name, filenameGiven);
	SetInstanceGetter<Database, &Database::JS_open>(_this, "open", addon);
	SetInstanceGetter<Database, &Database::JS_inTransaction>(_this, "inTransaction", addon);

	return info.This();
}

NODE_METHOD(Database::JS_prepare) {
	REQUIRE_ARGUMENT_STRING(first, Napi::String source);
	REQUIRE_ARGUMENT_OBJECT(second, Napi::Object database);
	REQUIRE_ARGUMENT_BOOLEAN(third, bool pragmaMode);
	REQUIRE_ARGUMENT_BOOLEAN(fourth, bool explainMode);
	(void)source;
	(void)database;
	(void)pragmaMode;
	(void)explainMode;
	UseAddon;
	UseIsolate;
	Napi::Function c = addon->Statement.Value();
	addon->privileged_info = &info;
	Napi::Object statement = SafeConstruct(env, c);
	addon->privileged_info = NULL;
	if (env.IsExceptionPending()) return env.Undefined();
	return statement;
}

NODE_METHOD(Database::JS_exec) {
	Database* db = ::Unwrap<Database>(info.This());
	REQUIRE_ARGUMENT_STRING(first, Napi::String source);
	REQUIRE_DATABASE_OPEN(db);
	REQUIRE_DATABASE_NOT_BUSY(db);
	REQUIRE_DATABASE_NO_ITERATORS_UNLESS_UNSAFE(db);
	db->busy = true;

	UseIsolate;
	std::string utf8 = source.Utf8Value();
	const char* sql = utf8.c_str();
	const char* tail;

	int status;
	const bool has_logger = db->has_logger;
	sqlite3* const db_handle = db->db_handle;
	sqlite3_stmt* handle;

	for (;;) {
		while (IS_SKIPPED(*sql)) ++sql;
		status = sqlite3_prepare_v2(db_handle, sql, -1, &handle, &tail);
		sql = tail;
		if (!handle) break;
		if (has_logger && db->Log(env, handle)) {
			sqlite3_finalize(handle);
			status = -1;
			break;
		}
		do status = sqlite3_step(handle);
		while (status == SQLITE_ROW);
		status = sqlite3_finalize(handle);
		if (status != SQLITE_OK) break;
	}

	db->busy = false;
	if (status != SQLITE_OK) {
		db->ThrowDatabaseError(env);
	}
	return env.Undefined();
}

NODE_METHOD(Database::JS_backup) {
	REQUIRE_ARGUMENT_OBJECT(first, Napi::Object database);
	REQUIRE_ARGUMENT_STRING(second, Napi::String attachedName);
	REQUIRE_ARGUMENT_STRING(third, Napi::String destFile);
	REQUIRE_ARGUMENT_BOOLEAN(fourth, bool unlink);
	(void)database;
	(void)attachedName;
	(void)destFile;
	(void)unlink;
	UseAddon;
	UseIsolate;
	Napi::Function c = addon->Backup.Value();
	addon->privileged_info = &info;
	Napi::Object backup = SafeConstruct(env, c);
	addon->privileged_info = NULL;
	if (env.IsExceptionPending()) return env.Undefined();
	return backup;
}

NODE_METHOD(Database::JS_serialize) {
	Database* db = ::Unwrap<Database>(info.This());
	REQUIRE_ARGUMENT_STRING(first, Napi::String attachedName);
	REQUIRE_DATABASE_OPEN(db);
	REQUIRE_DATABASE_NOT_BUSY(db);
	REQUIRE_DATABASE_NO_ITERATORS(db);

	UseIsolate;
	std::string attached_name = attachedName.Utf8Value();
	sqlite3_int64 length = -1;
	unsigned char* data = sqlite3_serialize(db->db_handle, attached_name.c_str(), &length, 0);

	if (!data && length) {
		return ThrowError(env, "Out of memory");
	}

	return Napi::Buffer<char>::NewOrCopy(env, reinterpret_cast<char*>(data), length, FreeSerialization);
}

NODE_METHOD(Database::JS_function) {
	Database* db = ::Unwrap<Database>(info.This());
	REQUIRE_ARGUMENT_FUNCTION(first, Napi::Function fn);
	REQUIRE_ARGUMENT_STRING(second, Napi::String nameString);
	REQUIRE_ARGUMENT_INT32(third, int argc);
	REQUIRE_ARGUMENT_INT32(fourth, int safe_ints);
	REQUIRE_ARGUMENT_BOOLEAN(fifth, bool deterministic);
	REQUIRE_ARGUMENT_BOOLEAN(sixth, bool direct_only);
	REQUIRE_DATABASE_OPEN(db);
	REQUIRE_DATABASE_NOT_BUSY(db);
	REQUIRE_DATABASE_NO_ITERATORS(db);

	UseIsolate;
	std::string name = nameString.Utf8Value();
	int mask = SQLITE_UTF8;
	if (deterministic) mask |= SQLITE_DETERMINISTIC;
	if (direct_only) mask |= SQLITE_DIRECTONLY;
	safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(db->safe_ints);

	if (sqlite3_create_function_v2(db->db_handle, name.c_str(), argc, mask, new CustomFunction(env, db, name.c_str(), fn, safe_ints), CustomFunction::xFunc, NULL, NULL, CustomFunction::xDestroy) != SQLITE_OK) {
		db->ThrowDatabaseError(env);
	}
	return env.Undefined();
}

NODE_METHOD(Database::JS_aggregate) {
	Database* db = ::Unwrap<Database>(info.This());
	REQUIRE_ARGUMENT_ANY(first, Napi::Value start);
	REQUIRE_ARGUMENT_FUNCTION(second, Napi::Function step);
	REQUIRE_ARGUMENT_ANY(third, Napi::Value inverse);
	REQUIRE_ARGUMENT_ANY(fourth, Napi::Value result);
	REQUIRE_ARGUMENT_STRING(fifth, Napi::String nameString);
	REQUIRE_ARGUMENT_INT32(sixth, int argc);
	REQUIRE_ARGUMENT_INT32(seventh, int safe_ints);
	REQUIRE_ARGUMENT_BOOLEAN(eighth, bool deterministic);
	REQUIRE_ARGUMENT_BOOLEAN(ninth, bool direct_only);
	REQUIRE_DATABASE_OPEN(db);
	REQUIRE_DATABASE_NOT_BUSY(db);
	REQUIRE_DATABASE_NO_ITERATORS(db);

	UseIsolate;
	std::string name = nameString.Utf8Value();
	auto xInverse = inverse.IsFunction() ? CustomAggregate::xInverse : NULL;
	auto xValue = xInverse ? CustomAggregate::xValue : NULL;
	int mask = SQLITE_UTF8;
	if (deterministic) mask |= SQLITE_DETERMINISTIC;
	if (direct_only) mask |= SQLITE_DIRECTONLY;
	safe_ints = safe_ints < 2 ? safe_ints : static_cast<int>(db->safe_ints);

	if (sqlite3_create_window_function(db->db_handle, name.c_str(), argc, mask, new CustomAggregate(env, db, name.c_str(), start, step, inverse, result, safe_ints), CustomAggregate::xStep, CustomAggregate::xFinal, xValue, xInverse, CustomAggregate::xDestroy) != SQLITE_OK) {
		db->ThrowDatabaseError(env);
	}
	return env.Undefined();
}

NODE_METHOD(Database::JS_table) {
	Database* db = ::Unwrap<Database>(info.This());
	REQUIRE_ARGUMENT_FUNCTION(first, Napi::Function factory);
	REQUIRE_ARGUMENT_STRING(second, Napi::String nameString);
	REQUIRE_ARGUMENT_BOOLEAN(third, bool eponymous);
	REQUIRE_DATABASE_OPEN(db);
	REQUIRE_DATABASE_NOT_BUSY(db);
	REQUIRE_DATABASE_NO_ITERATORS(db);

	UseIsolate;
	std::string name = nameString.Utf8Value();
	sqlite3_module* module = eponymous ? &CustomTable::EPONYMOUS_MODULE : &CustomTable::MODULE;

	db->busy = true;
	if (sqlite3_create_module_v2(db->db_handle, name.c_str(), module, new CustomTable(env, db, name.c_str(), factory), CustomTable::Destructor) != SQLITE_OK) {
		db->ThrowDatabaseError(env);
	}
	db->busy = false;
	return env.Undefined();
}

NODE_METHOD(Database::JS_loadExtension) {
	Database* db = ::Unwrap<Database>(info.This());
	Napi::String entryPoint;
	REQUIRE_ARGUMENT_STRING(first, Napi::String filename);
	if (info.Length() > 1) { REQUIRE_ARGUMENT_STRING(second, entryPoint); }
	REQUIRE_DATABASE_OPEN(db);
	REQUIRE_DATABASE_NOT_BUSY(db);
	REQUIRE_DATABASE_NO_ITERATORS(db);
	UseIsolate;
	char* error;
	std::string filename_utf8 = filename.Utf8Value();
	std::string entry_utf8;
	bool has_entry = !entryPoint.IsEmpty();
	if (has_entry) entry_utf8 = entryPoint.Utf8Value();
	int status = sqlite3_load_extension(
		db->db_handle,
		filename_utf8.c_str(),
		has_entry ? entry_utf8.c_str() : NULL,
		&error
	);
	if (status != SQLITE_OK) {
		ThrowSqliteError(env, db->addon, error, status);
	}
	sqlite3_free(error);
	return env.Undefined();
}

NODE_METHOD(Database::JS_close) {
	Database* db = ::Unwrap<Database>(info.This());
	if (db->open) {
		REQUIRE_DATABASE_NOT_BUSY(db);
		REQUIRE_DATABASE_NO_ITERATORS(db);
		db->addon->dbs.erase(db);
		db->CloseHandles();
	}
	return info.Env().Undefined();
}

NODE_METHOD(Database::JS_defaultSafeIntegers) {
	Database* db = ::Unwrap<Database>(info.This());
	if (info.Length() == 0) db->safe_ints = true;
	else { REQUIRE_ARGUMENT_BOOLEAN(first, db->safe_ints); }
	return info.Env().Undefined();
}

NODE_METHOD(Database::JS_unsafeMode) {
	Database* db = ::Unwrap<Database>(info.This());
	if (info.Length() == 0) db->unsafe_mode = true;
	else { REQUIRE_ARGUMENT_BOOLEAN(first, db->unsafe_mode); }
	sqlite3_db_config(db->db_handle, SQLITE_DBCONFIG_DEFENSIVE, static_cast<int>(!db->unsafe_mode), NULL);
	return info.Env().Undefined();
}

NODE_GETTER(Database::JS_open) {
	Database* db = ::Unwrap<Database>(info.This());
	return Napi::Boolean::New(info.Env(), db->open);
}

NODE_GETTER(Database::JS_inTransaction) {
	Database* db = ::Unwrap<Database>(info.This());
	return Napi::Boolean::New(info.Env(), db->open && !static_cast<bool>(sqlite3_get_autocommit(db->db_handle)));
}
