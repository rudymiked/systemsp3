// Shell
// Mike Rudy
// CS 485

#include "svsh.h"
//#include "y.tab.h"

char *prompt;

int call(int opr, char *arg1, char *arg2) {

  char *wd[PATH_MAX];
  char *s;
  int i = 0;
  int k = 0;
  char *jobs[MAX_JOBS];
  
    switch(opr) {
      case (METACHAR): {
        printf("%s\n", arg1);
        break;
      }
      case (DEFPROMPT): {
        prompt = arg1;
        return 0;
      }
      case (LISTJOBS): {
        int j, n;
        n = sizeof(jobs)/sizeof(jobs[0]);
        for(j = 0; j < n; j++){
          printf("%s %d\n", jobs[i], i);
        }
        return 0;
      }
      case (CD): {
        k = chdir(arg1);
        if (!k)  {
          getwd(wd);
          printf("pwd: %s\n", wd);
        }
        else 
          printf("%s : Not a Directory\n", arg1);

        return 0;
      }
      case (RUN): {
        printf("Run program \n");
        return 0;
      }
      case (ASSIGNTO): {
        s = arg1;
        printf(" %s, assign output to a variable\n", s);
        return 0;
      }
      case (NEWLINE): {
        printPrompt();
      }
      default: 
        printPrompt();
           
    }

  return 0;

}

int printPrompt() {

  if (!prompt)
    prompt = "svsh";
  printf("%s > ", prompt);
 
  yyparse();  

  return 0;

}

int main() {
  
  printPrompt();
  
  return 0;

}

