CC=gcc
CFLAGS=

example: libbs.so sample.c
	$(CC) $(CFLAGS) sample.c -o example -L. -lbs

bs.o: bs.h bs.c
	$(CC) $(CFLAGS) -c bs.c

test: test.c bs.c bs.h
	$(CC) $(CFLAGS) -DUNIT_TEST -c bs.c
	$(CC) $(CFLAGS) -DUNIT_TEST test.c bs.o -o test
	./test

libbs.so: bs.h bs.c
	$(CC) $(CFLAGS) -c -fpic bs.c
	$(CC) $(CFLAGS) -shared -lc -o libbs.so bs.o

run: example
	LD_LIBRARY_PATH=./ ./example github.com 3

clean:
	rm -f *.o *.so example test
