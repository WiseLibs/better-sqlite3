#ifndef BETTER_SQLITE3_TRANSACTION_H
#define BETTER_SQLITE3_TRANSACTION_H

// Dependencies
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../query.h"
#include "../../util/macros.h"
class Database;
class BindMap;

class Transaction : public Nan::ObjectWrap, public Query {
	public:
		explicit Transaction();
		~Transaction();
		static void Init();
		
		BindMap* GetBindMap();
		
		// Friends
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_METHOD(SafeIntegers);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Run);
		bool CloseHandles(); // Returns true if the handles were not previously closed
		
		Database* db;
		sqlite3_stmt** handles;
		unsigned int handle_count;
		uint8_t state;
};

#endif