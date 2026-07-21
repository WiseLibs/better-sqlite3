class Binder {
public:

	explicit Binder(sqlite3_stmt* _handle) {
		handle = _handle;
		param_count = sqlite3_bind_parameter_count(_handle);
		anon_index = 0;
		success = true;
	}

	bool Bind(NODE_ARGUMENTS info, int argc, Statement* stmt) {
		assert(anon_index == 0);
		Napi::Env env = info.Env();
		Result result = BindArgs(info, argc, stmt);
		if (success && result.count != param_count) {
			if (result.count < param_count) {
				if (!result.bound_object && stmt->GetBindMap(env).GetSize()) {
					Fail(ThrowTypeError, env, "Missing named parameters");
				} else {
					Fail(ThrowRangeError, env, "Too few parameter values were provided");
				}
			} else {
				Fail(ThrowRangeError, env, "Too many parameter values were provided");
			}
		}
		return success;
	}

private:

	struct Result {
		int count;
		bool bound_object;
	};

	static Napi::Value GetPrototype(Napi::Env env, Napi::Object obj) {
		napi_value proto;
		// This can fail (e.g., a Proxy whose getPrototypeOf trap throws), in
		// which case an empty value is returned and an exception is pending.
		if (napi_get_prototype(env, obj, &proto) != napi_ok) return Napi::Value();
		return Napi::Value(env, proto);
	}

	// An object is "plain" if its prototype is null or a top-level prototype
	// (i.e., some realm's Object.prototype). Rather than comparing against the
	// current realm's Object.prototype -- which would reject plain objects from
	// other contexts, such as the "vm" module -- we walk to the top of the
	// prototype chain. A plain object's chain is exactly "obj -> proto -> null",
	// so its immediate prototype must itself have a null prototype. This mirrors
	// the cross-realm heuristic used by lodash's isPlainObject.
	static bool IsPlainObject(Napi::Env env, Napi::Object obj) {
		Napi::Value proto = GetPrototype(env, obj);
		if (proto.IsEmpty()) return false;
		if (proto.IsNull()) return true;
		Napi::Value grandproto = GetPrototype(env, proto.As<Napi::Object>());
		if (grandproto.IsEmpty()) return false;
		return grandproto.IsNull();
	}

	void Fail(Napi::Value (*Throw)(Napi::Env, const char*), Napi::Env env, const char* message) {
		assert(success == true);
		assert((Throw == NULL) == (message == NULL));
		assert(Throw == ThrowError || Throw == ThrowTypeError || Throw == ThrowRangeError || Throw == NULL);
		if (Throw) Throw(env, message);
		success = false;
	}

	int NextAnonIndex() {
		while (sqlite3_bind_parameter_name(handle, ++anon_index) != NULL) {}
		return anon_index;
	}

	// Binds the value at the given index or throws an appropriate error.
	void BindValue(Napi::Env env, Napi::Value value, int index) {
		int status = Data::BindValueFromJS(env, handle, index, value);
		if (status != SQLITE_OK) {
			switch (status) {
				case -1:
					return Fail(ThrowTypeError, env, "SQLite3 can only bind numbers, strings, bigints, buffers, and null");
				case SQLITE_TOOBIG:
					return Fail(ThrowRangeError, env, "The bound string, buffer, or bigint is too big");
				case SQLITE_RANGE:
					return Fail(ThrowRangeError, env, "Too many parameter values were provided");
				case SQLITE_NOMEM:
					return Fail(ThrowError, env, "Out of memory");
				default:
					return Fail(ThrowError, env, "An unexpected error occured while trying to bind parameters");
			}
			assert(false);
		}
	}

	// Binds each value in the array or throws an appropriate error.
	// The number of successfully bound parameters is returned.
	int BindArray(Napi::Env env, Napi::Array arr) {
		uint32_t length = arr.Length();
		if (length > INT_MAX) {
			Fail(ThrowRangeError, env, "Too many parameter values were provided");
			return 0;
		}
		int len = static_cast<int>(length);
		for (int i = 0; i < len; ++i) {
			Napi::Value value = SafeGetElement(env, arr, static_cast<uint32_t>(i));
			if (value.IsEmpty()) {
				Fail(NULL, env, NULL);
				return i;
			}
			BindValue(env, value, NextAnonIndex());
			if (!success) {
				return i;
			}
		}
		return len;
	}

	// Binds all named parameters using the values found in the given object.
	// The number of successfully bound parameters is returned.
	// If a named parameter is missing from the object, an error is thrown.
	// This should only be invoked once per instance.
	int BindObject(Napi::Env env, Napi::Object obj, Statement* stmt) {
		BindMap& bind_map = stmt->GetBindMap(env);
		BindMap::Pair* pairs = bind_map.GetPairs();
		int len = bind_map.GetSize();

		for (int i = 0; i < len; ++i) {
			Napi::String key = pairs[i].GetName(env);

			// Check if the named parameter was provided.
			bool has_property;
			if (!SafeHasOwnProperty(env, obj, key, &has_property)) {
				Fail(NULL, env, NULL);
				return i;
			}
			if (!has_property) {
				std::string param_name = key.Utf8Value();
				Fail(ThrowRangeError, env, (std::string("Missing named parameter \"") + param_name + "\"").c_str());
				return i;
			}

			// Get the current property value.
			Napi::Value value = SafeGet(env, obj, key);
			if (value.IsEmpty()) {
				Fail(NULL, env, NULL);
				return i;
			}

			BindValue(env, value, pairs[i].GetIndex());
			if (!success) {
				return i;
			}
		}

		return len;
	}

	// Binds all parameters using the values found in the arguments object.
	// Anonymous parameter values can be directly in the arguments object or in an Array.
	// Named parameter values can be provided in a plain Object argument.
	// Only one plain Object argument may be provided.
	// If an error occurs, an appropriate error is thrown.
	// The return value is a struct indicating how many parameters were successfully bound
	// and whether or not it tried to bind an object.
	Result BindArgs(NODE_ARGUMENTS info, int argc, Statement* stmt) {
		Napi::Env env = info.Env();
		int count = 0;
		bool bound_object = false;

		for (int i = 0; i < argc; ++i) {
			Napi::Value arg = info[i];

			if (arg.IsArray()) {
				count += BindArray(env, arg.As<Napi::Array>());
				if (!success) break;
				continue;
			}

			if (arg.IsObject() && !arg.IsBuffer()) {
				Napi::Object obj = arg.As<Napi::Object>();
				if (IsPlainObject(env, obj)) {
					if (bound_object) {
						Fail(ThrowTypeError, env, "You cannot specify named parameters in two different objects");
						break;
					}
					bound_object = true;

					count += BindObject(env, obj, stmt);
					if (!success) break;
					continue;
				} else if (env.IsExceptionPending()) {
					Fail(NULL, env, NULL);
					break;
				} else if (stmt->GetBindMap(env).GetSize()) {
					Fail(ThrowTypeError, env, "Named parameters can only be passed within plain objects");
					break;
				}
			}

			BindValue(env, arg, NextAnonIndex());
			if (!success) break;
			count += 1;
		}

		return { count, bound_object };
	}

	sqlite3_stmt* handle;
	int param_count;
	int anon_index; // This value should only be used by NextAnonIndex()
	bool success; // This value should only be set by Fail()
};
