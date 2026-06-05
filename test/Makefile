CC = gcc
CFLAGS = -I. -I../src/c -Wall -Wextra -g

OBJS = pebble_mock.o test_settings.o ../src/c/settings.o

test_settings: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f test_settings $(OBJS)
