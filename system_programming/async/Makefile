CC=gcc
CFLAGS=-O0 -Wall -g
TARGET=server
SOURCES=server.c event_loop.c
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)