#ifndef NODE_SQLITE3_PLUS_WORKER_ALL_H
#define NODE_SQLITE3_PLUS_WORKER_ALL_H

#include <sqlite3.h>
#include <nan.h>
#include "statement-worker.h"
#include "../util/data.h"
#include "../util/list.h"
class Statement;

class AllWorker : public StatementWorker<Nan::AsyncWorker> {
	public:
		AllWorker(Statement*, sqlite3_stmt*, int, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
	private:
		int column_count;
		int row_count;
		List<Data::Row> rows;
};

#endif