sonnet: main.o sonnet.o
	clang++ -g -Wall main.o sonnet.o -o sonnet 
main.o: main.cpp sonnet.h
	clang++ -g -Wall main.cpp -c 
sonnet.o: sonnet.h sonnet.cpp 
	clang++ -g -Wall sonnet.cpp -c 