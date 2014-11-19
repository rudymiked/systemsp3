// CS 485
// Header file for shell
// Mike Rudy

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include "y.tab.h"
#include "variablecall.c"

#define MAX_JOBS 40
#define PATH_MAX 20
#define LINE 20


#define UP	0x48
#define DOWN	0x50
#define LEFT	0x4B
#define RIGHT	0x4D

struct job {
  int pid;
  int job_id;
  int state;
  char *name;
  char cmdline[LINE];
};
