/* Lex program for decimal to binary conversion */

%{
  /* Definition section */
  #include<stdio.h>
  int num, r, b=0, p=1;
%}

DIGIT [0-9]
/* Rule Section */
%%
{DIGIT}+   { num=atoi(yytext);
             while (num > 0)
             {
              r= num % 2;
              b+= r*p;
              p*= 10;
              num/= 2;
             }
              printf("%d", b);
            }
.|\n    ECHO;
       
%%

// driver code 
int main()
{
    yylex();
    return 0;
}
