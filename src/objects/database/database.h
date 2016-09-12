#ifndef BETTER_SQLITE3_DATABASE_H
#define BETTER_SQLITE3_DATABASE_H

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
		friend class Statement;
		friend class Transaction;
		friend class OpenWorker;
		friend class CloseWorker;
		friend class CheckpointWorker;
		template <class OBJECT, class ASYNC> friend class QueryWorker;
		friend class GetWorker;
		friend class AllWorker;
		friend class EachWorker;
		friend class RunWorker;
		friend class TransactionWorker;
		
	private:
		static NAN_METHOD(New);
		static NAN_GETTER(Open);
		static NAN_METHOD(Close);
		static NAN_METHOD(CreateStatement);
		static NAN_METHOD(CreateTransaction);
		static NAN_METHOD(Pragma);
		static NAN_METHOD(Checkpoint);
		int CloseHandles();
		void MaybeClose();
		
		// Sqlite3 interfacing
		sqlite3* read_handle;
		sqlite3* write_handle;
		TransactionHandles* t_handles;
		
		// State
		DB_STATE state;
		unsigned int workers;
		unsigned int checkpoints;
		
		// Associated Statements and Transactions
		std::set<Statement*, Statement::Compare> stmts;
		std::set<Transaction*, Transaction::Compare> transs;
};

#endif