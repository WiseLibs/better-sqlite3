#ifndef NODE_SQLITE3_PLUS_WORKER_WRITE_H
#define NODE_SQLITE3_PLUS_WORKER_WRITE_H

#include <nan.h>

class WriteWorker : public Nan::AsyncWorker {
	public:
		WriteWorker(Nan::Callback* cb, bool is_transaction = false)
		: Nan::AsyncWorker(cb)
		, is_transaction(is_transaction) {}
		
		bool const is_transaction;
};

#endif