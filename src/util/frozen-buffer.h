#ifndef NODE_SQLITE3_PLUS_FROZEN_BUFFER_H
#define NODE_SQLITE3_PLUS_FROZEN_BUFFER_H

#include <sys/types.h>

// Immutably stores some data of a given length. Data passed to the constructor
// is cloned, so you still must manage the original data yourself.
class FrozenBuffer {
	public:
		FrozenBuffer(const char* data = NULL, size_t length = 0)
			: data(CloneData(data, length)), length(length) {}
		~FrozenBuffer() {
			delete[] data;
		}
		const char* const data;
		const size_t length;
	
	private:
		static char* CloneData(const char* data, size_t length) {
			if (data == NULL || length == 0) {return NULL;}
			char* clone = new char[length];
			memcpy(clone, data, length);
			return clone;
		}
};

#endif