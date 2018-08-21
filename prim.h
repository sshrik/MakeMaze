#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "maze.h"

#ifndef PRIM
#define PRIM
#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

#define EMPTY -1
#define FULL 1

void nodeToMap(int width, int height, int (*map)[2 * width + 1], node (*maze)[width]);
int isBlocked(node n);

void primMaze(int width, int height, int (*map)[2 * width + 1]);
int searchAll(int width, int height, node (*maze)[width]);
int getCheckedNode(int sind);
int getNextNode(int width, int height, node (*maze)[width], node checkedNode, node *nextNode);
void deleteWall(node* n1, node* n2, int way);
int checkAround(int width, int height, node (*maze)[width], int x, int y);
int display(int width, int height, int (*map)[width]);

#endif
