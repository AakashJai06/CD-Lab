%{
  #include<stdio.h>
  #include<stdlib.h>
  int yylex(void);
  int yyerror(const char *s);
%}

%token FOR RELOP INCDEC ID NUMBER

%%
RULE : FOR '(' E1 ';' E2 ';' E3 ')' { printf("\nVALID FOR statement\n"); };
E1 : ID '=' E1
    | ID '=' NUMBER
    | /* empty */
    ;
E2 : ID RELOP ID
    | ID RELOP NUMBER
    | /* empty */
    ;
E3 : ID INCDEC
    | ID '=' ID
    | ID '=' NUMBER
    | /* empty */
    ;
%%

int main(){
  printf("\nEnter a For statement : \n");
  yyparse();
  return 0;
}

int yyerror(const char *s){
  return 0;
}
