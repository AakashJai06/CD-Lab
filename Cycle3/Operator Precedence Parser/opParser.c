#include <stdio.h>
#include <string.h>

int main() {
    char sym[10], tab[10][10], stack[40], input[20];
    int n, i, j, top = 0, pos1, pos2;
    printf("Enter number of terminals: ");
    scanf("%d", &n);

    printf("Enter terminals: ");
    for (i = 0; i < n; i++) scanf(" %c", &sym[i]);

    printf("\nEnter precedence table values (<,>,=):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            printf("%c vs %c: ", sym[i], sym[j]);
            scanf(" %c", &tab[i][j]);
        }

    printf("\nEnter input string: ");
    scanf("%s", input);
    strcat(input, "$");

    stack[top] = '$';
    stack[top + 1] = '\0';
    i = 0;

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    while (1) {
        // Find topmost terminal in stack
        int k = top;
        while (stack[k] == '<' || stack[k] == '>' || stack[k] == '=') k--;

        for (pos1 = 0; pos1 < n && sym[pos1] != stack[k]; pos1++);
        for (pos2 = 0; pos2 < n && sym[pos2] != input[i]; pos2++);

        printf("%s\t\t%s\t", stack, input + i);

        // Accept condition
        if (stack[top] == '$' && input[i] == '$') {
            printf("String accepted\n");
            break;
        }

        // SHIFT
        else if (tab[pos1][pos2] == '<' || tab[pos1][pos2] == '=') {
            printf("Shift '%c'\n", input[i]);
            stack[++top] = tab[pos1][pos2];
            stack[++top] = input[i++];
            stack[top + 1] = '\0';
        }

        // REDUCE
        else if (tab[pos1][pos2] == '>') {
            printf("Reduce '%c'\n", stack[top]);
            while (stack[top] != '<' && top > 0) top--;
            stack[top] = '\0';
            top--;
        }

        // ERROR
        else {
            printf("Error\n");
            break;
        }
    }
}
