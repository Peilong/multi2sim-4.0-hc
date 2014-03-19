INSTALL_ROOT = .
LIB_DIR = ../../tools/libm2s-acc
CC = gcc
CFLAGS = -Wall -lrt -m32 -I$(INSTALL_ROOT)
SOURCE_FILES =	Jacobians.c SphericalCoords.c des.c \
				IDSI.c segmentation_acc.c smithwaterman.c \
				SURF.c \
				Multithread-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-L$(LIB_DIR) -lm2s-acc \
	-o Multithread-test \
	-lm -lpthread
clean:
	rm -f Multithread-test
