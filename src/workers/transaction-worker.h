#ifndef BETTER_SQLITE3_WORKER_TRANSACTION_H
#define BETTER_SQLITE3_WORKER_TRANSACTION_H

#include <set>
#include <sqlite3.h>
#include <nan.h>
#include "query-worker.h"
class Transaction;

class TransactionWorker : public QueryWorker<Transaction, Nan::AsyncWorker> {
	public:
		TransactionWorker(Transaction*, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
		
	private:
		int changes;
		sqlite3_int64 id;
};

#endif