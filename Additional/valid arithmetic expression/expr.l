//Generate a YACC specification to recognize a valid arithmetic expression that uses
operators +, – , *,/ and parenthesis.

%{
#include "expr.tab.h"
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]       { return yytext[0]; }
[ \t\n]         { /* Ignore spaces */ }
.               { return 0; }
%%

int yywrap() { return 1; }
