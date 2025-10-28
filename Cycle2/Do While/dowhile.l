%{
#include "y.tab.h"
%}

%%
"do"                { return DO; }
"while"             { return WHILE; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }
";"                 { return ';'; }
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }
[ \t\n]             ;
.                   { return yytext[0]; }
%%
