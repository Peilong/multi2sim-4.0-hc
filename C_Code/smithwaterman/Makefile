INSTALL_ROOT = .
LIB_DIR = ../../tools/libm2s-acc
CC = gcc
CFLAGS = -Wall -lrt -m32 -I$(INSTALL_ROOT)
LFLAGS = -lm
SOURCE_FILES = smithwaterman.c smithwaterman-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-L$(LIB_DIR) -lm2s-acc \
	-o smithwaterman-test \
	$(LFLAGS)
clean:
	rm -f smithwaterman-test
