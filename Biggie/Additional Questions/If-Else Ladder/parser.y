%{
    #include <stdio.h>    

    int yylex();
    void yyerror(const char *s);

    int flag = 1;
%}

%token NUMBER ID IF ELSE LBRACE RBRACE LROUND RROUND
%token SEMICOLON ASSIGN LT GT LE GE EQ

%right ASSIGN
%left LT GT LE GE EQ
%nonassoc IFX
%nonassoc ELSE

%% 

stmt:
      IF LROUND cond RROUND stmt %prec IFX
    | IF LROUND cond RROUND stmt ELSE stmt
    | LBRACE body RBRACE
    | ID ASSIGN NUMBER SEMICOLON
    ;

body:
      stmt
    | stmt body
    ;

cond:
      expr LT expr
    | expr GT expr
    | expr LE expr
    | expr GE expr
    | expr EQ expr
    ;

expr: ID | NUMBER;

%%

void yyerror(const char *s) {
    fprintf(stderr, "\nInvalid Syntax\n");
    flag = 0;
}

int main() {
    printf("\nEnter The If-Else Statement: \n");
    yyparse();

    if (flag) printf("\nValid Syntax!\n");
    
    return 0;
}