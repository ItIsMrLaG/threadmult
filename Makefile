CC = gcc
CFLAGS = -Wall -pthread
TARGET = threads

all: $(TARGET)

$(TARGET): thread.c
	$(CC) $(CFLAGS) -o $(TARGET) thread.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
