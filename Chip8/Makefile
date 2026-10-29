CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = chip8
SOURCES = main.c chip8.c instructions.c execute.c io.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lSDL2 -o $(TARGET)

%.o: %.c chip8.h io.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean