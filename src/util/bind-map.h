#ifndef BETTER_SQLITE3_BIND_MAP_H
#define BETTER_SQLITE3_BIND_MAP_H

#include "./macros.h"

const int parameter_bits = 10;
const int parameter_mask = (1 << parameter_bits) - 1;
const int max_transaction_length = (1 << ((sizeof(int) * 8) - parameter_bits)) - 1;

class BindPair { public:
	~BindPair() {name.Reset();}
	v8::Persistent<v8::String> name;
	int index;
};

class BindMap { public:
	explicit BindMap() : pairs(NULL), length(0) {}
	~BindMap() {delete[] pairs;}
	static inline int GetParameterIndex(int index) {
		return index & parameter_mask;
	}
	static inline int GetTransactionIndex(int index) {
		return index >> parameter_bits;
	}
	inline void Add(v8::Isolate* isolate, const char* name, int index) {
		pairs[length].name.Reset(isolate, InternalizedFromUtf8(isolate, name, -1));
		pairs[length].index = index;
		length += 1;
	}
	inline void Add(v8::Isolate* isolate, const char* name, int parameter_index, int transaction_index) {
		Add(isolate, name, parameter_index | (transaction_index << parameter_bits));
	}
	void Grow(v8::Isolate* isolate, int* capacity) {
		int new_capacity = (*capacity << 1) | 2;
		BindPair* new_pairs = new BindPair[new_capacity];
		for (int i=0; i<length; ++i) {
			new_pairs[i].name.Reset(isolate, pairs[i].name);
			new_pairs[i].index = pairs[i].index;
		}
		delete[] pairs;
		pairs = new_pairs;
		*capacity = new_capacity;
	}
	BindPair* pairs;
	int length;
};

#endif