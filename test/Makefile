CC = gcc
CFLAGS = -I. -I../src/c
DEPS = ../src/c/settings.h ../src/c/sidebar_widgets.h mock_pebble.h

all: test_settings

test_settings: test_settings.c test_main.c ../src/c/settings.c
	mkdir -p include && cp mock_pebble.h include/pebble.h
	$(CC) $(CFLAGS) -I./include -o test_settings test_settings.c test_main.c ../src/c/settings.c
	rm -rf include

clean:
	rm -f test_settings
