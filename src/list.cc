#include <cstdlib>
#include "list.h"

template <class T>
List<T>::List() : front(NULL), end(NULL) {}

template <class T>
List<T>::~List() {
	Node* node = front;
	while (node != NULL) {
		Node* temp = node->prev;
		free(node);
		node = temp;
	}
}

template <class T>
void List<T>::Add(T* item) {
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

template <class T>
void List<T>::Remove(T* item) {
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

template <class T>
void List<T>::Flush(void (*fn)(T*)) {
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


// Explicit instantiations.
class Statement;
template class List<Statement>;

