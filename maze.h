#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#ifndef MAZE
#define MAZE
#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

#define EMPTY -1
#define FULL 1

typedef struct {
	int x, y;
	int contents;
	int wall[4];
} node;
#endif
