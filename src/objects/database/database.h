#ifndef NODE_SQLITE3_PLUS_DATABASE_H
#define NODE_SQLITE3_PLUS_DATABASE_H

// Dependencies
#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "../statement/statement.h"
#include "../transaction/transaction.h"
#include "../../util/macros.h"
#include "../../util/transaction-handles.h"

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
		friend class Transaction;
		template <class OBJECT, class ASYNC> friend class QueryWorker;
		friend class TransactionWorker;
		
	private:
		static NAN_METHOD(New);
		static NAN_GETTER(Open);
		static NAN_METHOD(Close);
		static NAN_METHOD(Prepare);
		static NAN_METHOD(CreateTransaction);
		int CloseHandles();
		void MaybeClose();
		
		// Sqlite3 interfacing
		sqlite3* read_handle;
		sqlite3* write_handle;
		TransactionHandles* t_handles;
		
		// State
		DB_STATE state;
		unsigned int workers;
		
		// Associated Statements and Transactions
		std::set<Statement*, Statement::Compare> stmts;
		std::set<Transaction*, Transaction::Compare> transs;
};

#endif