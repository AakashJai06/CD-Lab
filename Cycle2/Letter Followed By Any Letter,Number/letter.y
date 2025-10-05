%{
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
int yyerror(const char *s);  
%}

%token VALID INVALID

%%
input : VALID { printf("\nVALID statement\n"); }
      | INVALID { printf("\nINVALID statement\n"); };
%%

int main(){
  printf("Enter a variable: ");
  yyparse();
  return 0;
}

int yyerror(const char *s){
  return 0;
}
