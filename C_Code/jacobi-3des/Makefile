INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = jacobi.c des.c jacobi-3des.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o jacobi-3des \
	-lm -lpthread
clean:
	rm -f jacobi-3des
