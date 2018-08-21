#include"maze.h"
#include"prim.h"

int main()	{
	int width = 20;
	int height = 20;
	int map[2 * height + 1][2 * width + 1];

	memset(map, FULL, sizeof(int) * (2 * width + 1) * (2 * height + 1));

	primMaze(width, height, map);

	return 0;
}
