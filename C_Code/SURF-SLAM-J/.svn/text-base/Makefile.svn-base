INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = Jacobians.c SURF.c SURF-SLAM-J-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o SURF-SLAM-J-test \
	-lm -lpthread
clean:
	rm -f SURF-SLAM-J-test
