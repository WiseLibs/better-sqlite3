class Statement : public node::ObjectWrap { friend class StatementIterator;
public:

	~Statement();

	// Whenever this is used, db->RemoveStatement must be invoked beforehand.
	void CloseHandles();

	// Used to support ordered containers.
	static inline bool Compare(Statement const * const a, Statement const * const b) {
		return a->extras->id < b->extras->id;
	}

	// Returns the Statement's bind map (creates it upon first execution).
	BindMap* GetBindMap(v8::Isolate* isolate);

	static INIT(Init);

private:

	// A class for holding values that are less often used.
	class Extras { friend class Statement;
		explicit Extras(sqlite3_uint64 id);
		BindMap bind_map;
		const sqlite3_uint64 id;
	};

	explicit Statement(
		Database* db,
		sqlite3_stmt* handle,
		sqlite3_uint64 id,
		bool returns_data
	);

	static NODE_METHOD(JS_new);
	static NODE_METHOD(JS_run);
	static NODE_METHOD(JS_get);
	static NODE_METHOD(JS_all);
	static NODE_METHOD(JS_iterate);
	static NODE_METHOD(JS_bind);
	static NODE_METHOD(JS_pluck);
	static NODE_METHOD(JS_expand);
	static NODE_METHOD(JS_raw);
	static NODE_METHOD(JS_safeIntegers);
	static NODE_METHOD(JS_columns);
	static NODE_GETTER(JS_busy);

	Database* const db;
	sqlite3_stmt* const handle;
	Extras* const extras;
	bool alive;
	bool locked;
	bool bound;
	bool has_bind_map;
	bool safe_ints;
	char mode;
	const bool returns_data;
};
