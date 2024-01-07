maze: main.o maze.o
	clang++ -g -Wall main.o maze.o -o maze
main.o: main.cpp maze.h
	clang++ -g -Wall main.cpp -c 
maze.o: maze.cpp maze.h
	clang++ -g -Wall maze.cpp -c
