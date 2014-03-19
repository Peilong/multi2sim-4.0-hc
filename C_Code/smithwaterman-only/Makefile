INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = smithwaterman.c smithwaterman-only.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o smithwaterman-only \
	-lm
clean:
	rm -f smithwaterman-only
