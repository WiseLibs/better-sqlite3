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
		properties() {}

	Napi::Value GetRowJS() {
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

private:
	Napi::Env env;
	sqlite3_stmt* handle;
	int column_count;
	const bool safe_ints;
	std::vector<napi_property_descriptor> properties;
};
