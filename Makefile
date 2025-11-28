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

test_asan: test.c bs.c bs.h
	$(CC) $(CFLAGS) -DUNIT_TEST -fsanitize=address -g -O1 -fno-omit-frame-pointer -fPIC -c bs.c
	$(CC) $(CFLAGS) -DUNIT_TEST -fsanitize=address -g -O1 -fno-omit-frame-pointer test.c bs.o -o test_asan
	./test_asan
	ASAN_OPTIONS=detect_leaks=1:halt_on_error=0 ./test_asan

test_undef: test.c bs.c bs.h
	$(CC) $(CFLAGS) -DUNIT_TEST -fsanitize=undefined -fno-sanitize-recover=undefined -g -O1 -c bs.c
	$(CC) $(CFLAGS) -DUNIT_TEST -fsanitize=undefined -fno-sanitize-recover=undefined -g -O1 test.c bs.o -o test_undef
	./test_undef

test_tsan: test.c bs.c bs.h
	$(CC) $(CFLAGS) -DUNIT_TEST -fsanitize=thread -g -O1 -c bs.c
	$(CC) $(CFLAGS) -DUNIT_TEST -fsanitize=thread -g -O1 test.c bs.o -o test_tsan
	./test_tsan

test_msan: test.c bs.c bs.h
	$(CLANG) -DUNIT_TEST -fsanitize=memory -g -O1 -c bs.c
	$(CLANG) -DUNIT_TEST -fsanitize=memory -g -O1 test.c bs.o -o test_msan
	./test_msan

libbs.so: bs.h bs.c
	$(CC) $(CFLAGS) -c -fpic bs.c
	$(CC) $(CFLAGS) -shared -lc -o libbs.so bs.o

run: example
	LD_LIBRARY_PATH=./ ./example github.com 3

clean:
	rm -f *.o *.so example test test_*san test_undef
