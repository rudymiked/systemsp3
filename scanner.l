//CS 485 Fall 2014 Program 3
//Scanner
//Ashley Poe

%{
	#include "y.tab.h"
	#include "scanner.h"
	#include <stdlib.h>
	void yyerror(char *);
%}

STRING ("\""("\\\""|[^"\n])*"\"")|("\'"("\\\'"|[^'\n])*"\'")
VARIABLE ["$"][A-Za-z0-9]*
KEYWORD [dD][eE][fF][pP][rR][oO][mM][pP][tT]|[cC][dD]|[lL][iI][sS][tT][jJ][oO][bB][sS]|[bB][yY][eE]|[rR][uU][nN]|[aA][sS][sS][iI][gG][nN][tT][oO]|[<bg>]
WORD [^ \t\n]*
METACHARACTER "="|"#"

%%
{KEYWORD}	{
			printf("Token type = keyword   Token = %c\n", yytext);
			return KEYWORD;
		}


{VARIABLE}	{
			yylval.sIndex = *yytext - 'A';
                        printf("Token type = VARIABLE   Token = %c\n", yytext);

			return VARIABLE;
		}

{STRING}	{
                        printf("Token type = string   Token = %c\n", yytext);
			return STRING;
		}
{WORD}
		{
                        printf("Token type = word   Token = %c\n", yytext);
			return WORD;
		}

{METACHARACTER} {
	  		printf("Token type = metacharacter   Token = %c\n", yytext);
			return METACHARACTER;	
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
