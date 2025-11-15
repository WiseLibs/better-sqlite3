class RowBuilder {
public:

	explicit RowBuilder(
		v8::Isolate* isolate,
		sqlite3_stmt* handle,
		bool safe_ints
	) :
		isolate(isolate),
		handle(handle),
		column_count(-1),
		safe_ints(safe_ints),
		keys(isolate) {}

	v8::Local<v8::Value> GetRowJS() {
		if (column_count < 0) {
			column_count = sqlite3_column_count(handle);
			keys.reserve(column_count);
			for (int i = 0; i < column_count; ++i) {
				keys.emplace_back(
					InternalizedFromUtf8(isolate, sqlite3_column_name(handle, i), -1)
						.As<v8::Name>()
				);
			}
		}

		v8::LocalVector<v8::Value> values(isolate);
		values.reserve(column_count);
		for (int i = 0; i < column_count; ++i) {
			values.emplace_back(
				Data::GetValueJS(isolate, handle, i, safe_ints)
			);
		}

		return v8::Object::New(isolate,
			GET_PROTOTYPE(v8::Object::New(isolate)),
			keys.data(),
			values.data(),
			column_count
		);
	}

private:
	v8::Isolate* isolate;
	sqlite3_stmt* handle;
	int column_count;
	const bool safe_ints;
	v8::LocalVector<v8::Name> keys;
};
