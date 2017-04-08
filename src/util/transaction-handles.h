#ifndef BETTER_SQLITE3_TRANSACTION_HANDLES_H
#define BETTER_SQLITE3_TRANSACTION_HANDLES_H

#include <sqlite3.h>

// A simple construct for holding three sqlite3_stmt pointers.
// After invoking open(), if SQLITE_OK is returned, the three pointers can be
// used to start, commit, and rollback transactions.
// This object does not own its own data. The owner of this object must
// manually invoke close() to free the memory held by the three pointers.
class TransactionHandles { public:
	explicit TransactionHandles() : begin(NULL), commit(NULL), rollback(NULL) {}
	
	int open(sqlite3* db_handle) {
		int status;
		
		status = sqlite3_prepare_v2(db_handle, "BEGIN TRANSACTION;", -1, &begin, NULL);
		if (status != SQLITE_OK) {
			return status;
		}
		
		status = sqlite3_prepare_v2(db_handle, "COMMIT TRANSACTION;", -1, &commit, NULL);
		if (status != SQLITE_OK) {
			return status;
		}
		
		return sqlite3_prepare_v2(db_handle, "ROLLBACK TRANSACTION;", -1, &rollback, NULL);
	}
	
	void close() {
		sqlite3_finalize(begin);
		sqlite3_finalize(commit);
		sqlite3_finalize(rollback);
		begin = NULL;
		commit = NULL;
		rollback = NULL;
	}
	
	sqlite3_stmt* begin;
	sqlite3_stmt* commit;
	sqlite3_stmt* rollback;
};

#endif