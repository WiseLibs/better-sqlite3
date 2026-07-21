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
		assert(!addon->RecordFactory.IsEmpty());

		// Fast path, using a factory function from JS land.
		if (!done) {
			napi_value arg = value;
			return SafeCall(env, addon->RecordFactory.Value(), env.Undefined(), 1, &arg)
				.As<Napi::Object>();
		}

		// Slow path, only used after the iterator is done.
		napi_property_descriptor properties[2] = {};
		properties[0].name = addon->cs.value.Value();
		properties[0].value = value;
		properties[0].attributes = DEFAULT_ATTRIBUTES;
		properties[1].name = addon->cs.done.Value();
		properties[1].value = Napi::Boolean::New(env, done);
		properties[1].attributes = DEFAULT_ATTRIBUTES;

		napi_value record;
		napi_status status = napi_create_object(env, &record);
		assert(status == napi_ok);
		status = napi_define_properties(env, record, 2, properties);
		assert(status == napi_ok); ((void)status);
		return Napi::Object(env, record);
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
