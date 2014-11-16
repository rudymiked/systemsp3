%{
	#include "y.tab.h"
	#include <string.h>
//	#include "scanner.h"
	#include <stdlib.h>
	void yyerror(char *);
	#define ShowTokens 0
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

{DEFPROMPT}	{	
			if(ShowTokens)
			{
				printf("Token type = Keyword\t Token = %s\t\n", yytext);
			}
			return DEFPROMPT;
		}

{CD}		{       
			if(ShowTokens)
                        {
                                printf("Token type = Keyword\t Token = %s\t\n", yytext);
                        }

			return CD;		
		}

{LISTJOBS}	{	
			if(ShowTokens)
                        {
                                printf("Token type = Keyword\t Token = %s\t\n", yytext);
                        }

			return LISTJOBS;	
		}

{BYE}		{	if(ShowTokens)
                        {
                                printf("Token type = Keyword\t Token = %s\t\n", yytext);
                        }


			return BYE;		}

{RUN}		{	
			if(ShowTokens)
                        {
                                printf("Token type = Keyword\t Token = %s\t\n", yytext);
                        }

			return RUN;		
		}

{BG}		{	
			if(ShowTokens)
                        {
                                printf("Token type = Keyword\t Token = %s\t\n", yytext);
                        }

			return BG;		}

{ASSIGNTO}	{	
			if(ShowTokens)
                        {
                                printf("Token type = Keyword\t Token = %s\t\n", yytext);
                        }

			return ASSIGNTO;	}


{VARIABLE}	{
			if(ShowTokens)
                        {
                                printf("Token type = Variable\t Token = %s\t\n", yytext);
                        }

			yylval.var = strdup(yytext);
			return VARIABLE;
		}

{STRING}	{

			if(ShowTokens)
                        {
                                printf("Token type = String\t Token = %s\t\n", yytext);
                        }

			yylval.string = strdup(yytext);
			/* move string beginning beyond first quote */
			yylval.string++;
			/* remove final quote and replace with null terminator */
			yylval.string[strlen(yylval.string)-1] = '\0';
			return STRING;
		}

{WORD}		{
			if(ShowTokens)
                        {
                                printf("Token type = Word\t Token = %s\t\n", yytext);
                        }

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
