struct Addon {
	explicit Addon(Napi::Env env) :
		privileged_info(NULL),
		next_id(0),
		cs(env) {}

	static void Cleanup(Addon* addon) {
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

	static NODE_METHOD(JS_initialize) {
		REQUIRE_ARGUMENT_FUNCTION(first, Napi::Function SqliteError);
		REQUIRE_ARGUMENT_FUNCTION(second, Napi::Function ArrayFactory);
		REQUIRE_ARGUMENT_FUNCTION(third, Napi::Function ArrayAppender);
		REQUIRE_ARGUMENT_FUNCTION(fourth, Napi::Function RowFactory);
		REQUIRE_ARGUMENT_FUNCTION(fifth, Napi::Function RecordFactory);
		OnlyAddon->SqliteError = Napi::Persistent(SqliteError);
		OnlyAddon->ArrayFactory = Napi::Persistent(ArrayFactory);
		OnlyAddon->ArrayAppender = Napi::Persistent(ArrayAppender);
		OnlyAddon->RowFactory = Napi::Persistent(RowFactory);
		OnlyAddon->RecordFactory = Napi::Persistent(RecordFactory);
		return info.Env().Undefined();
	}

	Napi::FunctionReference Statement;
	Napi::FunctionReference StatementIterator;
	Napi::FunctionReference Backup;
	Napi::FunctionReference SqliteError;
	Napi::FunctionReference ArrayFactory;
	Napi::FunctionReference ArrayAppender;
	Napi::FunctionReference RowFactory;
	Napi::FunctionReference RecordFactory;
	NODE_ARGUMENTS_POINTER privileged_info;
	sqlite3_uint64 next_id;
	CS cs;
	std::set<Database*, Database::CompareDatabase> dbs;
};
