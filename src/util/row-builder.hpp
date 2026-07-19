// Builds row objects for queries that return many rows (i.e., Statement#all).
// The column names are initialized only once and reused for every row.
class LocalRowBuilder {
public:

	explicit LocalRowBuilder(Napi::Env env, sqlite3_stmt* handle, bool safe_ints);
	Napi::Value GetRowJS();

private:

	Napi::Env env;
	sqlite3_stmt* handle;
	int column_count;
	const bool safe_ints;
	CreateObjectWithPropertiesFn create;
	Napi::Value prototype;
	Napi::Value null_value;
	std::vector<napi_value> keys;
	std::vector<napi_value> values;
	std::vector<napi_property_descriptor> properties;
};

// Similar to LocalRowBuilder, but can be reused across separate query calls.
// The cache is rebuilt if SQLite reparses the statement after a schema change.
// This is used to optimize Statement#get and Statement#iterate.
class PersistentRowBuilder {
public:

	explicit PersistentRowBuilder(Napi::Env env);
	Napi::Value GetRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints);

private:

	CreateObjectWithPropertiesFn create;
	Napi::Reference<Napi::Object> prototype;
	std::vector<Napi::Reference<Napi::String>> keys;
	int column_count;
	int reprepare_count;
};
