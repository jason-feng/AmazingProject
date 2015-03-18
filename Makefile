#===============================================================================
# Makefile for AmazingProject
#
# Author: Jason Feng, Chris Leech, Jordan Hall
# Date: 4/27/14
#
#===============================================================================
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g 
SRC_DIR = src/
LIBS = -D_XOPEN_SOURCE=700

startup: $(SRC_DIR)startup.c avatar $(SRC_DIR)amazing.h
	$(CC) $(CFLAGS) -o startup $(SRC_DIR)startup.c 

avatar: $(SRC_DIR)avatar.c $(SRC_DIR)movealgorithm.o $(SRC_DIR)amazing.h $(SRC_DIR)ascii.c $(SRC_DIR)ascii.h
	$(CC) $(CFLAGS) -o avatar $(SRC_DIR)avatar.c $(SRC_DIR)movealgorithm.o $(SRC_DIR)ascii.c $(LIBS)

$(SRC_DIR)movealgorithm.o: $(SRC_DIR)movealgorithm.c $(SRC_DIR)movealgorithm.h $(SRC_DIR)amazing.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)movealgorithm.c -o $(SRC_DIR)movealgorithm.o

clean:
	rm -f $(SRC_DIR)*.o
	rm -f *~
	rm -f *#
	rm -f avatar
	rm -f startup
