CC=gcc
bs.o: bs.h bs.c
	$(CC) -c bs.c

test: test.c bs.o
	$(CC) test.c bs.o -o test
