#ifndef BETTER_SQLITE3_BIND_MAP_H
#define BETTER_SQLITE3_BIND_MAP_H

#include <string>

typedef struct BindPair {
	std::string name;
	int index;
} BindPair;

class BindMap { public:
	explicit BindMap(BindPair* pairs, int length) : pairs(pairs), length(length) {}
	static BindPair* Grow(BindPair* source, int* source_length) {
		int len = *source_length;
		int grow_by = (len << 1) | 2;
		BindPair* dest = new BindPair[len + grow_by];
		for (int i=0; i<len; ++i) {
			dest[i] = source[i];
		}
		delete[] source;
		*source_length += grow_by;
		return dest;
	}
	BindPair* pairs;
	int length;
};

#endif