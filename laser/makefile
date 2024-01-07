laser:main.o laser.o
	clang++ -g -Wall main.o laser.o -o laser 
main.o:main.cpp laser.h 
	clang++ -g -Wall main.cpp -c 
laser.o:laser.cpp laser.h
	clang++ -g -Wall laser.cpp -c 