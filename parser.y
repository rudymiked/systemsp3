%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/syscall.h>

/*#include "svsh.h"*/
#include "svsh.c"

// Maximum amount of arguments is 20

#define MAXARGS 20
#define ShowTokens 0
#define MAX_BUF_SIZE 256

char *argument[MAXARGS];

//Number of arguments being passed.
int list_index = 0;

extern int call(int opr, char * arg1, char * arg2, char *arg3, char *arg4[MAXARGS], int index);
int yylex(void);
char def[MAX_BUF_SIZE] = "";
char ShowToken[MAX_BUF_SIZE]= "";


%}
%union {
	char *string;
	char *word;
	char *var;
	char *mchar;
};


%token NEWLINE
%token DEFPROMPT
%token CD
%token ASSIGNTO
%token LISTJOBS
%token BYE
%token BG
%token RUN
%token <string> STRING
%token <var> VARIABLE
%token <mchar> METACHAR
%token <word> WORD

%type <string> stmt arglistcmd
%%


shell:
	   	stmt			{ getVar(ShowToken, "$ShowTokens", MAX_BUF_SIZE); }
					  
						
	      | cmd stmt		{ getVar(ShowToken, "$ShowTokens", MAX_BUF_SIZE); }
	      ;


cmd:
		stmt NEWLINE		{ call(NEWLINE, NULL, NULL, NULL, argument, list_index); }
	      | NEWLINE			{ call(NEWLINE, NULL, NULL, NULL, argument, list_index); }
	      | error NEWLINE		{ 
						yyerrok;
						yyclearin;
						printPrompt();
					}
	      ;


stmt: 
	DEFPROMPT STRING	 		{	
							
							if(ShowTokens)
                        				{
                                				printf("Token type = Keyword\t Token = defprompt\t usage = defprompt\n");
								printf("Token type = String\t Token = %s\t usage = string\n", $2);
                        				}
							call(DEFPROMPT, $2, NULL, NULL, argument, list_index);	}
	| METACHAR WORD				{	
							if(ShowTokens)
                                                        {
                                                                printf("Token type = Metachar\t Token = #\t Usage = comment\n");
                                                                printf("Token type = Word\t Token = %s\t Usage = string\n", $2);
                                                        }

							call(METACHAR, $2, NULL, NULL, argument, list_index);	}
	| VARIABLE METACHAR STRING		{	
							if(ShowTokens)
                                                        {
                                                                printf("Token type = Variable\t Token = %s\t Usage = variable_name \n", $1);
                                                                printf("Token type = Metachar\t Token = =\t Usage = assignment\n");
								printf("Token type = String\t Token = %s\t Usage = variable_def\n", $3);
                                                        }

							assignVarName($1, $3); 	}

	| ASSIGNTO VARIABLE arglistcmd VARIABLE STRING{	
							if(ShowTokens)
                                                        {
                                                                printf("Token type = Keyword\t Token = assignto\t Usage = assignto\n");
                                                             	printf("Token type = Variable\t Token = %s\t Usage = variable_name\n", $5);
								printf("Token type = Word\t Token = %s\t Usage = directory_name\n", $4);
								printf("Token type = Variable\t Token = %s\t Usage = arg1\n", $3);
								printf("Token type = String\t Token = %s\t Usage = arg2\n", $2);


                                                        }

							call(ASSIGNTO, $5, $4, $2, argument, list_index); 	}

	| LISTJOBS		{	
					if(ShowTokens)
					{
					printf("Token type = Keyword\t Token = listjobs\t Usage = listjobs\n");
					}
					call(LISTJOBS, NULL, NULL, NULL, argument, list_index);	}
	| CD WORD		{
					if(ShowTokens)
                                        {
                                           printf("Token type = Keyword\t Token = cd\t Usage = cd\n");
			                   printf("Token type = Word\t Token = %s\t Usage = directory_name\n", $2);
                                        }

		
		                        call(CD, $2, NULL, NULL, argument, list_index);		}
	| CD VARIABLE		{

					if(ShowTokens)
                                        {
                                           printf("Token type = Keyword\t Token = cd\t Usage = cd\n");
                                           printf("Token type = Word\t Token = %s\t Usage = directory_name\n", $2);
                                        }
					
					getVar($2, def, MAX_BUF_SIZE);
					printf("def = %s\t deflen = %i\n", def, MAX_BUF_SIZE);
					call(CD, def, NULL, NULL, argument, list_index);
					
				}

	| BYE			{	exit(0);				}
	| WORD			{	printf("\nInvalid input\n");		}
	| RUN arglistcmd	{	call(RUN, NULL, NULL, NULL, argument, list_index); list_index = 0;}

arglistcmd:			/*Recursive call of arglistcmd that allows for the build of the argument list */
        

	WORD    		 {argument[list_index] = $1;}
        |VARIABLE    		 {argument[list_index] = $1;}
	|VARIABLE arglistcmd 	{argument[list_index] = $1; list_index++; argument[list_index] = $2; list_index++;}
	|WORD arglistcmd       	{argument[list_index] = $1; list_index++; argument[list_index] = $2; list_index++;};
%%

void yyerror(char *s)
{
	return;
}
