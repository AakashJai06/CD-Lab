%{
  #include "for.tab.h"
%}

%%
"for" { return FOR; }
";" { return ';'; }
"(" { return '('; }
")" { return ')'; }
"=" { return '='; }
"<"|">"|"<="|">="|"!=" { return RELOP; }
"++"|"--" { return INCDEC; }
[a-zA-Z][a-zA-Z0-9_]* { return ID; }
[0-9]+ { return NUMBER; }
[ \t] { }
\n { }
%%

int yywrap(){
  return 0;
}
