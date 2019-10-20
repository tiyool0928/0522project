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

	int width;				//�̷��� �ʺ�
	int height;				//�̷��� ����
	int **map;				 //�̷� ��
	stack locStack;
	queue locQueue;

public:

	Maze() { init(0, 0); }

	~Maze() { reset(); }

	void init(int w, int h)			//map�� ������ �迭�� �����Ҵ�
	{
		map = new int*[h];
		for (int i = 0; i < height; i++)
		{
			map[i] = new int[w];
		}
	}

	void reset()					//���� ����
	{
		for (int i = 0; i < height; i++)
		{
			delete[]map[i];
		}
		delete[]map;
	}

	void DFS(const char *fname)					//���Ϸ� �̷� ���� �б�
	{
		ifstream fin(fname, ios::in);			//dfs����
		char temp;
		fin >> height>> width;
		init(width, height);
		

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fin >> temp;					//���ڷ� �޾ƿ���
				map[i][j] = temp;
				if (map[i][j] == 'e')			//���ڰ� e�� �� �ڸ��� ��ü ����
				{
					Node entry(j, i);
					locStack.push(&entry);
				}
			}
			//cout << endl;
		}
		fin.close();

		cout << "��ü �̷��� ũ�� = " << height << " * " << width << endl;
		for (int i = 0; i < height; i++)		//�̷� ������ ���
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

		int count = 0;							//Ž�� Ƚ��
		while (locStack.isEmpty() == false)		//Ż�� �Ҷ� ����
		{
			Node* here = locStack.peek();
			locStack.pop();

			int r = here->rows;
			int c = here->cols;
			printf("(%d,%d)", r, c);

			count++;

			if (map[r][c] == 'x')				//��ü�� x�� �������� ��
			{
				printf("�̷� Ž�� ����\n");
				printf("���� �켱 Ž�� Ƚ��: [%dȸ]\n", count);
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

	void BFS(const char *fname)			//���Ϸ� �̷� ���� �б�
	{
		ifstream fin(fname, ios::in);		//bfs����

		fin >> height >> width;
		init(width, height);
		char temp;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fin >> temp;				//���ڷ� �޾ƿ���
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
				printf("�̷� Ž�� ����\n");
				printf("�ʺ� �켱 Ž�� Ƚ��: [%dȸ]\n", count);
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
		//���� �Ѿ�ų� 0���� �۾����� ����
		else return map[r][c] == '0' || map[r][c] == 'x';
	};

};

