// .close() -> this

NAN_METHOD(Database::Close) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	if (db->state != DB_DONE) {
		db->Ref();
		db->workers += 1;
		
		// Try to close as many query objects as possible. If some queries are
		// busy, we'll have to wait for the last QueryWorker to actually close
		// the database.
		std::set<Statement*, Statement::Compare>::iterator stmts_it = db->stmts.begin();
		std::set<Statement*, Statement::Compare>::iterator stmts_end = db->stmts.end();
		while (stmts_it != stmts_end) {
			if ((*stmts_it)->CloseIfPossible()) {
				stmts_it = db->stmts.erase(stmts_it);
			} else {
				++stmts_it;
			}
		}
		std::set<Transaction*, Transaction::Compare>::iterator transs_it = db->transs.begin();
		std::set<Transaction*, Transaction::Compare>::iterator transs_end = db->transs.end();
		while (transs_it != transs_end) {
			if ((*transs_it)->CloseIfPossible()) {
				transs_it = db->transs.erase(transs_it);
			} else {
				++transs_it;
			}
		}
		db->MaybeClose();
		
		// This must be after the MaybeClose() attempt, so the CloseWorker
		// can detect if the database is still connecting.
		db->state = DB_DONE;
	}
	
	info.GetReturnValue().Set(info.This());
}

void Database::MaybeClose() {
	if (stmts.empty() && transs.empty() && checkpoints == 0) {
		Nan::AsyncQueueWorker(new CloseWorker(this, state == DB_CONNECTING));
	}
}
