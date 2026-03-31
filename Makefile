CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = source.code/clitodo.c
TARGET = clitodo
all:
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)
install:
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)
	@if [ -d "/data/data/com.termux/files/usr/bin" ]; then \
		cp $(TARGET) /data/data/com.termux/files/usr/bin/; \
		echo "Installed to Termux bin"; \
	else \
		sudo mv $(TARGET) /usr/local/bin/; \
		echo "Installed to Linux bin"; \
	fi
clean:
	rm -f $(TARGET)

