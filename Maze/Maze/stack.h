#pragma once
#include "Node.h"
#include <cstdio>

class stack {
	Node* top;
	
public:
	stack() { top = NULL; }
	~stack() { while (!isEmpty()) delete pop(); }
	bool isEmpty() { return top == NULL; }

	void push(Node *p)
	{
		if (isEmpty()) top = p;
		else
		{
			p->link = top;
			top = p;
		}
	}

	Node* pop()
	{
		if (isEmpty()) return NULL;
		else
		{
			Node*p = top;
			top = top->link;
			return p;
		}
	}

	Node* peek()
	{
		if (isEmpty()) return NULL;
		else
		{
			return top;
		}
	}

	void display()
	{
		for (Node*p = top; p != NULL; p = p->link)
			printf("(%d,%d)\n", p->rows, p->cols);
	}
};
