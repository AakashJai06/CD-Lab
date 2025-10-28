%{
#include <stdio.h>
#include <math.h>
int yyerror();
int yylex();
%}

%token NUM

%%
start: NUM '\n' {
        int n = $1, dec = 0, base = 1;
        while (n > 0) {
            int r = n % 10;
            dec += r * base;
            n /= 10;
            base *= 2;
        }
        printf("Decimal value = %d\n", dec);
        return 0;
     };
%%

int yyerror() {
    printf("Invalid binary number\n");
    return 0;
}

int main() {
    printf("Enter a binary number: ");
    yyparse();
    return 0;
}
