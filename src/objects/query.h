#ifndef BETTER_SQLITE3_QUERY_H
#define BETTER_SQLITE3_QUERY_H

#include <sqlite3.h>
#include "../util/bind-map.h"

class QueryExtras { public:
	explicit QueryExtras() : bind_map() {}
	sqlite3_uint64 id;
	BindMap bind_map;
};

class Query {
public:
	explicit Query() : extras(new QueryExtras()) {}
	~Query() {delete extras;}
	
	class Compare { public:
		bool operator() (const Query* a, const Query* b) const {
			return a->extras->id < b->extras->id;
		}
	};
	friend class Compare;
	
	virtual BindMap* GetBindMap() {
		return &extras->bind_map;
	}
protected:
	QueryExtras* extras;
};

#endif