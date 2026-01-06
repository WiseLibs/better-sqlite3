class StatementIterator : public node::ObjectWrap {
public:

	// The ~Statement destructor currently covers any state this object creates.
	// Additionally, we actually DON'T want to revert stmt->locked or db_state
	// ->iterators in this destructor, to ensure deterministic database access.
	~StatementIterator();

	static INIT(Init);

private:

	explicit StatementIterator(Statement* stmt, bool bound);

	void Next(NODE_ARGUMENTS info);
	void Return(NODE_ARGUMENTS info);
	void Throw();
	void Cleanup();

	static inline v8::Local<v8::Object> NewRecord(
		v8::Isolate* isolate,
		v8::Local<v8::Context> ctx,
		v8::Local<v8::Value> value,
		Addon* addon,
		bool done
	) {
		v8::Local<v8::Object> record = v8::Object::New(isolate);
		record->Set(ctx, addon->cs.value.Get(isolate), value).FromJust();
		record->Set(ctx, addon->cs.done.Get(isolate), v8::Boolean::New(isolate, done)).FromJust();
		return record;
	}

	static inline v8::Local<v8::Object> DoneRecord(v8::Isolate* isolate, Addon* addon) {
		return NewRecord(isolate, OnlyContext, v8::Undefined(isolate), addon, true);
	}

	static NODE_METHOD(JS_new);
	static NODE_METHOD(JS_next);
	static NODE_METHOD(JS_return);
	static NODE_METHOD(JS_symbolIterator);

	Statement* const stmt;
	sqlite3_stmt* const handle;
	Database::State* const db_state;
	const bool bound;
	const bool safe_ints;
	const char mode;
	bool alive;
	bool logged;
};
