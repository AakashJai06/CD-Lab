%{
#include <stdio.h>
#include <string.h>

char first4[5];
char str[100];
%}

%%
.* {
    if (strstr(yytext, first4))
        printf("\nInvalid statement : contains '%s'\n", first4);
    else
        printf("\nValid statement : does not contain '%s'\n", first4);
}
%%

int main() {
    char name[100];
    printf("Enter your name: ");
    scanf("%s", name);

    strncpy(first4, name, 4);
    first4[4] = '\0'; 

    printf("Enter the statement: ");
    yylex();
    return 0;
}

int yywrap() { return 1; }
