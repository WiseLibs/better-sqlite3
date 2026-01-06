class DataConverter {
public:

	void ThrowDataConversionError(sqlite3_context* invocation, bool isBigInt) {
		if (isBigInt) {
			ThrowRangeError((GetDataErrorPrefix() + " a bigint that was too big").c_str());
		} else {
			ThrowTypeError((GetDataErrorPrefix() + " an invalid value").c_str());
		}
		PropagateJSError(invocation);
	}

protected:

	virtual void PropagateJSError(sqlite3_context* invocation) = 0;
	virtual std::string GetDataErrorPrefix() = 0;
};
