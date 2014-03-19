INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = SURF.c SURF-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-lm \
	-o SURF-test 
clean:
	rm -f SURF-test
