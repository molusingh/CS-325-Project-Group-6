CC = g++
CFLAGS = -std=c++11

default: 2opt

2opt:	main.cpp 
		$(CC) $(CFLAGS) main.cpp -o 2opt

.PHONY : clean
clean: 
	rm -f 2opt