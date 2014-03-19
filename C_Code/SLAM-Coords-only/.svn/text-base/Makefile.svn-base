INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = SphericalCoords.c SLAM-Coords-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-lm \
	-o SLAM-Coords-test 

clean:
	rm -f SLAM-Coords-test
