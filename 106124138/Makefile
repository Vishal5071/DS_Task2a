TARGET = task2a
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
SOURCES = code\main.c code\platform.c code\post.c code\comment.c code\reply.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)