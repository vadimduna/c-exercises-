scrabble: main.o scrabble.o
	clang++ -g -Wall main.o scrabble.o -o scrabble 
main.o: main.cpp scrabble.h 
	clang++ -g -Wall main.cpp -c 
scrabble.o: scrabble.cpp scrabble.h 
	clang++ -g -Wall scrabble.cpp -c 