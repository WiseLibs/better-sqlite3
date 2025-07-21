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
