// .all(...any boundValues) -> array of rows or plucked columns

NAN_METHOD(Statement::All) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->column_count == 0) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	QUERY_START(stmt, statement, STATEMENT_BIND, info, info.Length());
	
	unsigned int row_count = 0;
	List<Data::Row> rows;
	
	while (sqlite3_step(stmt->st_handle) == SQLITE_ROW) {
		++row_count;
		rows.Add(new Data::Row(stmt->st_handle, stmt->column_count));
	}
	if (sqlite3_reset(stmt->st_handle) == SQLITE_OK) {
		v8::Local<v8::Array> returned_array = Nan::New<v8::Array>(row_count);
		
		// Get array of result rows or plucked columns.
		if (row_count > 0) {
			unsigned int i = 0;
			if (stmt->state & PLUCK_COLUMN) {
				// Fill array with plucked columns.
				rows.Flush([&returned_array, &i] (Data::Row* row) {
					Nan::Set(returned_array, i++, row->values[0]->ToJS());
				});
			} else {
				// Fill array with row objects.
				rows.Flush([&stmt, &returned_array, &i] (Data::Row* row) {
					v8::Local<v8::Object> object = Nan::New<v8::Object>();
					for (int j=0; j<row->column_count; ++j) {
						Nan::Set(object, NEW_INTERNAL_STRING16(sqlite3_column_name16(stmt->st_handle, j)), row->values[j]->ToJS());
					}
					Nan::Set(returned_array, i++, object);
				});
			}
		}
		QUERY_RETURN(stmt, STATEMENT_CLEAR_BINDINGS, returned_array);
	}
	
	QUERY_THROW(stmt, STATEMENT_CLEAR_BINDINGS, sqlite3_errmsg(stmt->db->db_handle));
}
