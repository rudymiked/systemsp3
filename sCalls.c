#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/gfp.h>
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
		bool match = true;
		/*define temp variables for call_from_user usage*/
		char VarNameTemp[MAX_BUF_SIZE];
		char VarDefTemp[MAX_BUF_SIZE];

		printk(KERN_EMERG "POE SAVE: %s\t %s\t\n", varname, vardef);

		if(VarIndex > 0)
		{
			/* if variable index exceeds the Maximum number of variables
			   that can be allocated */
			if(VarIndex >= MAX_VARS)
			{	printk(KERN_EMERG "POE SAVE: Not enough room for variable\n");
				return -1;
			}
		
			/* else add variables */
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
				printk(KERN_EMERG "Variable name = %s\n", VarNameTemp);
				printk(KERN_EMERG "Variable stored at current pos = %s\n", VariableNames[j]);
				
				for(i = 0; i < MAX_BUF_SIZE; i++)
				{
					/* if in use, redefine the variable */
                        		if(VarNameTemp[i] != VariableNames[j][i])
                               		{
						match = false;
                               		}
					
				}
				
                         }
			if(match == false)
			{	/* if not in use, add variable to variables arrays */
				for(i = 0; i < MAX_BUF_SIZE; i++)
				{
					VariableNames[VarIndex][i] = VarNameTemp[i];
					VariableDefs[VarIndex][i] = VarDefTemp[i];
				}
				VarIndex++;
			}
			else if(match == true)
			{
				printk(KERN_EMERG "POE SAVE: unable to save variable. Variable of this name is already defined.");
				return -1;
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
		}
		printk(KERN_EMERG "POE_SAVE_VAR: %d\n", retValue);
			
		return 0;
}

asmlinkage int sys_GetVariable(char *varname, char *vardef, int deflen){

	/*define temp variables for call_from_user usage*/
        char VarNameTemp[MAX_BUF_SIZE];
        char VarDefTemp[MAX_BUF_SIZE];

	bool match = true;
	int retValue = -1;
	int i = 0;
	int j = 0;

	retValue = copy_from_user(VarNameTemp, varname, MAX_BUF_SIZE);
	if(retValue != 0)
	{	
		printk(KERN_EMERG "POE GETVAR: copy unsuccessful\n");
		return -1;
	}
	for(i = 0; i < MAX_VARS; i++)
	{
		for(j = 0; j < MAX_BUF_SIZE; j++)
		{
			if(VarNameTemp[j] != VariableNames[i][j])
			{
				printk(KERN_EMERG 
				match = false;
			}
		}
		if(match == true)
		{
			for(j = 0; j < MAX_BUF_SIZE; j++)
			{
				VarDefTemp[j] = VariableDefs[i][j];
			}
			retValue = copy_to_user(vardef, VarDefTemp, deflen);
			if(retValue == 0)
			{
				printk(KERN_EMERG "Success! %s = %s\n", VarNameTemp, VarDefTemp);
			}
		}
		else
		{
			printk(KERN_EMERG "Failure. Match not found.\n");
			return -1;
		}
	}
	return 0;	
}

asmlinkage int sys_NextVariable(char *prevname, char *varname, int namelen, char *vardef, int deflen){
	/* define temp variables for call_from_user usage */
	char VarNameTemp[MAX_BUF_SIZE];
	char VarDefTemp[MAX_BUF_SIZE];
	char PrevNameTemp[MAX_BUF_SIZE];
	
	bool first = true;
	bool match = true;
	int retValue = -1;
	int i = 0;
	int j = 0;

	retValue = copy_from_user(PrevNameTemp, prevname, MAX_BUF_SIZE);
	if(retValue != 0)
	{
		printk(KERN_EMERG "POE NEXTVAR: copy from user error\n");
		return -1;
	}
	printk(KERN_EMERG "Searching for %s\n", PrevNameTemp);
	if((first == true) && (PrevNameTemp[0] = ' '))
	{
		printk(KERN_EMERG "Starting at first variable\n");
		for(i = 0; i < MAX_BUF_SIZE; i++)
		{
			VarNameTemp[i] = VariableNames[0][i];
			VarDefTemp[i] = VariableDefs[0][i];
		}
		copy_to_user(varname, VarNameTemp, namelen);
		copy_to_user(vardef, VarDefTemp, deflen);
		return 0;
	}		
	else
	{
		for(i = 0; i < MAX_VARS; i++)
		{
			match = true;
			for(j = 0; j < MAX_BUF_SIZE; j++)
			{
				if(VariableNames[i][j] != PrevNameTemp[j])
				{
					match = false;
				}
			}
			if(match == true)
			{
				if(i == (MAX_VARS-1))
				{
					printk(KERN_EMERG "POE NEXTVAR: Last item in list\n");
					return -1;
				}
				else if(i == (VarIndex))
				{
					printk(KERN_EMERG "POE NEXTVAR: Last item in list\n");
					return -1;
				}
				else
				{
					for(j = 0; j < MAX_BUF_SIZE; j++)
					{
						VarNameTemp[j] = VariableNames[i+1][j];
						VarDefTemp[j] = VariableDefs[i+1][j];
					} 
					copy_to_user(varname, VarNameTemp, namelen);
					copy_to_user(vardef, VarDefTemp, deflen);
					printk(KERN_EMERG "POE NEXTVAR: retrieved \n");
					return 0;
				}
			}
			else if (match == false)
			{
				if(i == (MAX_VARS-1))
				{
					printk(KERN_EMERG "POE NEXTVAR: Item not on list\n");
					return -2;
				}
			}
		}
	}
	return -2; 
}
