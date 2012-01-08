CC=gcc
CFLAGS=

bs: bs.o sample.c
	$(CC) $(CFLAGS) bs.o sample.c -o sample

bs.o: bs.h bs.c
	$(CC) $(CFLAGS) -c bs.c

test: test.c bs.c bs.h
	$(CC) $(CFLAGS) -DUNIT_TEST -c bs.c
	$(CC) $(CFLAGS) -DUNIT_TEST test.c bs.o -o test
clean:
	rm -f *.o test
