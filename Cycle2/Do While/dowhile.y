%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror();
%}

%token DO WHILE ID

%%
stmt: DO block WHILE '(' cond ')' ';'  { printf("Valid do-while statement\n"); return 0; };

block: '{' stmt_list '}' 
     | stmt
     ;

stmt_list: stmt_list stmt
          | stmt
          | /* empty */
          ;

cond: ID 
    | ID relop ID
    ;

relop: '<' | '>' | LE | GE | EQ | NE; /* optional for realism, though not lex-defined */
%%

int yyerror() {
    printf("Invalid do-while syntax\n");
    return 0;
}

int main() {
    printf("Enter a do-while statement:\n");
    yyparse();
    return 0;
}
