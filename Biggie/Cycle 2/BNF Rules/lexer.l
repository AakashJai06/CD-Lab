%{
    #include "y.tab.h"
    #include <stdlib.h>
%}

%%

[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
[ \t\n]     ;   // ignore spaces/newlines
.           { return yytext[0]; }

%%