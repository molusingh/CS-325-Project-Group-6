CC = g++
CFLAGS = -g -std=c++11

default: 2opt

2opt:	main.cpp 
		$(CC) $(CFLAGS) main.cpp -o 2opt

valgrind: 2opt
	valgrind --leak-check=yes -v --show-reachable=yes --track-origins=yes 2opt

.PHONY : clean
clean: 
	rm -f 2opt
	rm -f *.tour
	rm -f 2Opt