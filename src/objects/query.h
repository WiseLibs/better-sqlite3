#ifndef BETTER_SQLITE3_QUERY_H
#define BETTER_SQLITE3_QUERY_H

#include "../util/bind-map.h"

class Query { public:
	virtual BindMap GetBindMap() {
		return BindMap(NULL, 0);
	}
};

#endif