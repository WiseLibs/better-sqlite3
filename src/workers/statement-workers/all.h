#ifndef BETTER_SQLITE3_WORKER_ALL_H
#define BETTER_SQLITE3_WORKER_ALL_H

#include <sqlite3.h>
#include <nan.h>
#include "../query-worker.h"
#include "../../util/data.h"
#include "../../util/list.h"
class Statement;

class AllWorker : public QueryWorker<Statement, Nan::AsyncWorker> {
	public:
		AllWorker(Statement*, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
	private:
		unsigned int row_count;
		List<Data::Row> rows;
};

#endif