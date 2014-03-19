M2S_ROOT = ../..

AR = ar
CC = gcc
CFLAGS = -Wall -O3 -fPIC -m32 -I. -I$(M2S_ROOT)/src/lib/struct -I$(M2S_ROOT)/src/lib/mhandle \
	-I$(M2S_ROOT)/src/lib/misc

OBJECTS = acc.o \
	#debug.o \
	#list.o \

all: libm2s-acc.so libm2s-acc.a


#
# Dynamic and static library targets
#

libm2s-acc.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -shared -o libm2s-acc.so

libm2s-acc.a: $(OBJECTS)
	$(AR) cru libm2s-acc.a $(OBJECTS)

clean:
	rm -f $(OBJECTS) libm2s-acc.so libm2s-acc.a



#
# Auxiliary targets
#

#debug.o: $(M2S_ROOT)/src/lib/struct/debug.c $(M2S_ROOT)/src/lib/struct/debug.h
#	$(CC) $(CFLAGS) -c $(M2S_ROOT)/src/lib/struct/debug.c -o debug.o

#list.o: $(M2S_ROOT)/src/lib/struct/list.c $(M2S_ROOT)/src/lib/struct/list.h
#	$(CC) $(CFLAGS) -c $(M2S_ROOT)/src/lib/struct/list.c -o list.o



#
# M2S OpenGL Library targets
#

acc.o: acc.c m2s-acc.h
	$(CC) $(CFLAGS) -c acc.c -o acc.o

