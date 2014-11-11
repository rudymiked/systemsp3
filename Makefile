#Makefile
#CS 485 Project 3

CC=gcc
CFLAGS=-Wall

DEPS = scanner.h
OBJ = svsh.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

