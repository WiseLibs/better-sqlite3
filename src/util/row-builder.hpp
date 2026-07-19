// Builds row objects efficiently by utilizing a factory function in JS land.
// The column names are initialized only once and reused for every row/query.
// The cache is rebuilt if SQLite reparses the statement after a schema change.
class RowBuilder {
public:

	explicit RowBuilder(
		Napi::Env env,
		Napi::Function row_factory,
		Napi::Function array_factory
	);

	Napi::Value GetRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints);
	Napi::Value GetRawRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints);

private:
	Napi::FunctionReference row_factory;
	Napi::FunctionReference create_row;
	Napi::FunctionReference array_factory;
	int column_count;
	int reprepare_count;
};
