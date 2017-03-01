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
extern Nan::Persistent<v8::Function> NullFactory;

// Class Declaration
class Database : public Nan::ObjectWrap {
	public:
		explicit Database();
		~Database();
		static void Init(v8::Local<v8::Object>, v8::Local<v8::Object>);
		
		// Friends
		friend class Statement;
		friend class Transaction;
		
	private:
		static NAN_METHOD(New);
		static NAN_GETTER(Open);
		static NAN_METHOD(Close);
		static NAN_METHOD(CreateStatement);
		static NAN_METHOD(CreateTransaction);
		static NAN_METHOD(Exec);
		static NAN_METHOD(Pragma);
		static NAN_METHOD(Checkpoint);
		static NAN_METHOD(DefaultSafeIntegers);
		int OpenHandles(const char*); // If SQLITE_OK is not returned, CloseHandles should be invoked
		int CloseHandles();
		void CloseChildHandles();
		
		// Sqlite3 interfacing
		sqlite3* db_handle;
		TransactionHandles* t_handles;
		
		// State
		bool open;
		bool in_each;
		bool safe_ints;
		
		// Associated Statements and Transactions
		std::set<Statement*, Statement::Compare> stmts;
		std::set<Transaction*, Transaction::Compare> transs;
};

#endif