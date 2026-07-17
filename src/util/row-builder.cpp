// Builds row objects for queries that return many rows (see Statement::JS_all).
// The column names are converted into JavaScript strings only once, and then
// reused for every row; Node-API has no equivalent of V8's internalized
// strings, so recreating the keys for each row would be needlessly expensive.
// The cached keys are local handles, so a RowBuilder must not outlive the
// handle scope it was created in.
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
		keys() {}

	Napi::Value GetRowJS() {
		if (column_count < 0) {
			column_count = sqlite3_column_count(handle);
			keys.reserve(column_count);
			for (int i = 0; i < column_count; ++i) {
				keys.emplace_back(
					InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1)
				);
			}
		}

		Napi::Object row = Napi::Object::New(env);
		for (int i = 0; i < column_count; ++i) {
			row.Set(
				keys[i],
				Data::GetValueJS(env, handle, i, safe_ints)
			);
		}

		return row;
	}

private:
	Napi::Env env;
	sqlite3_stmt* handle;
	int column_count;
	const bool safe_ints;
	std::vector<Napi::String> keys;
};
