#ifndef BETTER_SQLITE3_SQL_ROPE_H
#define BETTER_SQLITE3_SQL_ROPE_H

#include <cstdlib>
#include <cstring>
#include <stdint.h>

class RopeNode { public:
	explicit RopeNode(v8::Local<v8::String> string) : value(string) {
		add_semicolon = (*value)[value.length() - 1] != 0x3b;
	}
	v8::String::Value value;
	bool add_semicolon;
};

// This class is used to store a sequence of UTF-16 SQL strings and provides the
// ability to efficiently concatenate them together, ensuring that each one ends
// with a semicolon and is separated by a newline character.
class SQLRope {
public:
	explicit SQLRope(unsigned int capacity) : weight(0), length(0) {
		nodes = static_cast<RopeNode*>(malloc(capacity * sizeof(RopeNode)));
	}
	~SQLRope() {
		while (length) {nodes[--length].~RopeNode();}
		free(nodes);
	}
	inline void Push(v8::Local<v8::String> string) {
		RopeNode* node = new (nodes + length++) RopeNode(string);
		weight += node->value.length() + static_cast<int>(node->add_semicolon);
	}
	inline v8::String::Value* Get(unsigned int index) {
		return &nodes[index].value;
	}
	inline size_t GetConcatLength() {
		return weight + length - 1;
	}
	
	// The buffer returned by this method must be delete[]d by the caller.
	// This method's argument should be the value returned by GetConcatLength().
	const uint16_t* Concat(size_t concat_length) {
		size_t offset = 0;
		uint16_t* buffer = new uint16_t[concat_length];
		for (RopeNode* node = nodes, * end = nodes + length; node != end; ++node) {
			if (node != nodes) {
				buffer[offset++] = 0xa;
			}
			size_t chunk_weight = node->value.length();
			memcpy(buffer + offset, *(node->value), chunk_weight * sizeof(uint16_t));
			offset += chunk_weight;
			if (node->add_semicolon) {
				buffer[offset++] = 0x3b;
			}
		}
		return buffer;
	}
private:
	RopeNode* nodes;
	size_t weight;
	unsigned int length;
};

#endif