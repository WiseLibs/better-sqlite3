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
		
		class DeleteHandles { public:
			void operator() (Transaction*);
		};
		
		// Friends
		friend class DeleteHandles;
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Pluck);
		
		// Sqlite3 interfacing
		Database* db;
		unsigned int handle_count;
		sqlite3_stmt** handles;
		bool* handle_types; // True means writer, false means readonly.
		
		// State
		bool config_locked;
		bool bound;
		bool busy;
		
		// Config
		bool returns_data;
		bool pluck_column;
};

#endif