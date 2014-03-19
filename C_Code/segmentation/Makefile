INSTALL_ROOT = .
LIB_DIR = ../../tools/libm2s-acc
CC = gcc
CFLAGS = -Wall -m32 -lrt -I$(INSTALL_ROOT)
LFLAGS = -lm
SOURCE_FILES = segmentation_acc.c seg-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-L$(LIB_DIR) -lm2s-acc \
	-o seg-test \
	$(LFLAGS)
clean:
	rm -f seg-test
