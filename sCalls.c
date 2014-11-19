#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#define MAX_VARS 20
#define MAX_BUF_SIZE 256
/* define arrays for Names and Definitions of Variables as well as index value*/
char VariableNames[MAX_VARS][MAX_BUF_SIZE];
char VariableDefs[MAX_VARS][MAX_BUF_SIZE];
int VarIndex = 0;

/* system call to save variable */
asmlinkage int sys_SaveVariable(char *varname, char * vardef){
		
		int retValue = -1;		
		int i = 0;	
		int j = 0;
		bool match = false;
		/*define temp variables for call_from_user usage*/
		char VarNameTemp[MAX_BUF_SIZE];
		char VarDefTemp[MAX_BUF_SIZE];

		printk(KERN_EMERG "POE SAVE: %s\t %s\t\n", varname, vardef);

		if(VarIndex > 0)
		{
			printk(KERN_EMERG "POE SAVE: adding more variables\n");

			retValue = copy_from_user(VarNameTemp, varname, MAX_BUF_SIZE);
			retValue = copy_from_user(VarDefTemp, vardef, MAX_BUF_SIZE);
			/* check to see if temp holds copy of user input for variable */
			if(retValue != 0)
			{
				printk(KERN_EMERG "POE SAVE: failed to save variable!\n");
				return -1;
			}
			/* check that variable name is not already in use */
			for(j = 0; j < MAX_VARS; j++)
                        {
				printk(KERN_EMERG "POE: Variable stored at %i = %s\n", j, VariableNames[j]);
				
				if(strcmp(VarNameTemp, VariableNames[j])==0)
				{
					match = true;
					VariableDefs[j][i] = VarDefTemp[i];
					printk(KERN_EMERG "POE: variable given new def\n");
					return 0;
				}	
                         }
			if(match == false)
			{	
				/* if variable index exceeds the Maximum number of variables that can be allocated */
                        	if(VarIndex >= MAX_VARS)
                        	{
                               		printk(KERN_EMERG "POE SAVE: Not enough room for variable\n");
                               		return -1;
                       		 }

				
				/* if not in use, add variable to variables arrays */
				for(i = 0; i < MAX_BUF_SIZE; i++)
				{
					VariableNames[VarIndex][i] = VarNameTemp[i];
					VariableDefs[VarIndex][i] = VarDefTemp[i];
				}
				VarIndex++;
				printk("POE: Var index = %i\n", VarIndex);
			}
		}
		else
		{
			/* add the first variable, no checking for names required */
			printk(KERN_EMERG "POE SAVE: adding first variable\n");
			retValue = copy_from_user(VarNameTemp, varname, MAX_BUF_SIZE);
                        retValue = copy_from_user(VarDefTemp, vardef, MAX_BUF_SIZE);
			/* if the coppy form user calls are not successful, fail */
			if(retValue != 0)
			{
				printk(KERN_EMERG "POE SAVE: failed to save variable\n");
				return -1;
			}
			/* else, create variable */
			for(i = 0; i < MAX_BUF_SIZE; i++)
			{
				VariableNames[VarIndex][i] = VarNameTemp[i];
				VariableDefs[VarIndex][i] = VarDefTemp[i];
			}
			printk(KERN_EMERG "POE SAVE: Variable = %s\t %s\t\n", VariableNames[0], VariableDefs[0]);
			VarIndex++;
			printk(KERN_EMERG "POE: VarIndex = %i\n", VarIndex);
		}
		printk(KERN_EMERG "POE_SAVE_VAR: %d\n", retValue);
			
		return 0;
}

asmlinkage int sys_GetVariable(char *varname, char *vardef, int deflen){

	/*define temp variables for call_from_user usage*/
        char VarNameTemp[MAX_BUF_SIZE];

	int retValue = -1;
	int i = 0;

	for(i = 0; i < MAX_VARS; i++)
	{
		retValue = copy_from_user(VarNameTemp, varname, MAX_BUF_SIZE);
		if(retValue != 0)
	        {
                	/* return error if copy doesnt work */
                	printk(KERN_EMERG "POE GETVAR: copy unsuccessful\n");
     	        	return -1;
       		}
	
		/* check for match */
		printk(KERN_EMERG "VarNameTemp = %s, VarNames[i] = %s\n", VarNameTemp, VariableNames[i]);
		if(strcmp(VarNameTemp, VariableNames[i])==0)
		{
			/* if match, set user the def of variable*/
			copy_to_user(vardef, VariableDefs[i], MAX_BUF_SIZE);
			printk(KERN_EMERG "Success! Vardef = %s", vardef);
			return 0;
		}
	}
	/* if something goes wrong, return -1 */
	return -1;	
}

asmlinkage int sys_NextVariable(char *prevname, char *varname, int namelen, char *vardef, int deflen){
	/* define temp variables for call_from_user usage */
	char VarNameTemp[MAX_BUF_SIZE];
	char VarDefTemp[MAX_BUF_SIZE];
	char PrevNameTemp[MAX_BUF_SIZE];
	
	int retValue = -1;
	int i = 0;

	retValue = copy_from_user(PrevNameTemp, prevname, MAX_BUF_SIZE);
	if(retValue != 0)
	{
		/* return -2 if copy doesnt work*/
		printk(KERN_EMERG "POE NEXTVAR: copy from user error\n");
		return -2;
	}
	printk(KERN_EMERG "Searching for %s\n", PrevNameTemp);
	if((PrevNameTemp[0]) == ' ')
	{
		/* if at first variable, copy first variable into varname vardef*/
		printk(KERN_EMERG "Starting at first variable\n");
		copy_to_user(varname, VarNameTemp[0], MAX_BUF_SIZE);
		copy_to_user(vardef, VarDefTemp[0], MAX_BUF_SIZE);
		return 0;
	}		
	else
	{
		for(i = 0; i < MAX_VARS; i++)
		{
			if(strcmp(VariableNames[i], PrevNameTemp) == 0)
			{
				/*if match found for previous*/
				if(i == (MAX_VARS-1))
				{
					/* if at last item, return -1*/
					printk(KERN_EMERG "POE NEXTVAR: Last item in list\n");
					return -1;
				}
				else if(i == (VarIndex))
				{
					/* if at last item allocated, return -1 */
					printk(KERN_EMERG "POE NEXTVAR: Last item in list\n");
					return -1;
				}
				else
				{
					/* if not at last item, copy next to varname, vardef */
					copy_to_user(varname, VariableNames[i+1], MAX_BUF_SIZE);
					copy_to_user(vardef, VariableDefs[i+1], MAX_BUF_SIZE);
					printk(KERN_EMERG "POE NEXTVAR: retrieved \n");
					return 0;
				}
			}
			else if (strcmp(VariableNames[i], PrevNameTemp)!=0)
			{
				/* if not match with previous*/
				if(i == (MAX_VARS-1))
				{
					/* item not on list, return -2*/
					printk(KERN_EMERG "POE NEXTVAR: Item not on list\n");
					return -2;
				}
			}
		}
	}
	/* if something messes up, return -2 as error */
	return -2; 
}
