%{
#include "calculator.tab.h"
#include<stdlib.h>  
%}
%%
[0-9]+    { yylval = atoi(yytext); return NUMBER; }
[+\-*/%]  { return *yytext; }
[ \t]     { }
\n        { return 0; }
%%

int yywrap() {
  return 1;
}
