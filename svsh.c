// Shell
// Mike Rudy
// CS 485

#include "svsh.h"
//#include "sCalls.c"

char *prompt;
int job_number;
struct job run_s[MAX_JOBS];
 
//extern int SaveVariable(char *varname, char *vardef);
//extern int GetVariable(char *varname, char *vardef, int deflen);
//extern int NextVariable(char *prevname, char *varname, namelen, char *vardef, int deflen);

int printPrompt() {

  if (!prompt)
    prompt = "svsh";
  printf("%s > ", prompt);
 
  yyparse();  

  return 0;

}
int run(struct job *run_s, char *arg1, char *arg2) {
  pid_t parent = getpid();
  pid_t pid = fork();
  int status;

  if (pid == -1)
  {
    printf("Failed to fork! \n");
  }
  else if (pid > 0)
  {
    job_number = pid - parent;
    addjob(run_s, arg1, pid, 1);
    waitpid(pid, status, 0);
  }
  else { 
    execl(arg1, "", (char *)NULL);
    _exit(EXIT_FAILURE);
  }

}


int addjob(struct job *run_s, char *arg1, int pid, int state) {
  int status = 1;
  if (pid < 1)
    status = 0;
  int i;
  int n = job_number;
 // if (run_s->pid == 0) {
  run_s[n].pid = pid;
  run_s[n].state = state;
  run_s[n].job_id = n;
  run_s[n].name  = arg1;
  //}
 // }

  return status;
}


int call(int opr, char *arg1, char *arg2, char *arg3, char *arg4[], int index) {
 
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
        int j;
        for(j = 1; j < MAX_JOBS; j++){
          if (run_s[j].job_id != 0)
            printf("%d : %s \n", run_s[j].job_id, run_s[j].name);  
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
        if (arg2) { // run prog $VARIABLE <-variable is present
          run(&run_s[job_number], arg2, arg1);
        }
        else { 
          arg2 = ""; // <- $VARIABLE is not present, therefore set arguments to "" (for now)
          run(&run_s[job_number], arg1, arg2);
        }
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

int main() {
  
  printPrompt();
  
  return 0;

}

