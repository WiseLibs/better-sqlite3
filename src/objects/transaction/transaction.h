#ifndef NODE_SQLITE3_PLUS_TRANSACTION_H
#define NODE_SQLITE3_PLUS_TRANSACTION_H

#include <nan.h>
#include "../../util/macros.h"

class Transaction : public Nan::ObjectWrap {
	public:
		Transaction();
		~Transaction();
		static void Init();
		
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
};

#endif