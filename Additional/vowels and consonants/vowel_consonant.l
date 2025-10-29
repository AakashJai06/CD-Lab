//Write a lex program to find out total number of vowels and consonants from the given
input sting.

%{
int vowels = 0, consonants = 0;
%}

%%
[AEIOUaeiou]    { vowels++; }              // Match vowels
[a-zA-Z]         { consonants++; }          // Match consonants
.|\n             {  }
%%

int main() {
    yylex();
    printf("\nTotal Vowels: %d\nTotal Consonants: %d\n", vowels, consonants);
    return 0;
}

int yywrap() { return 1; }
