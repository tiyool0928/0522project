#pragma once
#include "Node.h"
#include <cstdio>

class queue
{
public:

	Node* front;
	Node* rear;

	queue(): front(NULL), rear(NULL){}
	~queue() { while (isEmpty()) delete dequeue(); }
 	bool isEmpty() { return front == NULL; }

	void enqueue(Node* p)
	{
		if (isEmpty()) front = rear = p;
		else {
			rear->link = p;
			rear = p;
		}
	}
	Node* dequeue()
	{
		if (isEmpty()) return NULL;
			Node* p = front;
			front = front->link;
		if (front == NULL) rear = NULL;
		return p;
	}
	Node* peek() { return front; }
};
