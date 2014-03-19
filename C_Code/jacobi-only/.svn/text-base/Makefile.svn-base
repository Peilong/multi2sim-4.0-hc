INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = jacobi.c jacobi-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o jacobi-test \
	-lm
clean:
	rm -f jacobi-test
