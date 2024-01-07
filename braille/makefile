braille: main.o braille.o
	clang++ -g -Wall main.o braille.o -o braille
main.o: main.cpp braille.h
	clang++ -g -Wall main.cpp -c
braille.o: braille.h braille.cpp
	clang++ -g -Wall braille.cpp -c 