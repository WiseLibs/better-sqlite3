class DataConverter {
public:

	void ThrowDataConversionError(Napi::Env env, sqlite3_context* invocation, bool isBigInt) {
		if (isBigInt) {
			ThrowRangeError(env, (GetDataErrorPrefix() + " a bigint that was too big").c_str());
		} else {
			ThrowTypeError(env, (GetDataErrorPrefix() + " an invalid value").c_str());
		}
		PropagateJSError(invocation);
	}

protected:

	virtual void PropagateJSError(sqlite3_context* invocation) = 0;
	virtual std::string GetDataErrorPrefix() = 0;
};
