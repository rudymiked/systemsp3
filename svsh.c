// Shell
// Mike Rudy
// CS 485

#include "svsh.h"
//#include "y.tab.h"


char *prompt;

int call(int opr, char *arg1, char *arg2) {
  char str[60];
  int i = 0;
  char *jobs[MAX_JOBS];
  prompt = "svsh";

  
    switch(opr) {
     /* case (METACHAR): {
        printf("%s\n", str);
        break;
      }*/
      case (DEFPROMPT): {
        prompt = arg1;
        break;
      }
      case (LISTJOBS): {
        int j, n;
        n = sizeof(jobs)/sizeof(jobs[0]);
        for(j = 0; j < n; j++){
          printf("%s %d\n", jobs[i], i);
        }
        break;
      }
      case (CD): {
        chdir(arg1);
        getwd(arg1);
        printf("%s \n", arg1);
        break;
      }
      case (RUN): {
        printf("Run program \n");
        break;
      }
      case (ASSIGNTO): {
        printf("assign output to a variable\n");
        break;
      }
      case (BYE): {
        exit(0); 
        break;
      }
      default:
        printf("'%s' : Not A Command\n", str);
    }
/*
  while (strcmp(str, "bye") != 0) {
    if (strcmp(str, "pwd") == 0)
      printf("Present Working Directory\n"); 
    else if (str[0] == '#') {
      printf("%s\n", str);
    }
    else if (strcmp(str, "defprompt") == 0) {
      prompt = "new_svsh";
    }
    else if (strcmp(str, "listjobs") == 0) {
      int j, n;
      n = sizeof(jobs)/sizeof(jobs[0]);
      for(j = 0; j < n; j++){
        printf("%s %d\n", jobs[i], i);
      }
    }
    else if (strcmp(str, "cd") == 0) { 
      getwd(wd);
      printf("wd: %s \n", wd);
      chdir("/home/");
      getwd(wd);
      printf("wd: %s \n", wd);
    }
    else if (strcmp(str, "run") == 0) {
      printf("Run program \n");
    }
    else if (strcmp(str, "assignto") == 0) {
      printf("assign output to a variable\n");
    }
    else
        printf("'%s' : Not A Command\n", str);
    printf("%s > ", prompt);
    fgets(str, sizeof(str), stdin);
    
    str[strlen(str) - 1 ] = '\0';
    
  }
*/
  return 0;
}

int main() {
   
  yyparse();  
  printf("CS Shared Variable Shell\n");
  printf("%s > ", prompt);


  return 0;

}

