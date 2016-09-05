#ifndef NODE_SQLITE3_PLUS_WORKER_RUN_H
#define NODE_SQLITE3_PLUS_WORKER_RUN_H

#include <sqlite3.h>
#include <nan.h>
#include "../query-worker.h"
class Statement;

class RunWorker : public QueryWorker<Statement, Nan::AsyncWorker> {
	public:
		RunWorker(Statement*, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
	private:
		int changes;
		sqlite3_int64 id;
};

#endif