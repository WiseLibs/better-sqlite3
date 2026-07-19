LocalRowBuilder::LocalRowBuilder(Napi::Env env, sqlite3_stmt* handle, bool safe_ints) :
	env(env),
	handle(handle),
	column_count(-1),
	safe_ints(safe_ints),
	create(GetCreateObjectWithProperties()),
	prototype(Napi::Object::New(env).GetPrototype()),
	null_value(env.Null()),
	keys(),
	values(),
	properties() {}

Napi::Value LocalRowBuilder::GetRowJS() {
	if (create != NULL) {
		// Fast path, using the new "node_api_create_object_with_properties" API.
		if (column_count < 0) {
			column_count = sqlite3_column_count(handle);
			keys.reserve(column_count);
			values.resize(column_count);
			for (int i = 0; i < column_count; ++i) {
				keys.emplace_back(InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1));
			}
		}

		for (int i = 0; i < column_count; ++i) {
			values[i] = Data::GetValueJS(env, handle, i, safe_ints, null_value);
		}

		napi_value row;
		napi_status status = create(env, prototype, keys.data(), values.data(), values.size(), &row);
		assert(status == napi_ok); ((void)status);
		return Napi::Value(env, row);
	} else {
		// Slow path, only in old versions of Node.
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
			properties[i].value = Data::GetValueJS(env, handle, i, safe_ints, null_value);
		}

		napi_value row;
		napi_status status = napi_create_object(env, &row);
		assert(status == napi_ok);
		status = napi_define_properties(env, row, properties.size(), properties.data());
		assert(status == napi_ok); ((void)status);
		return Napi::Value(env, row);
	}
}

PersistentRowBuilder::PersistentRowBuilder(Napi::Env env) :
	create(GetCreateObjectWithProperties()),
	prototype(Napi::Persistent(Napi::Object::New(env).GetPrototype().As<Napi::Object>())),
	column_count(-1),
	reprepare_count(-1) {}

Napi::Value PersistentRowBuilder::GetRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints) {
	assert(create != NULL); // Never used in old versions of Node

	int current_reprepare_count = sqlite3_stmt_status(handle, SQLITE_STMTSTATUS_REPREPARE, false);
	if (current_reprepare_count != reprepare_count) {
		column_count = sqlite3_column_count(handle);
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
