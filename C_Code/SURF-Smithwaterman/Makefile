INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = smithwaterman.c SURF.c SURF-Smithwaterman-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o SURF-Smithwaterman-test \
	-lm -lpthread
clean:
	rm -f SURF-Smithwaterman-test
