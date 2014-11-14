%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "svsh.h"
#include "svsh.c"

extern int call(int opr,...);
int yylex(void);

%}
%union {
	char *string;
	char *word;
	char *var;
	char *mchar;
};

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
%token <mchar> METACHARACTER
%token <word> WORD

%type <string> stmt

%%

stmt: 
	DEFPROMPT STRING	 		{	call(DEFPROMPT, $2, NULL);	}
	| PATH STRING 				{	call(PATH, $2, NULL);		}
	| ASSIGNTO WORD STRING 			{	call(ASSIGNTO, $3, $2); 	}
	| LISTJOBS				{	call(LISTJOBS, NULL, NULL);	}
	| CD WORD				{	call(CD, $2, NULL);		}
	| BYE					{	call(BYE, NULL, NULL);		}
	;
%%

void yyerror(char * s)
{
	printf("%s\n", s);
}

