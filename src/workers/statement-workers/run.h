#ifndef NODE_SQLITE3_PLUS_WORKER_RUN_H
#define NODE_SQLITE3_PLUS_WORKER_RUN_H

#include <sqlite3.h>
#include <nan.h>
#include "statement-worker.h"
#include "../write-worker.h"
class Statement;

class RunWorker : public StatementWorker<WriteWorker> {
	public:
		RunWorker(Statement*, sqlite3_stmt*, int, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
	private:
		int changes;
		sqlite3_int64 id;
};

#endif