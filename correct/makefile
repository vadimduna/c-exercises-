correct: main.o correct.o
	clang++ -g -Wall main.o correct.o -o correct
main.o: main.cpp correct.h
	clang++ -g -Wall main.cpp -c
correct.o: correct.cpp correct.h
	clang++ -g -Wall correct.cpp -c 
clean:
	rm -f *o correct