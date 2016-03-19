#ifndef NODE_SQLITE3_PLUS_HANDLE_MANAGER_H
#define NODE_SQLITE3_PLUS_HANDLE_MANAGER_H

#include <sqlite3.h>
#include "../objects/statement/statement.h"

// This is used by Statements to manage their cache of sqlite3_stmt handles.
// Use the Request() method to get a reference to an available handle. If a
// handle is not available, a new one is created. If a handle could not be
// created, the handle argument is set to NULL. The return value is an integer
// that must be eventually passed to Release(), in order to make that handle
// available again (or free the memory of a temporary handle).
// 
// When you create a new HandleManager, you need to invoke Fill(), passing a
// function whose return values are the handles to fill the HandleManager with.
// If Fill() returns non-zero, it's because one of the handles was NULL, and
// therefore the HandleManager should be considered unusable.
class HandleManager {
	public:
		HandleManager(Statement* stmt, int count)
		: count(count)
		, stmt(stmt)
		, next_handle(0) {
			handles = new sqlite3_stmt* [count]();
			handle_states = new bool [count]();
		}
		~HandleManager() {
			for (int i=0; i<count; i++) {
				sqlite3_finalize(handles[i]);
			}
			delete[] handles;
			delete[] handle_states;
		}
		template <class F> int Fill(F fn) {
			for (int i=0; i<count; i++) {
				if ((handles[i] = fn()) == NULL) {
					return 1;
				}
			}
			return 0;
		}
		int Request(sqlite3_stmt** handle) {
			if (!handle_states[next_handle]) {
				handle_states[next_handle] = true;
				*handle = handles[next_handle];
				int ret = next_handle;
				if (++next_handle >= count) {
					next_handle = 0;
				}
				return ret;
			}
			*handle = stmt->NewHandle();
			return -1;
		}
		void Release(int index, sqlite3_stmt* handle) {
			if (index == -1) {
				sqlite3_finalize(handle);
			} else {
				handle_states[index] = false;
				sqlite3_reset(handle);
			}
		}
		sqlite3_stmt* GetFirst() {
			return handles[0];
		}
		void SetFirst(sqlite3_stmt* handle) {
			handles[0] = handle;
		}
		
		const int count;
		
	private:
		Statement* stmt;
		int next_handle;
		sqlite3_stmt** handles;
		bool* handle_states;
};

#endif