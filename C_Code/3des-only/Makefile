INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = des.c 3des-only.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o 3des-only \
	-lm
clean:
	rm -f 3des-only
