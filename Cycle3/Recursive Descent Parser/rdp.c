#include <stdio.h>
#include <string.h>

char input[50];
int i = 0;
char expr[100] = "E";  // to show current expression form

void printStep(const char *rule) {
    printf("E=%-25s %s\n", expr, rule);
}

void replace(char from, const char *to) {
    char temp[100];
    int j = 0;
    for (int k = 0; expr[k]; k++) {
        if (expr[k] == from) {
            for (int x = 0; to[x]; x++)
                temp[j++] = to[x];
        } else {
            temp[j++] = expr[k];
        }
    }
    temp[j] = '\0';
    strcpy(expr, temp);
}

void E(), Edash(), T(), Tdash(), F();

void E() {
    replace('E', "TE'");
    printStep("E -> TE'");
    T();
    Edash();
}

void Edash() {
    if (input[i] == '+') {
        replace('E', "+TE'");
        printStep("E' -> +TE'");
        i++;
        T();
        Edash();
    } else {
        replace('E', "e");
        printStep("E' -> e");
    }
}

void T() {
    replace('T', "FT'");
    printStep("T -> FT'");
    F();
    Tdash();
}

void Tdash() {
    if (input[i] == '*') {
        replace('T', "*FT'");
        printStep("T' -> *FT'");
        i++;
        F();
        Tdash();
    } else {
        replace('T', "e");
        printStep("T' -> e");
    }
}

void F() {
    if (input[i] == '(') {
        replace('F', "(E)");
        printStep("F -> (E)");
        i++;
        E();
        if (input[i] == ')') i++;
    } else if (input[i] == 'i') {
        replace('F', "i");
        printStep("F -> i");
        i++;
    } else {
        printf("\nError: invalid symbol '%c'\n", input[i]);
    }
}

int main() {
    printf("Grammar without left recursion:\n");
    printf("E -> TE'\nE' -> +TE' | e\nT -> FT'\nT' -> *FT' | e\nF -> (E) | i\n");
    printf("\nEnter the input expression: ");
    scanf("%s", input);

    printf("\nExpressions\t\tSequence of production rules\n");
    E();

    if (input[i] == '\0')
        printf("\nE=%s\n", input);
    else
        printf("\nInvalid Expression\n");
}
