all:
	gcc -o maze makeMaze.c mazeMain.c

clean:
	rm maze
