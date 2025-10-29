%{
#include <stdio.h>
%}

%%

.*nira.* { printf("Rejected: contains 'nira'\n"); }

.* { printf("Accepted: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}


/* 
To run the program:
    flex rejectName.l
    gcc lex.yy.c -o rejectName
    ./rejectName
*/