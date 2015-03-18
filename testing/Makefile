#===============================================================================
# Makefile for AmazingProject Unit Test
#
# Author: Jason Feng, Chris Leech, Jordan Hall
# Date: 4/27/14
#
#===============================================================================
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g
SRC_DIR = ../src/

unitTest: unitTest.c avatar_test.c startup_test.c $(SRC_DIR)movealgorithm.c $(SRC_DIR)movealgorithm.h $(SRC_DIR)startup.h $(SRC_DIR)avatar.c $(SRC_DIR)ascii.c $(SRC_DIR)ascii.h $(SRC_DIR)amazing.h
	$(CC) $(CFLAGS) -o unitTest unitTest.c avatar_test.c startup_test.c $(SRC_DIR)movealgorithm.c $(SRC_DIR)ascii.c

clean:
	rm -f $(SRC_DIR)*.o
	rm -f *~
	rm -f *#     
	rm -f *.log
	rm -f unitTest
