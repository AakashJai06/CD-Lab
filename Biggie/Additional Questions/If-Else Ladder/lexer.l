%{
    #include "y.tab.h"
    #include <stdio.h>
%}

%%

"if"                    { return IF; }
"else"                  { return ELSE; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
";"                     { return SEMICOLON; }
"="                     { return ASSIGN; }
"<"                     { return LT; }
">"                     { return GT; }
"<="                    { return LE; }
">="                    { return GE; }
"=="                    { return EQ; }
"("                     { return LROUND; }
")"                     { return RROUND; }
[ \t\n]+                 ;
[a-zA-Z_][a-zA-Z_0-9]*  { return ID; }
[0-9]+                  { yylval = atoi(yytext); return NUMBER;}

%%

int yywrap() {
    return 1;
}