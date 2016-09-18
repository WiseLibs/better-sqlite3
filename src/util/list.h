#ifndef BETTER_SQLITE3_LIST_H
#define BETTER_SQLITE3_LIST_H

template <class T>
class List {
	private:
		typedef struct Node {
			T item;
			Node* next;
		} Node;
		Node* first;
		
	public:
		explicit List() : first(NULL) {}
		
		~List() {
			while (first != NULL) {
				Node* next = first->next;
				delete first;
				first = next;
			}
		}
		
		// Unshifts an item onto the list.
		void Add(T item) {
			Node* new_node = new Node;
			new_node->item = item;
			new_node->next = first;
			first = new_node;
		}
		
		// Executes a function for each item in the list, and removes them all
		// from the list. The passed function must not modify the list.
		// The execution order goes from last-added to first-added.
		template <class F> void Flush(F fn) {
			while (first != NULL) {
				fn(first->item);
				Node* next = first->next;
				delete first;
				first = next;
			}
		}
};

#endif