minesweeper: main.o minesweeper.o
	clang++ -g -Wall main.o minesweeper.o -o minesweeper
main.o: main.cpp minesweeper.h
	clang++ -g -Wall main.cpp -c 
minesweeper.o: minesweeper.cpp minesweeper.h
	clang++ -g -Wall minesweeper.cpp -c 
clean: 
	rm -f *.o minesweeper