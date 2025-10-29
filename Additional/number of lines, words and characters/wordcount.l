//Write a lex program to display the number of lines, words and characters in an input text.

%{
int lines = 0, words = 0, chars = 0;
%}

%%
[ \t]+        { chars += yyleng; }        
\n            { lines++; chars++; }        
[^ \t\n]+     { words++; chars += yyleng; } 
%%

int main() {
    yylex();
    printf("\nLines: %d\nWords: %d\nCharacters: %d\n", lines, words, chars);
    return 0;
}

int yywrap() { return 1; }
