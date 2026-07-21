#define JS_VALUE_TO_SQLITE(to, value, env, ...)                                \
	if (value.IsNumber()) {                                                    \
		return sqlite3_##to##_double(                                          \
			__VA_ARGS__,                                                       \
			value.As<Napi::Number>().DoubleValue()                             \
		);                                                                     \
	} else if (value.IsBigInt()) {                                             \
		bool lossless;                                                         \
		int64_t v = value.As<Napi::BigInt>().Int64Value(&lossless);            \
		if (lossless) {                                                        \
			return sqlite3_##to##_int64(__VA_ARGS__, v);                       \
		}                                                                      \
	} else if (value.IsString()) {                                             \
		std::string utf8 = value.As<Napi::String>().Utf8Value();               \
		return sqlite3_##to##_text(                                            \
			__VA_ARGS__,                                                       \
			utf8.c_str(),                                                      \
			utf8.length(),                                                     \
			SQLITE_TRANSIENT                                                   \
		);                                                                     \
	} else if (value.IsBuffer()) {                                             \
		Napi::Buffer<char> buffer = value.As<Napi::Buffer<char>>();            \
		const char* data = buffer.Data();                                      \
		return sqlite3_##to##_blob(                                            \
			__VA_ARGS__,                                                       \
			data ? data : "",                                                  \
			buffer.Length(),                                                   \
			SQLITE_TRANSIENT                                                   \
		);                                                                     \
	} else if (value.IsNull() || value.IsUndefined()) {                        \
		return sqlite3_##to##_null(__VA_ARGS__);                               \
	}

#define SQLITE_VALUE_TO_JS(from, env, safe_ints, ...)                          \
	switch (sqlite3_##from##_type(__VA_ARGS__)) {                              \
	case SQLITE_INTEGER:                                                       \
		if (safe_ints) {                                                       \
			return Napi::BigInt::New(                                          \
				env,                                                           \
				(int64_t)sqlite3_##from##_int64(__VA_ARGS__)                   \
			);                                                                 \
		}                                                                      \
	case SQLITE_FLOAT:                                                         \
		return Napi::Number::New(                                              \
			env,                                                               \
			sqlite3_##from##_double(__VA_ARGS__)                               \
		);                                                                     \
	case SQLITE_TEXT:                                                          \
		return StringFromUtf8(                                                 \
			env,                                                               \
			reinterpret_cast<const char*>(sqlite3_##from##_text(__VA_ARGS__)), \
			sqlite3_##from##_bytes(__VA_ARGS__)                                \
		);                                                                     \
	case SQLITE_BLOB:                                                          \
		return Napi::Buffer<char>::Copy(                                       \
			env,                                                               \
			static_cast<const char*>(sqlite3_##from##_blob(__VA_ARGS__)),      \
			sqlite3_##from##_bytes(__VA_ARGS__)                                \
		);                                                                     \
	default:                                                                   \
		assert(sqlite3_##from##_type(__VA_ARGS__) == SQLITE_NULL);             \
		return env.Null();                                                     \
	}                                                                          \
	assert(false);

namespace Data {

	static const char FLAT = 0;
	static const char PLUCK = 1;
	static const char EXPAND = 2;
	static const char RAW = 3;

	Napi::Value GetValueJS(Napi::Env env, sqlite3_stmt* handle, int column, bool safe_ints) {
		SQLITE_VALUE_TO_JS(column, env, safe_ints, handle, column);
	}

	Napi::Value GetValueJS(Napi::Env env, sqlite3_value* value, bool safe_ints) {
		SQLITE_VALUE_TO_JS(value, env, safe_ints, value);
	}

	Napi::Value GetExpandedRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints) {
		Napi::Object row = Napi::Object::New(env);
		int column_count = sqlite3_column_count(handle);
		for (int i = 0; i < column_count; ++i) {
			const char* table_raw = sqlite3_column_table_name(handle, i);
			Napi::String table = InternalizedFromUtf8(env, table_raw == NULL ? "$" : table_raw, -1);
			Napi::String column = InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1);
			Napi::Value value = Data::GetValueJS(env, handle, i, safe_ints);
			if (row.HasOwnProperty(table)) {
				row.Get(table).As<Napi::Object>().Set(column, value);
			} else {
				Napi::Object nested = Napi::Object::New(env);
				row.Set(table, nested);
				nested.Set(column, value);
			}
		}
		return row;
	}

	Napi::Value GetFlatRowJS(Napi::Env env, Statement* stmt, sqlite3_stmt* handle, bool safe_ints) {
		return stmt->GetRowBuilder().GetRowJS(env, handle, safe_ints);
	}

	Napi::Value GetRawRowJS(Napi::Env env, Statement* stmt, sqlite3_stmt* handle, bool safe_ints) {
		return stmt->GetRowBuilder().GetRawRowJS(env, handle, safe_ints);
	}

	Napi::Value GetRowJS(Napi::Env env, Statement* stmt, sqlite3_stmt* handle, bool safe_ints, char mode) {
		if (mode == Data::FLAT) return GetFlatRowJS(env, stmt, handle, safe_ints);
		if (mode == PLUCK) return GetValueJS(env, handle, 0, safe_ints);
		if (mode == EXPAND) return GetExpandedRowJS(env, handle, safe_ints);
		if (mode == RAW) return GetRawRowJS(env, stmt, handle, safe_ints);
		assert(false);
		return Napi::Value();
	}

	void GetArgumentsJS(Napi::Env env, napi_value* out, sqlite3_value** values, int argument_count, bool safe_ints) {
		assert(argument_count > 0);
		for (int i = 0; i < argument_count; ++i) {
			out[i] = Data::GetValueJS(env, values[i], safe_ints);
		}
	}

	int BindValueFromJS(Napi::Env env, sqlite3_stmt* handle, int index, Napi::Value value) {
		JS_VALUE_TO_SQLITE(bind, value, env, handle, index);
		return value.IsBigInt() ? SQLITE_TOOBIG : -1;
	}

	void ResultValueFromJS(Napi::Env env, sqlite3_context* invocation, Napi::Value value, DataConverter* converter) {
		JS_VALUE_TO_SQLITE(result, value, env, invocation);
		converter->ThrowDataConversionError(env, invocation, value.IsBigInt());
	}

}
