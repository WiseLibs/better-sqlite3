#ifndef BETTER_SQLITE3_TRANSACTION_H
#define BETTER_SQLITE3_TRANSACTION_H

// Dependencies
#include <stdint.h>
#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "../query.h"
#include "../../util/macros.h"
class Database;

class Transaction : public Nan::ObjectWrap, public Query {
	public:
		Transaction();
		~Transaction();
		static void Init();
		
		class Compare { public:
			bool operator() (const Transaction*, const Transaction*);
		};
		v8::Local<v8::Object> GetBindMap();
		
		// Friends
		friend class Compare;
		friend class Database;
		template <class OBJECT, class ASYNC> friend class QueryWorker;
		friend class TransactionWorker;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_GETTER(Busy);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Run);
		bool CloseHandles(); // Returns true if the handles were not previously closed
		bool CloseIfPossible(); // Returns true if the transaction is not busy
		
		// Tools for QueryWorker
		inline void ClearBindings() {
			for (unsigned int i=0; i<handle_count; ++i) {
				sqlite3_clear_bindings(handles[i]);
			}
		}
		void EraseFromSet();
		
		// Sqlite3 interfacing and state
		Database* db;
		unsigned int handle_count;
		sqlite3_stmt** handles;
		uint8_t state;
		
		// Unique Transaction Id
		sqlite3_uint64 id;
};

#endif