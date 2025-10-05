%{
  #include<stdio.h>
%}

%%
[a-zA-Z]*aaka[a-zA-Z]*  { printf("\nInvalid statement\n"); }
.* { printf("\nValid statement\n"); }
%%

int main(){
  printf("Enter the statement : ");
  yylex();
  return 0;
}

int yywrap(){
  return 1;
}
