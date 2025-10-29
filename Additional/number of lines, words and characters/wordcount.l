//Write a lex program to display the number of lines, words and characters in an input text.

%{
int lines = 0, words = 0, chars = 0;
%}

%%
\n        { lines++; chars++; }       // count new line as character
[ \t]+    { chars += yyleng; }        // spaces/tabs count as characters
[^ \t\n]+ { words++; chars += yyleng; } // any word (non-space sequence)
.         { chars += yyleng; }        // any other single char
%%

int main() {
    yylex();
    printf("Lines: %d\nWords: %d\nCharacters: %d\n", lines, words, chars);
    return 0;
}
