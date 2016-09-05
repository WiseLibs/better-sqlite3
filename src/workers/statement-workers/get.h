#ifndef NODE_SQLITE3_PLUS_WORKER_GET_H
#define NODE_SQLITE3_PLUS_WORKER_GET_H

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