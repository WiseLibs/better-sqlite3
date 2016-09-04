#ifndef NODE_SQLITE3_PLUS_TRANSACTION_H
#define NODE_SQLITE3_PLUS_TRANSACTION_H

// Dependencies
#include <sqlite3.h>
#include <nan.h>
#include "../../util/macros.h"
class Database;

class Transaction : public Nan::ObjectWrap {
	public:
		Transaction();
		~Transaction();
		static void Init();
		
		class CloseHandles { public:
			void operator() (Transaction*);
		};
		
		// Friends
		friend class CloseHandles;
		friend class Database;
		friend class TransactionWorker;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_GETTER(Busy);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Run);
		
		// Sqlite3 interfacing
		Database* db;
		unsigned int handle_count;
		sqlite3_stmt** handles;
		
		// State
		bool config_locked;
		bool bound;
		bool busy;
};

#endif