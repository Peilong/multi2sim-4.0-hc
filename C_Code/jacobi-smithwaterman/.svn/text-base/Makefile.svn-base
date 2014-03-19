INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = jacobi.c smithwaterman.c jacobi-smithwaterman.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o jacobi-smithwaterman \
	-lm -lpthread
clean:
	rm -f jacobi-smithwaterman
