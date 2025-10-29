%{
#include "y.tab.h"
#include <stdio.h>
%}

%option noyywrap

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       ;   /* ignore spaces and tabs */
\n          { return '\n'; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"("         { return LPAREN; }
")"         { return RPAREN; }

.           { printf("Invalid character: %s\n", yytext); }

%%

/*

lex calc.l
yacc -d calc.y
gcc lex.yy.c y.tab.c -o calc -ll
./calc

*/