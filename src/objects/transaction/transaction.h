#ifndef BETTER_SQLITE3_TRANSACTION_H
#define BETTER_SQLITE3_TRANSACTION_H

// Dependencies
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../query.h"
#include "../../util/macros.h"
class Database;

class Transaction : public Nan::ObjectWrap, public Query {
	public:
		explicit Transaction();
		~Transaction();
		static void Init();
		
		class Compare { public:
			bool operator() (const Transaction*, const Transaction*) const;
		};
		v8::Local<v8::Object> GetBindMap();
		
		// Friends
		friend class Compare;
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_METHOD(SafeIntegers);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Run);
		bool CloseHandles(); // Returns true if the handles were not previously closed
		
		sqlite3_uint64 id; // Unique Transaction Id
		Database* db;
		sqlite3_stmt** handles;
		unsigned int handle_count;
		uint8_t state;
};

#endif