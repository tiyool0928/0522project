#pragma once

#include <iostream>
#include <fstream>
#include<cstring>
#include "Node.h"
#include "stack.h"
#include "queue.h"
using namespace std;

class Maze

{
private:

	int width;				//미로의 너비
	int height;				//미로의 높이
	int **map;				 //미로 맵
	stack locStack;
	queue locQueue;

public:

	Maze() { init(0, 0); }

	~Maze() { reset(); }

	void init(int w, int h)			//map을 이차원 배열로 동적할당
	{
		map = new int*[h];
		for (int i = 0; i < height; i++)
		{
			map[i] = new int[w];
		}
	}

	void reset()					//동적 해제
	{
		for (int i = 0; i < height; i++)
		{
			delete[]map[i];
		}
		delete[]map;
	}

	void DFS(const char *fname)					//파일로 미로 파일 읽기
	{
		ifstream fin(fname, ios::in);			//dfs버전
		char temp;
		fin >> height>> width;
		init(width, height);
		

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fin >> temp;					//문자로 받아오기
				map[i][j] = temp;
				if (map[i][j] == 'e')			//문자가 e면 그 자리에 객체 생성
				{
					Node entry(j, i);
					locStack.push(&entry);
				}
			}
			//cout << endl;
		}
		fin.close();

		cout << "전체 미로의 크기 = " << height << " * " << width << endl;
		for (int i = 0; i < height; i++)		//미로 데이터 출력
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j] == '1')
				{
					cout << "1";
				}
				else if (map[i][j] == '0')
				{
					cout << "0";
				}
				else if (map[i][j] == 'e')
				{
					cout << "e";
				}
				else if (map[i][j] == 'x')
				{
					cout << "x";
				}
			}
			cout << endl;
		}
		//cout << endl;

		int count = 0;							//탐색 횟수
		while (locStack.isEmpty() == false)		//탈출 할때 까지
		{
			Node* here = locStack.peek();
			locStack.pop();

			int r = here->rows;
			int c = here->cols;
			printf("(%d,%d)", r, c);

			count++;

			if (map[r][c] == 'x')				//객체가 x에 도달했을 시
			{
				printf("미로 탐색 성공\n");
				printf("깊이 우선 탐색 횟수: [%d회]\n", count);
				break;
			}
			else
			{
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locStack.push(new Node(r - 1, c));
				if (isValidLoc(r + 1, c)) locStack.push(new Node(r + 1, c));
				if (isValidLoc(r, c - 1)) locStack.push(new Node(r, c - 1));
				if (isValidLoc(r, c + 1)) locStack.push(new Node(r, c + 1));
			}
		}
	}

	void BFS(const char *fname)			//파일로 미로 파일 읽기
	{
		ifstream fin(fname, ios::in);		//bfs버전

		fin >> height >> width;
		init(width, height);
		char temp;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fin >> temp;				//문자로 받아오기
				map[i][j] = temp;
				if (map[i][j] == 'e')
				{
					Node entry(j, i);
					locQueue.enqueue(&entry);

				}
			}
			cout << endl;
		}
		fin.close();

		int count = 0;
		while (locQueue.isEmpty() == false)
		{
			Node* here = locQueue.peek();
			locQueue.dequeue();

			int r = here->rows;
			int c = here->cols;
			printf("(%d,%d)", r, c);

			count++;

			if (map[r][c] == 'x')
			{
				printf("미로 탐색 성공\n");
				printf("너비 우선 탐색 횟수: [%d회]\n", count);
				break;
			}
			else
			{
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
				if (isValidLoc(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
				if (isValidLoc(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
				if (isValidLoc(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
			}
		}
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r > height || c > width) return false;
		//맵을 넘어가거나 0보다 작아지면 에러
		else return map[r][c] == '0' || map[r][c] == 'x';
	};

};

