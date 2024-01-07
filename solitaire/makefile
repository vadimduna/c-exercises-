solitaire: main.o solitaire.o
	clang++ -g -Wall main.o solitaire.o -o solitaire
main.o: main.cpp solitaire.h
	clang++ -g -Wall main.cpp -c
solitaire.o: solitaire.cpp solitaire.h
	clang++ -g -Wall solitaire.cpp -c
clean:
	rm -f *.o solitaire