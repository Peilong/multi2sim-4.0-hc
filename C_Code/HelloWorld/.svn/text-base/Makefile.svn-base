INSTALL_ROOT = .
CC = gcc
CFLAGS = -Wall -m32 -lrt -I$(INSTALL_ROOT)
SOURCE_FILES = hello.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-lm \
	-o hello

clean:
	rm -f hello
