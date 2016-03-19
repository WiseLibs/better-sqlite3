// Only use while db.state == DB_READY

sqlite3_stmt* Statement::NewHandle() {
	sqlite3_stmt* handle;
	sqlite3_prepare_v2(db_handle, source->data, source->length, &handle, NULL);
	return handle;
}
