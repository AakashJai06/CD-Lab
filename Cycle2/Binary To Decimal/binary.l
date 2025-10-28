%{
#include "y.tab.h"
%}

%%
[0-1]+    { yylval = atoi(yytext); return NUM; }
\n        { return '\n'; }
.         ;
%%
