#include "Node.h"
#include "maze2.h"
#include "stack.h"
#include "queue.h"

int main()
{
	Maze maze1;
	maze1.DFS("maze.txt");
	//maze1.searchExitDts();
	maze1.reset();
	Maze maze2;
	maze2.BFS("maze.txt");
	//maze2.searchExitBts();
	maze2.reset();
}