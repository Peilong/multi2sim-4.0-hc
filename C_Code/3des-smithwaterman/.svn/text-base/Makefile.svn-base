INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = smithwaterman.c des.c 3des-smithwaterman.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o 3des-smithwaterman \
	-lm -lpthread
clean:
	rm -f 3des-smithwaterman
