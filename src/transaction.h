#ifndef NODE_SQLITE3_PLUS_TRANSACTION_H
#define NODE_SQLITE3_PLUS_TRANSACTION_H

#include <nan.h>
#include "macros.h"

class Transaction : public Nan::ObjectWrap {
	public:
		Transaction();
		~Transaction();
		static void Init();
		
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		
		bool closed;
};

#endif