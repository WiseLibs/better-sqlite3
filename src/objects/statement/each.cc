// .each(Function dataHandler, Function callback) -> this

NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_LAST_TWO_ARGUMENTS_FUNCTIONS(func_index, func1, func2)
	WORKER_START(stmt, statement);
	EachWorker* worker = new EachWorker(stmt, new Nan::Callback(func2), new Nan::Callback(func1));
	
	if (!(stmt->state & PLUCK_COLUMN)) {
		// Cache column names.
		v8::Local<v8::Array> columnNames = Nan::New<v8::Array>(stmt->column_count);
		for (int i=0; i<stmt->column_count; ++i) {
			Nan::Set(columnNames, (uint32_t)i, NEW_INTERNAL_STRING16(sqlite3_column_name16(stmt->st_handle, i)));
		}
		worker->SaveToPersistent((uint32_t)0, columnNames);
	}
	
	WORKER_BIND(stmt, worker, info, func_index, STATEMENT_BIND, statement);
	WORKER_END(stmt, worker);
}
