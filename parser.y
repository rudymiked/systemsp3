%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "svsh.h"
#include "svsh.c"

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
session:
	   	lines			{ /* Do nothing */ }	
	      | /* NULL */		{ /* Do nothing */ }
	      ;

lines:
		line			{ /* Do nothing */ }
	      |	lines line		{ /* Do nothing */ }
	      ;

line:
		stmt NEWLINE		{ call(NEWLINE, NULL, NULL, NULL, NULL); }
	      | NEWLINE			{ call(NEWLINE, NULL, NULL, NULL, NULL); }
	      | error NEWLINE		{ 
						yyerrok;
						yyclearin;
						printPrompt();
					}
	      ;

stmt: 
	DEFPROMPT STRING	 		{	call(DEFPROMPT, $2, NULL, NULL, NULL);	}
	| METACHAR WORD				{	call(METACHAR, $2, NULL, NULL, NULL);	}
	| VARIABLE METACHAR STRING		{	/*call(PATH, $2, NULL);*/		}
	| ASSIGNTO VARIABLE WORD VARIABLE STRING{	call(ASSIGNTO, $5, $4, $3, $2); 	}
	| LISTJOBS				{	call(LISTJOBS, NULL, NULL, NULL, NULL);	}
        | RUN WORD VARIABLE                     {	printf("POE DEBUG: RUN in parser \n");
							call(RUN, $3, $2, NULL, NULL);		}
	| CD WORD				{	printf("POE DEBUG: CD in Parser \n");
							call(CD, $2, NULL, NULL, NULL);		}
	| BYE					{	printf("POE DEBUG: in BYE \n");
							exit(0);		}
	| WORD					{	printf("Invalid input\n");	}
	;
%%

void yyerror(char * s)
{
	printf("%s\n", s);
}

