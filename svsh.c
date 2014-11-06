#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

char * prompt = "svsh";

int call() {
  char str[60];
  int space_flag = 0;
  int i = 0;

  printf("CS Shared Variable Shell\n");
  printf("%s > ", prompt);
  //scanf("%s", str);
  //printf("newstr: %s\n", str);
  fgets(str, sizeof(str), stdin);
  str[strlen(str) - 1 ] = '\0';

  while (strcmp(str, "exit") != 0) {
    if (strcmp(str, "pwd") == 0)
      printf("Present Working Directory\n");
    else if (str[0] == '#')
      printf("%s\n", str);

    else if (strcmp(str, "defprompt") == 0)
      prompt = str;

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
