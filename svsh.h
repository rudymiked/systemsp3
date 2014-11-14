// CS 485
// Header file for shell
// Mike Rudy

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "scanner.h"

#define MAX_JOBS 20

#define UP	0x48
#define DOWN	0x50
#define LEFT	0x4B
#define RIGHT	0x4D




