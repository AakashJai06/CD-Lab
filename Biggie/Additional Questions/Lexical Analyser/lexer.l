%{
#include <stdio.h>
%}

%%

[ \t\n]+                                ;

"int"|"float"|"char"|"if"|"else"|"for"|"while"|"do"|"return"|"void"    { printf("Keyword\t\t%s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*                  { printf("Identifier\t\t%s\n", yytext); }

[0-9]+\.[0-9]+                          { printf("Number\t\t%s\n", yytext); }
[0-9]+                                  { printf("Number\t\t%s\n", yytext); }

\"([^\"\\]|\\.)*\"                      { printf("String\t\t%s\n", yytext); }

"==" |"!="|"<="|">="|"<"|">"|
"=" |"+"|"-"|"*"|"/"|"%"|"++"|"--"|
"&&" |"||"|"!"                          { printf("Operator\t\t%s\n", yytext); }

";" |","|"("|")"|"{"|"}"|"["|"]"        { printf("Delimiter\t\t%s\n", yytext); }

.                                       { printf("Unknown\t\t%s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    printf("Enter C code (Ctrl+D to end):\n\n");
    yylex();
    printf("\nLexical analysis complete.\n");
    return 0;
}