#ifndef NODE_SQLITE3_PLUS_LIST_H
#define NODE_SQLITE3_PLUS_LIST_H

template <class T>
class List {
	public:
		List();
		~List();
		void Add(T*);
		void Remove(T*);
		void Each(void (*fn)(T*));
		
	private:
		typedef struct Node {
			T* item;
			Node* prev;
		} Node;
		Node* front;
		Node* end;
};

#endif