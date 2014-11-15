%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "svsh.h"
#include "svsh.c"

extern int call(int opr, char * arg1, char * arg2);
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
%token PATH
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
		stmt NEWLINE		{ call(NEWLINE, NULL, NULL); }
	      | NEWLINE			{ call(NEWLINE, NULL, NULL); }
	      | error NEWLINE		{ 
						yyerrok;
						yyclearin;
						printPrompt();
					}
	      ;

stmt: 
	DEFPROMPT STRING	 		{	call(DEFPROMPT, $2, NULL);	}
	| METACHAR				{	/* ignore comments */		}
	| PATH METACHAR STRING			{	call(PATH, $2, NULL);		}
	| ASSIGNTO WORD STRING 			{	call(ASSIGNTO, $3, $2); 	}
	| LISTJOBS				{	call(LISTJOBS, NULL, NULL);	}
	| CD WORD				{	printf("POE DEBUG: CD in Parser \n");
							call(CD, $2, NULL);		}
	| BYE					{	printf("POE DEBUG: in BYE \n");
							exit(0);		}
	;
%%

void yyerror(char * s)
{
	printf("%s\n", s);
}

