#pragma once
#include <cstdio>

class Node
{
public:
	Node* link;
	int rows;
	int cols;

	Node(int r,int c) {
		rows = r;
		cols = c;
		link = NULL; 
	}
	~Node() {}
};
