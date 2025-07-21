class Database : public node::ObjectWrap {
public:

	~Database();

	// Whenever this is used, addon->dbs.erase() must be invoked beforehand.
	void CloseHandles();

	// Used to support ordered containers.
	class CompareDatabase { public:
		inline bool operator() (Database const * const a, Database const * const b) const {
			return a < b;
		}
	};
	class CompareStatement { public:
		inline bool operator() (Statement const * const a, Statement const * const b) const {
			return Statement::Compare(a, b);
		}
	};
	class CompareBackup { public:
		inline bool operator() (Backup const * const a, Backup const * const b) const {
			return Backup::Compare(a, b);
		}
	};

	// Proper error handling logic for when an sqlite3 operation fails.
	void ThrowDatabaseError();
	static void ThrowSqliteError(Addon* addon, sqlite3* db_handle);
	static void ThrowSqliteError(Addon* addon, const char* message, int code);

	// Allows Statements to log their executed SQL.
	bool Log(v8::Isolate* isolate, sqlite3_stmt* handle);

	// Allow Statements to manage themselves when created and garbage collected.
	inline void AddStatement(Statement* stmt) { stmts.insert(stmts.end(), stmt); }
	inline void RemoveStatement(Statement* stmt) { stmts.erase(stmt); }

	// Allow Backups to manage themselves when created and garbage collected.
	inline void AddBackup(Backup* backup) { backups.insert(backups.end(), backup); }
	inline void RemoveBackup(Backup* backup) { backups.erase(backup); }

	// A view for Statements to see and modify Database state.
	// The order of these fields must exactly match their actual order.
	struct State {
		const bool open;
		bool busy;
		const bool safe_ints;
		const bool unsafe_mode;
		bool was_js_error;
		const bool has_logger;
		unsigned short iterators;
		Addon* const addon;
	};

	inline State* GetState() { return reinterpret_cast<State*>(&open); }
	inline sqlite3* GetHandle() { return db_handle; }
	inline Addon* GetAddon() { return addon; }

	static INIT(Init);

private:

	explicit Database(
		v8::Isolate* isolate,
		Addon* addon,
		sqlite3* db_handle,
		v8::Local<v8::Value> logger
	);

	static NODE_METHOD(JS_new);
	static NODE_METHOD(JS_prepare);
	static NODE_METHOD(JS_exec);
	static NODE_METHOD(JS_backup);
	static NODE_METHOD(JS_serialize);
	static NODE_METHOD(JS_function);
	static NODE_METHOD(JS_aggregate);
	static NODE_METHOD(JS_table);
	static NODE_METHOD(JS_loadExtension);
	static NODE_METHOD(JS_close);
	static NODE_METHOD(JS_defaultSafeIntegers);
	static NODE_METHOD(JS_unsafeMode);
	static NODE_GETTER(JS_open);
	static NODE_GETTER(JS_inTransaction);

	static bool Deserialize(v8::Local<v8::Object> buffer, Addon* addon, sqlite3* db_handle, bool readonly);
	static void FreeSerialization(char* data, void* _);

	static const int MAX_BUFFER_SIZE;
	static const int MAX_STRING_SIZE;

	sqlite3* const db_handle;
	bool open;
	bool busy;
	bool safe_ints;
	bool unsafe_mode;
	bool was_js_error;
	const bool has_logger;
	unsigned short iterators;
	Addon* const addon;
	const v8::Global<v8::Value> logger;
	std::set<Statement*, CompareStatement> stmts;
	std::set<Backup*, CompareBackup> backups;
};
