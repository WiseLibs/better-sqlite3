#ifndef BETTER_SQLITE3_TRANSACTION_HANDLES_H
#define BETTER_SQLITE3_TRANSACTION_HANDLES_H

#include <sqlite3.h>

// A simple construct for holding three sqlite3_stmt pointers.
// After construction, if statusOut is SQLITE_OK, the three pointers
// can be used to start, commit, and rollback transactions.
class TransactionHandles {
	public:
		TransactionHandles(sqlite3* db_handle, int* statusOut)
		: begin(NULL)
		, commit(NULL)
		, rollback(NULL) {
			int status;
			
			status = sqlite3_prepare_v2(db_handle, "BEGIN TRANSACTION;", -1, &begin, NULL);
			if (status != SQLITE_OK) {
				*statusOut = status;
				return;
			}
			
			status = sqlite3_prepare_v2(db_handle, "COMMIT TRANSACTION;", -1, &commit, NULL);
			if (status != SQLITE_OK) {
				*statusOut = status;
				return;
			}
			
			*statusOut = sqlite3_prepare_v2(db_handle, "ROLLBACK TRANSACTION;", -1, &rollback, NULL);
		}
		~TransactionHandles() {
			sqlite3_finalize(begin);
			sqlite3_finalize(commit);
			sqlite3_finalize(rollback);
		}
		
	public:
		sqlite3_stmt* begin;
		sqlite3_stmt* commit;
		sqlite3_stmt* rollback;
};

#endif