#ifndef NODE_SQLITE3_PLUS_LIST_H
#define NODE_SQLITE3_PLUS_LIST_H

#include <cstdlib>

template <class T>
class List {
	private:
		typedef struct Node {
			T* item;
			Node* prev;
		} Node;
		Node* front;
		Node* end;
	public:
		List() : front(NULL), end(NULL) {}
		
		// This is not enough if the items in the list are stored in the heap.
		~List() {
			Node* node = front;
			while (node != NULL) {
				Node* temp = node->prev;
				free(node);
				node = temp;
			}
		}
		
		// Pushes an item onto the list.
		void Add(T* item) {
			Node* new_node = (Node*) malloc(sizeof(Node));
			new_node->item = item;
			new_node->prev = NULL;
			if (end == NULL) {
				front = end = new_node;
			} else {
				end->prev = new_node;
				end = new_node;
			}
		}
		
		// Removes the given item from the list, if found. If the item exists in
		// the list multiple times, only the first instance (first added) is
		// removed.
		void Remove(T* item) {
			if (front == NULL) {return;}
			
			if (front->item == item) {
				Node* temp = front->prev;
				free(front);
				front = temp;
				if (front == NULL) {
					end = NULL;
				}
				return;
			}
			
			Node* node = front;
			while (node->prev != NULL) {
				if (node->prev->item == item) {
					if (node->prev == end) {
						end = node;
					}
					Node* temp = node->prev->prev;
					free(node->prev);
					node->prev = temp;
					break;
				}
				node = node->prev;
			}
		}
		
		// Executes a function for each item in the list.
		// The passed function must not modify the list.
		template <class F> void Each(F fn) {
			Node* node = front;
			while (node != NULL) {
				fn(node->item);
				node = node->prev;
			}
		}
		
		// Executes a function for each item in the list, and removes them all
		// from the list. The passed function must not modify the list.
		// This should be used in the destructor of the owner object, as items
		// in this list are usually dynamically allocated and require their own
		// destruction.
		template <class F> void Flush(F fn) {
			Node* node = front;
			while (node != NULL) {
				fn(node->item);
				Node* temp = node->prev;
				free(node);
				node = temp;
			}
			front = NULL;
			end = NULL;
		}
};

#endif