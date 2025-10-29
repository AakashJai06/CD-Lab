%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER
%token PLUS MINUS MUL DIV
%token LPAREN RPAREN

%left PLUS MINUS
%left MUL DIV
%right UMINUS   /* unary minus */

%%

input:
    /* empty */
    | input expr '\n'   { printf("= %d\n", $2); }
    | input expr ';'    { printf("= %d\n", $2); }
    | input expr        { printf("= %d\n", $2); }
    ;

expr:
    NUMBER
    | expr PLUS expr    { $$ = $1 + $3; }
    | expr MINUS expr   { $$ = $1 - $3; }
    | expr MUL expr     { $$ = $1 * $3; }
    | expr DIV expr     { 
                            if ($3 == 0) {
                                yyerror("Division by zero");
                                $$ = 0;
                            } else {
                                $$ = $1 / $3;
                            }
                        }
    | LPAREN expr RPAREN { $$ = $2; }
    | MINUS expr %prec UMINUS { $$ = -$2; } /* unary minus */
    ;

%%

int main() {
    printf("Enter The Expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}