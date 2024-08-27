all: main

CC = gcc
override CFLAGS += -g -lm

SRCS = $(wildcard *.c) $(wildcard src/*.c) $(wildcard src/**/*.c)
HEADERS = $(wildcard *.h) $(wildcard include/*.h) $(wildcard include/**/*.h)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug
