%{
#include <stdio.h>
%}

%%
abc     { printf("123"); }   // Replace every "abc" with "123"
.|\n    { ECHO; }            // Print everything else as-is (including newlines)
%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
