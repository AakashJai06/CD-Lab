%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token NUMBER

%%
E : E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | '(' E ')'
  | NUMBER
  ;
%%

int main() {
    printf("Enter an arithmetic expression:\n");
    if (yyparse() == 0)
        printf("Valid expression\n");
    else
        printf("Invalid expression\n");
    return 0;
}

void yyerror(const char *s) {
    printf("Invalid expression\n");
}
