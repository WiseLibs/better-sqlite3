void Transaction::DeleteHandles::operator() (Transaction* trans) {
	if (trans->handles) {
		for (unsigned int i=0; i<trans->handle_count; ++i) {
			sqlite3_finalize(trans->handles[i]);
		}
		delete[] trans->handles;
		delete[] trans->handle_types;
		trans->handles = NULL;
	}
}
