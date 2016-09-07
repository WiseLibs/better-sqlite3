#ifndef BETTER_SQLITE3_WORKER_GET_H
#define BETTER_SQLITE3_WORKER_GET_H

#include <sqlite3.h>
#include <nan.h>
#include "../query-worker.h"
#include "../../util/data.h"
class Statement;

class GetWorker : public QueryWorker<Statement, Nan::AsyncWorker> {
	public:
		GetWorker(Statement*, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
	private:
		Data::Row row;
};

#endif