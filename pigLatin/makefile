piglatin: main.o piglatin.o
	clang++ -Wall -g main.o piglatin.o -o piglatin
main.o: main.cpp piglatin.h
	clang++ -Wall -g main.cpp -c
piglatin.o: piglatin.h piglatin.cpp
	clang++ -Wall -g piglatin.cpp -c 