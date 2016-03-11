#include <cstdlib>
#include "list.h"

template <class T>
List<T>::List<T>() : front(NULL), end(NULL) {}

template <class T>
List<T>::~List<T>() {
	// destruct here
}

template <class T>
void List<T>::Add(T* item) {
	Node* new_node = (Node*) malloc(sizeof(Node));
	new_node->item = item;
	new_node->prev = NULL;
	if (end == NULL) {
		front = end = new_node;
		return;
	}
	end->prev = new_node;
	end = new_node;
}

template <class T>
void List<T>::Remove(T* item) {
	if (front == NULL) {return;}
	
	if (front->item == item) {
		Node* prev = front->prev;
		free(front);
		front = prev;
		return;
	}
	
	Node* temp = front;
	while (temp->prev != NULL) {
		if (temp->prev->item == item) {
			if (temp->prev == end) {
				end = temp;
			}
			Node* prev = temp->prev->prev;
			free(temp->prev);
			temp->prev = prev;
			break;
		}
		temp = temp->prev;
	}
}
