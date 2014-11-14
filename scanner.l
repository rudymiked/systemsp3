%{
	#include "y.tab.h"
	#include <string.h>
//	#include "scanner.h"
	#include <stdlib.h>
	void yyerror(char *);
%}

STRING ("\""("\\\""|[^"\n])*"\"")|("\'"("\\\'"|[^'\n])*"\'")
VARIABLE ["$"][A-Za-z0-9]*
DEFPROMPT [dD][eE][fF][pP][rR][oO][mM][pP][tT]
CD [cC][dD]
LISTJOBS [lL][iI][sS][tT][jJ][oO][bB][sS]
BYE [bB][yY][eE]
RUN [rR][uU][nN]
ASSIGNTO [aA][sS][sS][iI][gG][nN][tT][oO]
BG [<bg>]
PATH ["$"][a-zA-Z0-9]+
WORD [^><% \t\n\"]+

%%

{DEFPROMPT}	{	return DEFPROMPT;	}
{CD}		{	return CD;	}
{LISTJOBS}	{	return LISTJOBS;	}
{BYE}		{	return BYE;	}
{RUN}		{	return RUN;	}
{BG}		{	return BG;	}
{PATH}		{	return PATH;	}


{VARIABLE}	{
			yylval.var = *yytext - 'A';
			return VARIABLE;
		}

{STRING}	{
			yylval.string = strdup(yytext);
			/* move string beginning beyond first quote */
			yylval.string++;
			/* remove final quote and replace with null terminator */
			yylval.string[strlen(yylval.string)-1] = '\0';
			return STRING;
		}

{WORD}		{
			yylval.word = strdup(yytext);
			return WORD;
		}

.		{
			yyerror("Unknown character");
		}
%%
int yywrap(void) {
	return 1;
}
int main(void){
	yylex();
	return 0;
}
