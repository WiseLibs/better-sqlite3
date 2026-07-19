const napi_type_tag StatementIterator::TYPE_TAG = RandomTypeTag();

StatementIterator::StatementIterator(const Napi::CallbackInfo& info) :
	Napi::ObjectWrap<StatementIterator>(info),
	stmt(NULL),
	handle(NULL),
	db_state(NULL),
	bound(false),
	safe_ints(false),
	mode(Data::FLAT),
	alive(false),
	logged(false) {
	napi_status status = napi_type_tag_object(info.Env(), info.This(), &TYPE_TAG);
	assert(status == napi_ok); ((void)status);
	JS_new(info);
}

// The ~Statement destructor currently covers any state this object creates.
// Additionally, we actually DON'T want to revert stmt->locked or db_state
// ->iterators in this destructor, to ensure deterministic database access.
StatementIterator::~StatementIterator() {}

Napi::Value StatementIterator::Next(Napi::Env env) {
	assert(alive == true);
	db_state->busy = true;
	if (!logged) {
		logged = true;
		if (stmt->db->Log(env, handle)) {
			db_state->busy = false;
			return Throw(env);
		}
	}
	int status = sqlite3_step(handle);
	db_state->busy = false;

	if (status == SQLITE_ROW) {
		Napi::Value row = Data::GetRowJS(env, stmt, handle, safe_ints, mode);
		return NewRecord(env, row, db_state->addon, false);
	} else {
		if (status == SQLITE_DONE) return Return(env);
		return Throw(env);
	}
}

Napi::Value StatementIterator::Return(Napi::Env env) {
	Cleanup();
	STATEMENT_RETURN_LOGIC(DoneRecord(env, db_state->addon));
}

Napi::Value StatementIterator::Throw(Napi::Env env) {
	Cleanup();
	Database* db = stmt->db;
	STATEMENT_THROW_LOGIC();
}

void StatementIterator::Cleanup() {
	assert(alive == true);
	alive = false;
	stmt->locked = false;
	db_state->iterators -= 1;
	sqlite3_reset(handle);
}

INIT(StatementIterator::Init) {
	return DefineClass(env, "StatementIterator", {
		PrototypeMethod<StatementIterator, &StatementIterator::JS_next>("next", addon),
		PrototypeMethod<StatementIterator, &StatementIterator::JS_return>("return", addon),
		PrototypeSymbolMethod<StatementIterator, &StatementIterator::JS_symbolIterator>(Napi::Symbol::WellKnown(env, "iterator"), addon),
	}, addon);
}

NODE_METHOD(StatementIterator::JS_new) {
	UseAddon;
	if (!addon->privileged_info) return ThrowTypeError(info.Env(), "Disabled constructor");
	assert(info.IsConstructCall());

	{
		const Napi::CallbackInfo& info = *addon->privileged_info;
		STATEMENT_START_LOGIC(REQUIRE_STATEMENT_RETURNS_DATA, DOES_ADD_ITERATOR);
		this->stmt = stmt;
		this->handle = stmt->handle;
		this->db_state = stmt->db->GetState();
		this->bound = bound;
		this->safe_ints = stmt->safe_ints;
		this->mode = stmt->mode;
		this->alive = true;
		this->logged = !db_state->has_logger;
		assert(stmt != NULL);
		assert(handle != NULL);
		assert(stmt->bound == bound);
		assert(stmt->alive == true);
		assert(stmt->locked == false);
		assert(db_state->iterators < USHRT_MAX);
		stmt->locked = true;
		db_state->iterators += 1;
	}

	UseIsolate;
	SetFrozen(env, info.This().As<Napi::Object>(), addon->cs.statement, addon->privileged_info->This());

	return info.This();
}

NODE_METHOD(StatementIterator::JS_next) {
	StatementIterator* iter = ::Unwrap<StatementIterator>(info.This());
	REQUIRE_DATABASE_NOT_BUSY(iter->db_state);
	if (iter->alive) return iter->Next(info.Env());
	return DoneRecord(info.Env(), iter->db_state->addon);
}

NODE_METHOD(StatementIterator::JS_return) {
	StatementIterator* iter = ::Unwrap<StatementIterator>(info.This());
	REQUIRE_DATABASE_NOT_BUSY(iter->db_state);
	if (iter->alive) return iter->Return(info.Env());
	return DoneRecord(info.Env(), iter->db_state->addon);
}

NODE_METHOD(StatementIterator::JS_symbolIterator) {
	return info.This();
}
