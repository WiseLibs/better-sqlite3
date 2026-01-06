struct Addon {
	explicit Addon(v8::Isolate* isolate) :
		privileged_info(NULL),
		next_id(0),
		cs(isolate) {}

	static void Cleanup(void* ptr) {
		Addon* addon = static_cast<Addon*>(ptr);
		for (Database* db : addon->dbs) db->CloseHandles();
		addon->dbs.clear();
		delete addon;
	}

	inline sqlite3_uint64 NextId() {
		return next_id++;
	}

	static void ConfigureURI() {
		static std::once_flag init_flag;
		std::call_once(init_flag, [](){
			const char* env = getenv("SQLITE_USE_URI");
			if (env != NULL) {
				if (strcmp(env, "1") == 0) {
					int status = sqlite3_config(SQLITE_CONFIG_URI, 1);
					assert(status == SQLITE_OK); ((void)status);
				} else if (strcmp(env, "0") == 0) {
					int status = sqlite3_config(SQLITE_CONFIG_URI, 0);
					assert(status == SQLITE_OK); ((void)status);
				}
			}
		});
	}

	static NODE_METHOD(JS_setErrorConstructor) {
		REQUIRE_ARGUMENT_FUNCTION(first, v8::Local<v8::Function> SqliteError);
		OnlyAddon->SqliteError.Reset(OnlyIsolate, SqliteError);
	}

	v8::Global<v8::Function> Statement;
	v8::Global<v8::Function> StatementIterator;
	v8::Global<v8::Function> Backup;
	v8::Global<v8::Function> SqliteError;
	NODE_ARGUMENTS_POINTER privileged_info;
	sqlite3_uint64 next_id;
	CS cs;
	std::set<Database*, Database::CompareDatabase> dbs;
};
