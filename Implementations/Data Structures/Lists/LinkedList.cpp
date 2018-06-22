template <class T> struct Node{
	
	Node *next = NULL, *prev = NULL;
	T val;

	Node(T t) { this->val = t; }

};

template <class T> struct LinkedList{

	Node<T> *head = NULL, *tail = NULL;

	void push(T t) {
		if(!head) tail = head = new Node<T>(t);
		else if(head == tail) {
			tail = new Node<T>(t);
			head->next = tail;
			tail->prev = head;
		} else {
			tail->next = new Node<T>(t);
			tail->next->prev = tail;
			tail = tail->next;
		}
	}

	void pop() {
		head = head->next;
		head->prev = NULL;
	}
	
	void moveToFront(Node<T> *node) {
		if(node == head) return;
		if(node == tail) {
			tail = tail->prev;
			tail->next = NULL;
		} else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		node->prev = NULL;
		node->next = head;
		head = head->prev = node;
	}

};
