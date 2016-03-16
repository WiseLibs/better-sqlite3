#ifndef NODE_SQLITE3_PLUS_WORKER_CLOSE_H
#define NODE_SQLITE3_PLUS_WORKER_CLOSE_H

#include <nan.h>
class Database;

class CloseWorker : public Nan::AsyncWorker {
	public:
		CloseWorker(Database*, bool);
		void Execute();
		void HandleOKCallback();
		void HandleErrorCallback();
	private:
		Database* const db;
		bool still_connecting;
};

#endif