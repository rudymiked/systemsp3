#Makefile
#CS 485 Project 3

YACC = bison -d -v -b y
FLEX = flex
BIN_NAME = scannerparser

CC=gcc
CFLAGS=-Wall
OPTIONS = -lfl

OBJ = svsh.o
BIN = svsh



$(BIN_NAME): clean
	$(YACC) parser.y
	$(FLEX) scanner.l
	$(CC) -o $(BIN_NAME) y.tab.c lex.yy.c $(OPTIONS)
	

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

svshmake: svsh.o 
	$(CC) -o svsh svsh.c

clean: 
	rm -f $(BIN) *.o
	rm -f $(BIN_NAME) *.o
