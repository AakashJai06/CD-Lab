#include <stdio.h>
#include <string.h>

char input[100], stack[100];
int top = -1, i = 0;

void printStack() {
    printf("$");
    for (int j = 0; j <= top; j++)
        (stack[j] == 'I') ? printf("id") : printf("%c", stack[j]);
}

void reduce(const char *handle) {
    stack[top - (strlen(handle) - 1)] = 'E';
    top -= strlen(handle) - 1;
    stack[top + 1] = '\0';
    printStack();
    printf("\t\t%s$\t\tREDUCE→%s\n", input + i, handle);
}

void check() {
    while (1) {
        if (top >= 0 && stack[top] == 'I') reduce("id");
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') reduce("E+E");
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') reduce("E*E");
        else if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') reduce("(E)");
        else break;
    }
}

int main() {
    printf("GRAMMAR is:\nE → E+E | E*E | (E) | id\n");
    printf("Enter input string: ");
    scanf("%s", input);
    strcat(input, "$");

    printf("\nStack\t\tInput\t\tAction\n");

    while (input[i] != '$') {
        if (input[i] == 'i' && input[i + 1] == 'd') {
            stack[++top] = 'I';
            i += 2;
            printStack();
            printf("\t\t%s\t\tSHIFT→id\n", input + i);
        } else {
            stack[++top] = input[i++];
            printStack();
            printf("\t\t%s\t\tSHIFT→%c\n", input + i, stack[top]);
        }
        check();
    }

    if (top == 0 && stack[0] == 'E')
        printf("\nInput string is VALID.\n");
    else
        printf("\nInput string is INVALID.\n");
}
