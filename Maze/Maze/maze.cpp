#include "Node.h"
#include "queue.h"
#include "stack.h"
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

const int width = 6;
const int height = 6;

char map1[width][height] =		//¸Ê µ¥ÀÌÅÍ
{
	{ '1','1','1','1','1','1' },
	{ 'e','0','1','0','0','1' },
	{ '1','0','0','0','1','1' },
	{ '1','0','1','0','1','1' },
	{ '1','0','1','0','0','x' },
	{ '1','1','1','1','1','1' },
};

char map2[width][height] =		//¸Ê µ¥ÀÌÅÍ
{
	{ '1','1','1','1','1','1' },
	{ 'e','0','1','0','0','1' },
	{ '1','0','0','0','1','1' },
	{ '1','0','1','0','1','1' },
	{ '1','0','1','0','0','x' },
	{ '1','1','1','1','1','1' },
};

bool isValidLoc1(int r, int c)
{
	if (r < 0 || c < 0 || r >= width || c >= height) return false;
	else return map1[r][c] == '0' || map1[r][c] == 'x';
};

bool isValidLoc2(int r, int c)
{
	if (r < 0 || c < 0 || r >= width || c >= height) return false;
	else return map2[r][c] == '0' || map2[r][c] == 'x';
};

int main()
{
	stack locStack;
	Node entry1(1, 0);
	int dtscount = 0;
	int btscount = 0;

	locStack.push(&entry1);

	while (locStack.isEmpty() == false)
	{
		Node* here = locStack.peek();
		locStack.pop();

		int r = here->rows;
		int c = here->cols;
		printf("(%d,%d)", r, c);

		dtscount++;

		if (map1[r][c] == 'x')
		{
			printf("¹Ì·Î Å½»ö ¼º°ø\n");
			printf("±íÀÌ ¿ì¼± Å½»ö È½¼ö: [%dÈ¸]\n",dtscount);
			break;
		}
		else
		{
			map1[r][c] = '.';
			if (isValidLoc1(r - 1, c)) locStack.push(new Node(r - 1, c));
			if (isValidLoc1(r + 1, c)) locStack.push(new Node(r + 1, c));
			if (isValidLoc1(r, c - 1)) locStack.push(new Node(r, c - 1));
			if (isValidLoc1(r, c + 1)) locStack.push(new Node(r, c + 1));
		}
	}

	queue locQueue;
	Node entry2(1, 0);
	locQueue.enqueue(&entry2);

	while (locQueue.isEmpty() == false)
	{
		Node* here = locQueue.peek();
		locQueue.dequeue();

		int r = here->rows;
		int c = here->cols;
		printf("(%d,%d)", r, c);

		btscount++;

		if (map2[r][c] == 'x')
		{
			printf("¹Ì·Î Å½»ö ¼º°ø\n");
			printf("³Êºñ ¿ì¼± Å½»ö È½¼ö: [%dÈ¸]\n", btscount);

			return 0;
		}
		else
		{
			map2[r][c] = '.';
			if (isValidLoc2(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
			if (isValidLoc2(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
			if (isValidLoc2(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
			if (isValidLoc2(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
		}
	}
	printf("¹Ì·ÎÅ½»ö ½ÇÆÐ");
}