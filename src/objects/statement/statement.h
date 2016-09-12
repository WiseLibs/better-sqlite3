#ifndef BETTER_SQLITE3_STATEMENT_H
#define BETTER_SQLITE3_STATEMENT_H

// Dependencies
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "../query.h"
#include "../../util/macros.h"
class Database;

// Class Declaration
class Statement : public Nan::ObjectWrap, public Query {
	public:
		Statement();
		~Statement();
		static void Init();
		
		class Compare { public:
			bool operator() (const Statement*, const Statement*);
		};
		v8::Local<v8::Object> GetBindMap();
		
		// Friends
		friend class Compare;
		friend class Database;
		
	private:
		static CONSTRUCTOR(constructor);
		static NAN_METHOD(New);
		static NAN_GETTER(Readonly);
		static NAN_METHOD(Bind);
		static NAN_METHOD(Pluck);
		static NAN_METHOD(Run);
		static NAN_METHOD(Get);
		static NAN_METHOD(All);
		static NAN_METHOD(Each);
		bool CloseHandles(); // Returns true if the handles were not previously closed
		
		// Sqlite3 interfacing and state
		Database* db;
		sqlite3_stmt* st_handle;
		int column_count; // If this is 0, the statement is a write statement
		uint8_t state;
		
		// Unique Statement Id
		sqlite3_uint64 id;
};

#endif