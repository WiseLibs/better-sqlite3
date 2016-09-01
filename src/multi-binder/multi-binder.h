#ifndef NODE_SQLITE3_PLUS_MULTIBINDER_H
#define NODE_SQLITE3_PLUS_MULTIBINDER_H

#include <sqlite3.h>
#include "../binder/binder.h"

class MultiBinder : public Binder {
	public:
		MultiBinder(sqlite3_stmt**, unsigned int);
		~MultiBinder();
		void Bind(Nan::NAN_METHOD_ARGS_TYPE, int);
		
	protected:
		unsigned int NextAnonIndex();
		unsigned int BindObject(v8::Local<v8::Object>); // This should only be invoked once per handle
		
		sqlite3_stmt** const handles;
		unsigned int const handle_count;
		unsigned int handle_index;
		unsigned int param_count_sum;
};

#endif