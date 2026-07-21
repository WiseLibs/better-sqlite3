class Statement : public Napi::ObjectWrap<Statement> { friend class StatementIterator;
public:

	explicit Statement(const Napi::CallbackInfo& info);
	~Statement();

	// Whenever this is used, db->RemoveStatement must be invoked beforehand.
	void CloseHandles();

	// Used to support ordered containers.
	static inline bool Compare(Statement const * const a, Statement const * const b) {
		return a->extras->id < b->extras->id;
	}

	// Returns the Statement's bind map (creates it upon first execution).
	BindMap& GetBindMap(Napi::Env env);

	// Returns the Statement's row builder.
	RowBuilder& GetRowBuilder();

	// Identifies objects that are backed by this class (see IsInstanceOf).
	static const napi_type_tag TYPE_TAG;

	static INIT(Init);

private:

	// A class for holding values that are less often used.
	class Extras { friend class Statement; friend class StatementIterator;
		explicit Extras(
			Napi::Env env,
			Napi::Function row_factory,
			Napi::Function array_Factory,
			sqlite3_uint64 id
		);
		BindMap bind_map;
		RowBuilder row_builder;
		const sqlite3_uint64 id;
	};

	NODE_METHOD(JS_new);
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
	static NODE_METHOD(JS_toString);
	static NODE_GETTER(JS_busy);

	Database* db;
	sqlite3_stmt* handle;
	Extras* extras;
	bool alive;
	bool locked;
	bool bound;
	bool has_bind_map;
	bool safe_ints;
	char mode;
	bool returns_data;
};
