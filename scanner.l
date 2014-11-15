%{
	#include "y.tab.h"
	#include <string.h>
//	#include "scanner.h"
	#include <stdlib.h>
	void yyerror(char *);
%}

STRING ("\""("\\\""|[^"\n])*"\"")|("\'"("\\\'"|[^'\n])*"\'")
VARIABLE ["$"][a-zA-z0-9]+
DEFPROMPT [dD][eE][fF][pP][rR][oO][mM][pP][tT]
CD [cC][dD]
LISTJOBS [lL][iI][sS][tT][jJ][oO][bB][sS]
BYE [bB][yY][eE]
RUN [rR][uU][nN]
ASSIGNTO [aA][sS][sS][iI][gG][nN][tT][oO]
BG [<bg>]
WORD [^><% \t\n\"]+
NEWLINE "\n"
METACHAR "#"|"="

%%

{METACHAR}	{	return METACHAR;	}
{NEWLINE}	{ 	return NEWLINE;		}
{DEFPROMPT}	{	return DEFPROMPT;	}
{CD}		{       return CD;		}
{LISTJOBS}	{	return LISTJOBS;	}
{BYE}		{	return BYE;		}
{RUN}		{	return RUN;		}
{BG}		{	return BG;		}
{ASSIGNTO}	{	return ASSIGNTO;	}


{VARIABLE}	{
			printf("POE DEBUG: variable\n");
			yylval.var = strdup(yytext);
			return VARIABLE;
		}

{STRING}	{
			printf("POE DEBUG: string\n");
			yylval.string = strdup(yytext);
			/* move string beginning beyond first quote */
			yylval.string++;
			/* remove final quote and replace with null terminator */
			yylval.string[strlen(yylval.string)-1] = '\0';
			return STRING;
		}

{WORD}		{
			printf("POE DEBUG: word\n");
			yylval.word = strdup(yytext);
			return WORD;
		}
[ \t]+	;	/*ignore whitespace*/
.		{
			printf("Unknown Character\n");
		}

%%
int yywrap(void) {
	return 1;
}
