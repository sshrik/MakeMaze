#include<stdio.h>
#include "maze.h"

void nodeToMap(int width, int height, int (*map)[2 * height + 1], node (*maze)[height])	{
	int i, j;
	for( i = 0; i < height; i++)    {
		for(j = 0; j < width; j++)    {
           	if(!isBlocked(maze[i][j]))    {
           	    map[i * 2 + 1][j * 2 + 1] = EMPTY;    // Make room to NULL;
           	}
           	if(maze[i][j].wall[EAST] == EMPTY)    {
           	    map[i * 2 + 1][j * 2 + 2] = EMPTY;    // Make room to NULL;
           	}
           	if(maze[i][j].wall[WEST] == EMPTY)    {
           	    map[i * 2 + 1][j * 2] = EMPTY;    // Make room to NULL;
           	}
           	if(maze[i][j].wall[SOUTH] == EMPTY)    {
           	    map[i * 2 + 2][j * 2 + 1] = EMPTY;    // Make room to NULL;
           	}
           	if(maze[i][j].wall[NORTH] == EMPTY)    {
           	    map[i * 2][j * 2 + 1] = EMPTY;    // Make room to NULL;
           	}
        }
    }	
}

int isBlocked(node n)	{
	return n.contents != EMPTY;
}

void primMaze(int width, int height, int (*map)[2 * height + 1])	{
	int cind, eind, way;
	node* checkedNode = (node *)malloc(sizeof(node) * width * height);
	node maze[width][height];
	node nextNode;
	int i, j;

	srand(time(NULL));
		
	for(i = 0; i < height; i++)	{
		for(j = 0; j < width; j++)	{
			maze[i][j].x = i;
			maze[i][j].y = j;
			memset(maze[i][j].wall, FULL, sizeof(int) * 4);
			maze[i][j].contents = FULL;
		}
	}
	
	cind = 0;	// for checked node index.
	eind = 0;	// for checked node end index.
	
	// Pick random.
	checkedNode[eind].x = rand() % height;
	checkedNode[eind].y = rand() % width;
	eind++;
	maze[checkedNode[0].x][checkedNode[0].y].contents = EMPTY;

	while(searchAll(width, height, maze) != 1)	{
		cind = getCheckedNode(eind);
		way = getNextNode(width, height, maze, checkedNode[cind], &nextNode);
		maze[nextNode.x][nextNode.y].contents = EMPTY;

		deleteWall(&maze[checkedNode[cind].x][checkedNode[cind].y], &maze[nextNode.x][nextNode.y], way);
		// Check checkedNode[cind]`s around node is all empty, if yes delete from checkedNode.
		if(checkAround(width, height, maze, checkedNode[cind].x, checkedNode[cind].y) == EMPTY)	{
			memmove(&checkedNode[cind], &checkedNode[cind + 1], sizeof(node) * (eind - cind - 1));
			memset(&checkedNode[eind], 0x00, sizeof(node));
			eind--;
		}

		if(checkAround(width, height, maze, nextNode.x, nextNode.y) == FULL)	{
			checkedNode[eind].x = nextNode.x;
			checkedNode[eind].y = nextNode.y;
			eind++;
		}
		
		for(i = 0; i < eind; i++)	{
			if(checkAround(width, height, maze, checkedNode[i].x, checkedNode[i].y) == EMPTY)	{
				memmove(&checkedNode[i], &checkedNode[i + 1], sizeof(node) * (eind - i - 1));
				memset(&checkedNode[eind], 0x00, sizeof(node));
				eind--;
				i--;
			}
		}
	}

	nodeToMap(width, height, map, maze);
	display(2 * width + 1, 2 * height + 1, map);
	free(checkedNode);
}
int searchAll(int width, int height, node (*maze)[width])	{
	// Search All maze node and if not empty is exist, return -1;
	int i, j;
	int result = 1;

	for(i = 0; i < width; i++)	{
		for(j = 0; j < height; j++)	{
			if(maze[i][j].contents == FULL)	{
				result = 0;
			}
		}
	}

	return result;
}
int getCheckedNode(int sind)	{
	return rand() % sind;
}

int getNextNode(int width, int height, node (*maze)[width], node checkedNode, node * nextNode)	{
	int way;
	int x = checkedNode.x;
	int y = checkedNode.y;
	
	while(1)	{
		way = rand() % 4;
		switch(way){
			case(EAST):
				if(y + 1 < width) {
					if(maze[x][y + 1].contents == FULL)	{
						nextNode->x = x;
						nextNode->y = y + 1;
						return way;
					}
				}
				break;
			case(WEST):
				if(y - 1 > -1) {
					if(maze[x][y - 1].contents == FULL)	{
						nextNode->x = x;
						nextNode->y = y - 1;
						return way;
					}
				}
				break;
			case(SOUTH):
				if(x + 1 < height) {
					if(maze[x + 1][y].contents == FULL)	{
						nextNode->x = x + 1;
						nextNode->y = y;
						return way;
					}
				}
				break;
			case(NORTH):
				if(x - 1 > -1) {
					if(maze[x - 1][y].contents == FULL)	{
						nextNode->x = x - 1;
						nextNode->y = y;
						return way;
					}
				}
				break;
	
			default:
				break;
		}
	}
}

void deleteWall(node* n1, node* n2, int way)	{
	switch(way){
		case EAST:
			n1->wall[EAST] = EMPTY;
			n2->wall[WEST] = EMPTY;
			break;
		case WEST:
			n1->wall[WEST] = EMPTY;
			n2->wall[EAST] = EMPTY;
			break;
		case SOUTH:
			n1->wall[SOUTH] = EMPTY;
			n2->wall[NORTH] = EMPTY;
			break;
		case NORTH:
			n1->wall[NORTH] = EMPTY;
			n2->wall[SOUTH] = EMPTY;
			break;

		default:
			break;
	}
}

int checkAround(int width, int height, node (*maze)[width], int x, int y)	{
	int result = EMPTY;
	if(x + 1 < height) {
		if(maze[x+1][y].contents == FULL) result = FULL;
	}
	if(x - 1 > -1)	{
		if(maze[x-1][y].contents == FULL) result = FULL;
	}
	if(y + 1 < width) {
		if(maze[x][y+1].contents == FULL) result = FULL;
	}
	if(y - 1 > -1)	{
		if(maze[x][y-1].contents == FULL) result = FULL;
	}
	return result;
}

int display(int width, int height, int (*map)[width])	{
	int i, j;
	for(i = 0; i < height; i++)	{
		for(j = 0; j < width; j++)	{
			if(map[i][j] == EMPTY) printf("  ");
			else printf("■ ");
		}
		printf("\n");
	}
}
