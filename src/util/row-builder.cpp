// Builds row objects for queries that return many rows (see Statement::JS_all).
// The property descriptors and JavaScript column-name handles are initialized
// only once and reused for every row.
class RowBuilder {
public:

	explicit RowBuilder(
		Napi::Env env,
		sqlite3_stmt* handle,
		bool safe_ints
	) :
		env(env),
		handle(handle),
		column_count(-1),
		safe_ints(safe_ints),
		prototype(Napi::Object::New(env).GetPrototype()),
		keys(),
		values(),
		properties() {}

	Napi::Value GetRowJS() {
		CreateObjectWithPropertiesFn create = GetCreateObjectWithProperties();
		if (create != NULL) {
			if (column_count < 0) {
				column_count = sqlite3_column_count(handle);
				keys.reserve(column_count);
				values.resize(column_count);
				for (int i = 0; i < column_count; ++i) {
					keys.emplace_back(InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1));
				}
			}

			for (int i = 0; i < column_count; ++i) {
				values[i] = Data::GetValueJS(env, handle, i, safe_ints);
			}

			napi_value row;
			napi_status status = create(env, prototype, keys.data(), values.data(), values.size(), &row);
			assert(status == napi_ok); ((void)status);
			return Napi::Value(env, row);
		} else {
			if (column_count < 0) {
				column_count = sqlite3_column_count(handle);
				properties.resize(column_count);
				for (int i = 0; i < column_count; ++i) {
					napi_property_descriptor& property = properties[i];
					property.name = InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1);
					property.attributes = DEFAULT_ATTRIBUTES;
				}
			}

			for (int i = 0; i < column_count; ++i) {
				properties[i].value = Data::GetValueJS(env, handle, i, safe_ints);
			}

			napi_value row;
			napi_status status = napi_create_object(env, &row);
			assert(status == napi_ok);
			status = napi_define_properties(env, row, properties.size(), properties.data());
			assert(status == napi_ok); ((void)status);
			return Napi::Value(env, row);
		}
	}

private:
	Napi::Env env;
	sqlite3_stmt* handle;
	int column_count;
	const bool safe_ints;
	Napi::Value prototype;
	std::vector<napi_value> keys;
	std::vector<napi_value> values;
	std::vector<napi_property_descriptor> properties;
};

// Caches the handles needed by the bulk object API across separate callbacks
// (Statement#get and iterator#next). The cache is rebuilt if SQLite reparses
// the statement after a schema change.
class PersistentRowBuilder {
public:
	explicit PersistentRowBuilder(Napi::Env env) :
		prototype(Napi::Persistent(Napi::Object::New(env).GetPrototype().As<Napi::Object>())),
		reprepare_count(-1) {}

	Napi::Value GetRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints) {
		CreateObjectWithPropertiesFn create = GetCreateObjectWithProperties();
		if (create == NULL) return Data::GetFlatRowJS(env, handle, safe_ints);

		int current_reprepare_count = sqlite3_stmt_status(handle, SQLITE_STMTSTATUS_REPREPARE, false);
		int column_count = sqlite3_column_count(handle);
		if (current_reprepare_count != reprepare_count) {
			keys.clear();
			keys.reserve(column_count);
			for (int i = 0; i < column_count; ++i) {
				keys.emplace_back(Napi::Persistent(
					InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1)
				));
			}
			reprepare_count = current_reprepare_count;
		}

		napi_value local_key_storage[16];
		napi_value value_storage[16];
		std::vector<napi_value> extra_keys;
		std::vector<napi_value> extra_values;
		napi_value* local_keys = local_key_storage;
		napi_value* values = value_storage;
		if (column_count > 16) {
			extra_keys.resize(column_count);
			extra_values.resize(column_count);
			local_keys = extra_keys.data();
			values = extra_values.data();
		}
		for (int i = 0; i < column_count; ++i) {
			local_keys[i] = keys[i].Value();
			values[i] = Data::GetValueJS(env, handle, i, safe_ints);
		}

		napi_value row;
		napi_status status = create(env, prototype.Value(), local_keys, values, column_count, &row);
		assert(status == napi_ok); ((void)status);
		return Napi::Value(env, row);
	}

private:
	Napi::Reference<Napi::Object> prototype;
	std::vector<Napi::Reference<Napi::String>> keys;
	int reprepare_count;
};
