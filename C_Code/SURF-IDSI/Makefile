INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = IDSI.c SURF.c SURF-IDSI-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o SURF-IDSI-test \
	-lm -lpthread
clean:
	rm -f SURF-IDSI-test
