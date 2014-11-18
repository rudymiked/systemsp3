#include <sys/syscall.h>
#define __NR_sys_SaveVariable 314
#define __NR_sys_GetVariable 315

int assignVarName(char * arg1, char * arg2 )
{	
	int retval;
	printf("arg 1: %s\t arg2: %s\t\n", arg1, arg2);
	printf("arg 1 addr: %x\t arg2 addr: %x\t\n", &arg1, &arg2);
	retval = syscall(__NR_sys_SaveVariable, arg1, arg2);
	printf("Done calling Save Variable!\n");
	printf("SaveVariable() returned %d\n", retval);
	
	return 0;
}

int getVar(char *varname, char *vardef, int deflen)
{
	int retval;
	retval = syscall(__NR_sys_GetVariable, varname, vardef, deflen);
	printf("done calling get variable!\n");
	printf("GetVariable() returned %d\n", retval);
	return 0; 
}
