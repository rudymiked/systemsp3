#include <sys/syscall.h>
#define __NR_sys_SaveVariable 314

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
