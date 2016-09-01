#ifndef NODE_SQLITE3_PLUS_WORKER_EACH_H
#define NODE_SQLITE3_PLUS_WORKER_EACH_H

#include <sys/types.h>
#include <sqlite3.h>
#include <nan.h>
#include "statement-worker.h"
#include "../../util/data.h"
#include "../../util/list.h"
class Statement;

class EachWorker : public StatementWorker<Nan::AsyncProgressWorker> {
	public:
		EachWorker(Statement*, sqlite3_stmt*, int, Nan::Callback*, Nan::Callback*);
		~EachWorker();
		void Execute(const Nan::AsyncProgressWorker::ExecutionProgress&);
		void HandleProgressCallback(const char*, size_t);
		void HandleOKCallback();
	private:
		sqlite3_mutex* data_mutex;
		sqlite3_mutex* handle_mutex;
		int column_count;
		bool cached_names;
		List<Data::Row> rows;
		Nan::Callback* progressCallback;
};

#endif