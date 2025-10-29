//Write a LEX Program to convert the substring abc to ABC from the given input string.

%{
#include <stdio.h>
%}

%%
abc     { printf("ABC"); }       // Replace "abc" with "ABC"
.       { ECHO; }                // Print all other characters as is
\n      { ECHO; }                // Handle newline properly
%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
