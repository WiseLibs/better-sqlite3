#ifndef NODE_SQLITE3_PLUS_DATABASE_H
#define NODE_SQLITE3_PLUS_DATABASE_H

// Dependencies
#include <sqlite3.h>
#include <nan.h>
#include "../../util/macros.h"
#include "../../util/list.h"
class Statement;

// Globals
extern bool CONSTRUCTING_PRIVILEGES;
enum DB_STATE {DB_CONNECTING, DB_READY, DB_DONE};

// Class Declaration
class Database : public Nan::ObjectWrap {
	public:
		Database();
		~Database();
		static NAN_MODULE_INIT(Init);
		
		// Friends
		friend class OpenWorker;
		friend class CloseWorker;
		friend class Statement;
		template <class T> friend class StatementWorker;
		
	private:
		static NAN_METHOD(New);
		static NAN_GETTER(Open);
		static NAN_METHOD(Close);
		static NAN_METHOD(Prepare);
		static NAN_METHOD(Begin);
		static void CloseHandles(Database*);
		void ActuallyClose();
		
		// Sqlite3 interfacing
		sqlite3* read_handle;
		sqlite3* write_handle;
		
		// State
		DB_STATE state;
		unsigned int requests;
		unsigned int workers;
		
		// Associated Statements
		List<Statement> stmts;
};

#endif