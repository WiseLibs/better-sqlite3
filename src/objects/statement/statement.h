#ifndef NODE_SQLITE3_PLUS_STATEMENT_H
#define NODE_SQLITE3_PLUS_STATEMENT_H

// Dependencies
#include <sqlite3.h>
#include <nan.h>
#include "../../util/macros.h"
class Database;
class HandleManager;
class FrozenBuffer;

// Class Declaration
class Statement : public Nan::ObjectWrap {
	public:
		Statement();
		~Statement();
		static void Init();
		
		class DeleteHandles { public:
			void operator() (Statement*);
		};

		
		// Friends
		friend class DeleteHandles;
		friend class Database;
		friend class HandleManager;
		template <class T> friend class StatementWorker;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_METHOD(Cache);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Pluck);
		static NAN_METHOD(Run);
		static NAN_METHOD(Get);
		static NAN_METHOD(All);
		static NAN_METHOD(Each);
		sqlite3_stmt* NewHandle(); // This should only be invoked while db.state == DB_READY
		
		// Sqlite3 interfacing
		Database* db;
		sqlite3* db_handle;
		HandleManager* handles;
		FrozenBuffer* source;
		
		// State
		bool config_locked;
		bool bound;
		unsigned int requests;
		
		// Config
		bool readonly;
		bool pluck_column;
};

#endif