INSTALL_ROOT = .
CC = gcc
CFLAGS = -m32 -Wall -lrt 
SOURCE_FILES = Jacobians.c SLAM-jacobian-test.c

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-lm \
	-o SLAM-jacobian-test

clean:
	rm -f SLAM-jacobian-test
