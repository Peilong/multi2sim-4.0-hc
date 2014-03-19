INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = IDSI.c IDSI-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-lm \
	-o IDSI-test
clean:
	rm -f IDSI-test
