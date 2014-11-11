#Makefile
#CS 485 Project 3

CC=gcc
CFLAGS=-Wall

DEPS = scanner.h
OBJ = svsh.o
BIN = svsh

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

svshmake: svsh.o 
	$(CC) -o svsh svsh.c

clean: 
	rm -f $(BIN) *.o
