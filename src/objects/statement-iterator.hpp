class StatementIterator : public Napi::ObjectWrap<StatementIterator> {
public:

	// The ~Statement destructor currently covers any state this object creates.
	// Additionally, we actually DON'T want to revert stmt->locked or db_state
	// ->iterators in this destructor, to ensure deterministic database access.
	explicit StatementIterator(const Napi::CallbackInfo& info);
	~StatementIterator();

	// Identifies objects that are backed by this class (see IsInstanceOf).
	static const napi_type_tag TYPE_TAG;

	static INIT(Init);

private:

	Napi::Value Next(Napi::Env env);
	Napi::Value Return(Napi::Env env);
	Napi::Value Throw(Napi::Env env);
	void Cleanup();

	static inline Napi::Object NewRecord(
		Napi::Env env,
		Napi::Value value,
		Addon* addon,
		bool done
	) {
		Napi::Object record = Napi::Object::New(env);
		record.Set(addon->cs.value.Value(), value);
		record.Set(addon->cs.done.Value(), Napi::Boolean::New(env, done));
		return record;
	}

	static inline Napi::Object DoneRecord(Napi::Env env, Addon* addon) {
		return NewRecord(env, env.Undefined(), addon, true);
	}

	NODE_METHOD(JS_new);
	static NODE_METHOD(JS_next);
	static NODE_METHOD(JS_return);
	static NODE_METHOD(JS_symbolIterator);

	Statement* stmt;
	sqlite3_stmt* handle;
	Database::State* db_state;
	bool bound;
	bool safe_ints;
	char mode;
	bool alive;
	bool logged;
};
