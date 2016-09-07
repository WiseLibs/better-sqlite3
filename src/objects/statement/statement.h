#ifndef BETTER_SQLITE3_STATEMENT_H
#define BETTER_SQLITE3_STATEMENT_H

// Dependencies
#include <stdint.h>
#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "../../util/macros.h"
class Database;

// Class Declaration
class Statement : public Nan::ObjectWrap {
	public:
		Statement();
		~Statement();
		static void Init();
		
		class Compare { public:
			bool operator() (const Statement*, const Statement*);
		};
		
		// Friends
		friend class Compare;
		friend class Database;
		template <class OBJECT, class ASYNC> friend class QueryWorker;
		friend class RunWorker;
		friend class GetWorker;
		friend class AllWorker;
		friend class EachWorker;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_GETTER(Busy);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Pluck);
		static NAN_METHOD(Run);
		static NAN_METHOD(Get);
		static NAN_METHOD(All);
		static NAN_METHOD(Each);
		bool CloseHandles(); // Returns true if the handles were not previously closed
		bool CloseIfPossible(); // Returns true if the statement is not busy
		void BuildBindMap();
		
		// Tools for QueryWorker
		inline void ClearBindings() {
			sqlite3_clear_bindings(st_handle);
		}
		void EraseFromSet();
		
		// Sqlite3 interfacing and state
		Database* db;
		sqlite3_stmt* st_handle;
		int column_count; // If this is 0, the statement is a write statement
		uint8_t state;
		
		// Unique Statement Id
		sqlite3_uint64 id;
};

#endif