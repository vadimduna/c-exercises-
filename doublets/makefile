doublets: doublets.o main.o
	clang++ -g -O3 -Wall doublets.o main.o -o doublets
main.o: main.cpp doublets.h
	clang++ -g -O3 -Wall main.cpp -c 
doublets.o: doublets.cpp doublets.h dictionary.h
	clang++ -g -O3 -Wall doublets.cpp -c 
