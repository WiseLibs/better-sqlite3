#ifndef NODE_SQLITE3_PLUS_WORKER_OPEN_H
#define NODE_SQLITE3_PLUS_WORKER_OPEN_H

#include <nan.h>
class Database;

class OpenWorker : public Nan::AsyncWorker {
	public:
		OpenWorker(Database*, char*);
		~OpenWorker();
		void Execute();
		void HandleOKCallback();
		void HandleErrorCallback();
	private:
		Database* const db;
		const char* const filename;
};

#endif