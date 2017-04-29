#ifndef BETTER_SQLITE3_STATEMENT_H
#define BETTER_SQLITE3_STATEMENT_H

// Dependencies
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../query.h"
#include "../../util/macros.h"
class Database;
class BindMap;

// Class Declaration
class Statement : public Nan::ObjectWrap, public Query {
	public:
		explicit Statement();
		~Statement();
		static void Init();
		
		BindMap* GetBindMap();
		
		// Friends
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_GETTER(ReturnsData);
		static NAN_METHOD(SafeIntegers);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Pluck);
		static NAN_METHOD(Run);
		static NAN_METHOD(Get);
		static NAN_METHOD(All);
		static NAN_METHOD(Each);
		bool CloseHandles(); // Returns true if the handles were not previously closed
		
		Database* db;
		sqlite3_stmt* st_handle;
		uint8_t state;
};

#endif