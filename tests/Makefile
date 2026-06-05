CC = gcc
CFLAGS = -I. -I../src/c -Wall -Wextra

test: test_util
	./test_util

test_util: test_util.o ../src/c/util.o pebble.o
	$(CC) $(CFLAGS) -o $@ $^

test_util.o: test_util.c
	$(CC) $(CFLAGS) -c $< -o $@

../src/c/util.o: ../src/c/util.c
	$(CC) $(CFLAGS) -c $< -o $@

pebble.o: pebble.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o ../src/c/*.o test_util
