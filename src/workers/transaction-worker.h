#ifndef NODE_SQLITE3_PLUS_WORKER_TRANSACTION_H
#define NODE_SQLITE3_PLUS_WORKER_TRANSACTION_H

#include <sqlite3.h>
#include <nan.h>
#include "write-worker.h"
class Transaction;

class TransactionWorker : public WriteWorker {
	public:
		TransactionWorker(Transaction*, Nan::Callback*);
		void Execute();
		void HandleErrorCallback();
		void HandleOKCallback();
		
	private:
		void FinishRequest();
		
		Transaction* const trans;
		
		int changes;
		sqlite3_int64 id;
};

#endif