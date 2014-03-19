INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = des.c segmentation_acc.c 3des-seg-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o 3des-seg-test \
	-lm -lpthread
clean:
	rm -f 3des-seg-test
