#include <sys/syscall.h>
#define __NR_sys_SaveVariable 314
#define __NR_sys_GetVariable 315
#define __NR_sys_NextVariable 316

int assignVarName(char * arg1, char * arg2 )
{	
	int retval;
	retval = syscall(__NR_sys_SaveVariable, arg1, arg2);
	if(retval == 0)
	{
		printf("Variable saved successfully\n");
	}
	else
	{
		printf("Save Failed\n");
	}
	return 0;
}

int getVar(char *varname, char *vardef, int deflen)
{
	int retval;
	retval = syscall(__NR_sys_GetVariable, varname, vardef, deflen);
	if(retval == 0)
        {
                printf("Variable retrieved successfully\n");
        }
        else
        {
                printf("Variable not found\n");
        }

	return 0; 
}

int nextVar(char* prevname, char *varname, int namelen, char * vardef, int deflen)
{
	int retval;
	retval = syscall(__NR_sys_NextVariable, prevname, varname, namelen, vardef, deflen);	
        if(retval == 0)
        {
                printf("Next variable retrieved successfully\n");
        }
	if(retval == -1)
	{
		printf("at end of list\n");
	}
        else
        {
                printf("Variable not found\n");
        }

	return 0;
}
