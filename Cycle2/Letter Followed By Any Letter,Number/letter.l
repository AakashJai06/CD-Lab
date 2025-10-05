%{
#include "letter.tab.h"  
%}

%%
[a-zA-Z][a-zA-Z0-9]* { return VALID; }
. { return INVALID; }
\n { return 0; }
%%

int yywrap(){
  return 1;
}
