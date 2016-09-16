#ifndef BETTER_SQLITE3_LIST_H
#define BETTER_SQLITE3_LIST_H

template <class T>
class List {
	private:
		typedef struct Node {
			T* item;
			Node* next;
		} Node;
		Node* first;
		Node* last;
		
	public:
		explicit List() : first(NULL), last(NULL) {}
		
		// Items that were added to the list are automatically `delete`d.
		// This is not appropriate if the item's memory must be freed with
		// free() or delete[]. In such cases, List should not be used.
		~List() {
			while (first != NULL) {
				Node* next = first->next;
				delete first->item;
				delete first;
				first = next;
			}
		}
		
		// Pushes an item onto the list.
		void Add(T* item) {
			Node* new_node = new Node;
			new_node->item = item;
			new_node->next = NULL;
			if (last == NULL) {
				first = last = new_node;
			} else {
				last->next = new_node;
				last = new_node;
			}
		}
		
		// Shifts the oldest item off the list.
		// You are responsible for deleting it yourself.
		T* Shift() {
			if (first == NULL) {return NULL;}
			T* item = first->item;
			Node* next = first->next;
			delete first;
			first = next;
			return item;
		}
		
		// Executes a function for each item in the list, and removes them all
		// from the list. The passed function must not modify the list.
		// The execution order goes from first-added to last-added.
		// Each item is `delete`d after their callback function returns.
		template <class F> void Flush(F fn) {
			while (first != NULL) {
				fn(first->item);
				Node* next = first->next;
				delete first->item;
				delete first;
				first = next;
			}
			last = NULL;
		}
};

#endif