// Shell
// Mike Rudy
// CS 485

#include "svsh.h"
//#include "sCalls.c"

char *prompt;

//extern int SaveVariable(char *varname, char *vardef);
//extern int GetVariable(char *varname, char *vardef, int deflen);
//extern int NextVariable(char *prevname, char *varname, namelen, char *vardef, int deflen);
int call(int opr, char *arg1, char *arg2, char *arg3, char *arg4) {

  char *wd[PATH_MAX];
  char *s;
  int i = 0;
  int k = 0;
  char *jobs[MAX_JOBS];
  
    switch(opr) {
      case (METACHAR): {
        printf("%s\n", arg1);
        return 0;
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
        printf("RUDY - run\n");
        run(arg2, arg1);
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
      case (VARIABLE): {
       printf("%s \n", arg1);
       //SetVariable(DO FUN STUFF);
       return 0;
      }
      default: 
        return 0;
           
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
int run(char *arg1, char *arg2) {
  printf("Running %s \n", arg1);
  pid_t parent = getpid();
  pid_t pid = fork();
   
  if (pid == -1)
  {
    printf("Failed to fork! \n");
  }
  else if (pid > 0)
  {
    int status;
    waitpid(pid, &status, 0);
  }
  else { 
    execl(arg1, arg2, (char *)NULL);
    //_exit(EXIT_FAILURE);
  }

}

int main() {
  
  printPrompt();
  
  return 0;

}

