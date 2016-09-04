#ifndef NODE_SQLITE3_PLUS_LIST_H
#define NODE_SQLITE3_PLUS_LIST_H

template <class T>
class List {
	private:
		typedef struct Node {
			T* item;
			Node* prev;
		} Node;
		Node* front;
		Node* end;
		bool owner;
		
	public:
		List(bool owner = true) : front(NULL), end(NULL), owner(owner) {}
		
		// Unless `owner` is false when destruction occurs, items that were
		// added to the list are automatically `delete`d. This is not
		// appropriate if the item's memory must be freed with free() or
		// delete[]. In such cases, `owner` should be set to false and manual
		// deallocation is required.
		~List() {
			Node* node = front;
			if (owner) {
				while (node != NULL) {
					front = node->prev;
					delete node->item;
					delete node;
					node = front;
				}
			} else {
				while (node != NULL) {
					front = node->prev;
					delete node;
					node = front;
				}
			}
		}
		
		// Pushes an item onto the list.
		void Add(T* item) {
			Node* new_node = new Node;
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
		// removed. Unless `owner` is false, the removed item is `delete`d.
		void Remove(T* item) {
			if (front == NULL) {return;}
			
			if (front->item == item) {
				Node* temp = front->prev;
				if (owner) {delete item;}
				delete front;
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
					if (owner) {delete item;}
					delete node->prev;
					node->prev = temp;
					break;
				}
				node = node->prev;
			}
		}
		
		// Executes a function for each item in the list, and removes them all
		// from the list. The passed function must not modify the list.
		// The execution order goes from first-added to last-added.
		// Unless `owner` is false, each item is `delete`d after their callback
		// function returns.
		template <class F> void Flush(F fn) {
			Node* node = front;
			if (owner) {
				while (node != NULL) {
					fn(node->item);
					front = node->prev;
					delete node->item;
					delete node;
					node = front;
				}
			} else {
				while (node != NULL) {
					fn(node->item);
					front = node->prev;
					delete node;
					node = front;
				}
			}
			end = NULL;
		}
};

#endif