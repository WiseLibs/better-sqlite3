#ifndef BETTER_SQLITE3_WORKER_CHECKPOINT_H
#define BETTER_SQLITE3_WORKER_CHECKPOINT_H

#include <nan.h>
class Database;

class CheckpointWorker : public Nan::AsyncWorker {
	public:
		CheckpointWorker(Database*, bool, Nan::Callback*);
		void Execute();
		void HandleOKCallback();
		void HandleErrorCallback();
	private:
		Database* const db;
		bool force;
		double fraction_checkpointed;
};

#endif