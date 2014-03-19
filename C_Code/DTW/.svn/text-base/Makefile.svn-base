INSTALL_ROOT = .
LIB_DIR = ../../tools/libm2s-acc
CC = g++
CFLAGS = -Wall -lrt -m32 -I$(INSTALL_ROOT)
LFLAGS = -lpthread
SUB_DIR = $(INSTALL_ROOT)/open_source

SOURCE_FILES = 	LoadFile.cpp uWave.h uWave.c \
		Main.cpp \
		$(SUB_DIR)/KalmanFilter.cpp \
		$(SUB_DIR)/mathstools.cpp \
		$(SUB_DIR)/sensors.cpp

#OBJ_FILES = LoadFile.o Main.o KalmanFilter.o mathstools.o sensors.o

#loadfile:
#	$(CC) $(CFLAGS) -o LoadFile.o LoadFile.cpp

#kalmanfilter:
#	$(CC) $(CFLAGS) -o KalmanFilter.o $(SUB_DIR)/KalmanFilter.cpp

#mathstools:
#	$(CC) $(CFLAGS) -o mathstools.o $(SUB_DIR)/mathstools.cpp

#sensors:
#	$(CC) $(CFLAGS) -o sensors.o $(SUB_DIR)/sensors.cpp

#main:
#	$(CC) $(CFLAGS) -o main.o $(SUB_DIR)/main.cpp

all:
	$(CC) $(CFLAGS) \
	$(SOURCE_FILES) \
	-o SensorProcessing \
	$(LFLAGS)

clean:
	rm SensorProcessing

