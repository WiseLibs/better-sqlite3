#ifndef NODE_SQLITE3_PLUS_WORKER_GET_H
#define NODE_SQLITE3_PLUS_WORKER_GET_H

#include <sqlite3.h>
#include <nan.h>
#include "statement-worker.h"
#include "../util/data.h"
class Statement;

class GetWorker : public StatementWorker<Nan::AsyncWorker> {
	public:
		GetWorker(Statement*, sqlite3_stmt*, int, int);
		void Execute();
		void HandleOKCallback();
	private:
		const int pluck_column;
		Data::Row row;
};

#endif