%{
  #include <stdio.h>  
  #include <stdlib.h>
  int yylex(void);
  int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'

%%
ArithmeticExpression : E{
  printf("\nResult : %d\n",$$);
  return 0;
};
E:E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'/'E {$$=$1/$3;}
|E'%'E {$$=$1%$3;}
|NUMBER {$$=$1;};
%%

int main(){
printf("\nEnter any arithmetic expression (supports +, -, *, /, %%):\n");
yyparse();
return 0;
}

int yyerror(const char *s){
  return 0;
}
