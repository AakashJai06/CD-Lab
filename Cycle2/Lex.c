#include <stdio.h>
#include <ctype.h>

void analyze(const char *code) {
    int i = 0;
    char buffer[100];
    int j;

    while (code[i] != '\0') {
        char ch = code[i];

        // Ignore spaces, tabs, newlines
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            i++;
            continue;
        }

        // Identifier
        if (isalpha(ch)) {
            j = 0;
            while (isalnum(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            printf("IDENTIFIER: %s\n", buffer);
        }
        // Number
        else if (isdigit(ch)) {
            j = 0;
            while (isdigit(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            printf("NUMBER: %s\n", buffer);
        }
        // Symbol
        else {
            printf("SYMBOL: %c\n", ch);
            i++;
        }
    }
}

int main() {
    char input[1000];
    int i = 0;
    char ch;

    printf("Enter code (end with $):\n");
    while ((ch = getchar()) != '$' && i < 999) {
        input[i++] = ch;
    }
    input[i] = '\0';

    printf("\n--- Tokens ---\n");
    analyze(input);

    return 0;
}
