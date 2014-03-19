INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt
SOURCE_FILES = Jacobians.c SphericalCoords.c SLAM-jacobians-Coords.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o SLAM-jacobians-Coords \
	-lm -lpthread
clean:
	rm -f SLAM-jacobians-Coords
