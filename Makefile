CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = source.code/clitodo.c
TARGET = clitodo
all:
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)
install:
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)
	sudo mv $(TARGET) /usr/local/bin/
clean:
	rm -f $(TARGET)

