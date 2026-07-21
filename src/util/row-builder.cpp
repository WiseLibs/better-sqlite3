RowBuilder::RowBuilder(
	Napi::Env env,
	Napi::Function row_factory,
	Napi::Function array_factory
) :
	row_factory(Napi::Persistent(row_factory)),
	array_factory(Napi::Persistent(array_factory)),
	column_count(-1),
	reprepare_count(-1) {}

Napi::Value RowBuilder::GetRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints) {
	int current_reprepare_count = sqlite3_stmt_status(handle, SQLITE_STMTSTATUS_REPREPARE, false);
	if (current_reprepare_count != reprepare_count) {
		column_count = sqlite3_column_count(handle);
		std::vector<napi_value> keys(column_count);
		for (int i = 0; i < column_count; ++i) {
			keys[i] = InternalizedFromUtf8(env, sqlite3_column_name(handle, i), -1);
		}
		create_row = Napi::Persistent(
			SafeCall(env, row_factory.Value(), env.Undefined(), column_count, keys.data())
				.As<Napi::Function>()
		);
		reprepare_count = current_reprepare_count;
	}

	napi_value value_storage[16];
	std::vector<napi_value> extra_values;
	napi_value* values = value_storage;
	if (column_count > 16) {
		extra_values.resize(column_count);
		values = extra_values.data();
	}
	for (int i = 0; i < column_count; ++i) {
		values[i] = Data::GetValueJS(env, handle, i, safe_ints);
	}

	return SafeCall(env, create_row.Value(), env.Undefined(), column_count, values);
}

Napi::Value RowBuilder::GetRawRowJS(Napi::Env env, sqlite3_stmt* handle, bool safe_ints) {
	column_count = sqlite3_column_count(handle);
	napi_value arg_storage[16];
	std::vector<napi_value> extra_args;
	napi_value* args = arg_storage;
	if (column_count > 16) {
		extra_args.resize(column_count);
		args = extra_args.data();
	}
	for (int i = 0; i < column_count; ++i) {
		args[i] = Data::GetValueJS(env, handle, i, safe_ints);
	}
	return SafeCall(env, array_factory.Value(), env.Undefined(), column_count, args);
}
