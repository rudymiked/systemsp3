// Shell
// Mike Rudy
// CS 485


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "scanner.h"

#define MAX_JOBS 20

char *prompt;

int call() {
  char str[60];
  int i = 0;
  char *jobs[MAX_JOBS];
  prompt = "svsh";

  printf("CS Shared Variable Shell\n");
  printf("%s > ", prompt);
  //scanf("%s", str);
  //printf("newstr: %s\n", str);
  fgets(str, sizeof(str), stdin);
  str[strlen(str) - 1 ] = '\0';

  while (strcmp(str, "bye") != 0) {
    if (strcmp(str, "pwd") == 0)
      printf("Present Working Directory\n");
    else if (str[0] == '#')
      printf("%s\n", str);
    else if (strcmp(str, "defprompt") == 0)
      prompt = "new_svsh";
    else if (strcmp(str, "listjobs") == 0) {
      int j, n;
      n = sizeof(jobs)/sizeof(jobs[0]);
      for(j = 0; j < n; j++){
        printf("%s %d\n", jobs[i], i);
      }
    }
    else if (strcmp(str, "cd") == 0) 
      printf("Changing directories\n");
    else if (strcmp(str, "run") == 0) {
      printf("Run program \n");
    }
    else if (strcmp(str, "assignto") == 0)
      printf("assign output to a variable\n");
    else
        printf("'%s' : Not A Command\n", str);
    printf("%s > ", prompt);
    fgets(str, sizeof(str), stdin);
    
    str[strlen(str) - 1 ] = '\0';
    
  }

  return 0;
}

int main() {
  
  call();  

return 0;

}
