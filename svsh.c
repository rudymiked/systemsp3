//Shell
//Mike Rudy
//CS 485


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#define MAX_JOBS 20
#define JOB_NAME_SIZE 20

char * prompt = "svsh";

int call() {
  char str[60];
  int i = 0;
  char *jobs[MAX_JOBS];

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
      prompt = str;
    else if (strcmp(str, "listjobs") == 0) {
      int j, n;
      n = sizeof(jobs)/sizeof(jobs[0]);
      for(j = 0; j < n; j++){
        printf("%s %d\n", jobs[i], i);
      }
    }
    else
        printf("%s : Not A Command\n", str);
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
