%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

//#include "svsh.h"

#include "svsh.c"
#define ShowTokens 1
#define MAXARGS 20

struct args{
	char * arg[MAXARGS];
};

extern int call(int opr, char * arg1, char * arg2, char *arg3, char *arg4);
int yylex(void);

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

%type <string> stmt

%%
shell:
	   	stmt			{ /* Do nothing */ }	
	      | cmd stmt		{ /* Do nothing */ }
	      ;


cmd:
		stmt NEWLINE		{ call(NEWLINE, NULL, NULL, NULL, NULL); }
	      | NEWLINE			{ call(NEWLINE, NULL, NULL, NULL, NULL); }
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
							call(DEFPROMPT, $2, NULL, NULL, NULL);	}
	| METACHAR WORD				{	
							if(ShowTokens)
                                                        {
                                                                printf("Token type = Metachar\t Token = #\t Usage = comment\n");
                                                                printf("Token type = Word\t Token = %s\t Usage = string\n", $2);
                                                        }

							call(METACHAR, $2, NULL, NULL, NULL);	}
	| VARIABLE METACHAR STRING		{	
							if(ShowTokens)
                                                        {
                                                                printf("Token type = Variable\t Token = %s\t Usage = variable_name \n", $1);
                                                                printf("Token type = Metachar\t Token = =\t Usage = assignment\n");
								printf("Token type = String\t Token = %s\t Usage = variable_def\n", $3);
                                                        }

							call(VARIABLE, $3, $2, NULL, NULL); 	}

	| ASSIGNTO VARIABLE WORD VARIABLE STRING{	
							if(ShowTokens)
                                                        {
                                                                printf("Token type = Keyword\t Token = assignto\t Usage = assignto\n");
                                                             	printf("Token type = Variable\t Token = %s\t Usage = variable_name\n", $5);
								printf("Token type = Word\t Token = %s\t Usage = directory_name\n", $4);
								printf("Token type = Variable\t Token = %s\t Usage = arg1\n", $3);
								printf("Token type = String\t Token = %s\t Usage = arg2\n", $2);


                                                        }

							call(ASSIGNTO, $5, $4, $3, $2); 	}

	| LISTJOBS		{	
					if(ShowTokens)
					{
					printf("Token type = Keyword\t Token = listjobs\t Usage = listjobs\n");
					}
					call(LISTJOBS, NULL, NULL, NULL, NULL);	}
	| CD WORD		{
					if(ShowTokens)
                                        {
                                           printf("Token type = Keyword\t Token = cd\t Usage = cd\n");
			                   printf("Token type = Word\t Token = %s\t Usage = directory_name\n", $2);
                                        }

		                        call(CD, $2, NULL, NULL, NULL);		}
	| BYE			{	exit(0);				}
	| WORD			{	printf("Invalid input\n");		}
	| arglistcmd		{	/*do nothing*/				}

arglistcmd:
        RUN WORD		{ call(RUN, $2, NULL, NULL, NULL); }
	| RUN WORD VARIABLE     {
                                      if(ShowTokens)
                                      {
                                        printf("Token type = Keyword\t Token = run\t Usage = run\n");
                                        printf("Token type = Word\t Token = %s\t Usage = cmd\n", $2);
                                        printf("Token type = Variable\t Token = %s\t Usage = variable_name\n", $3);
                                      }
                                      call(RUN, $3, $2, NULL, NULL);
                                }
        	;
%%

void yyerror(char * s)
{
	printf("%s\n", s);
}

