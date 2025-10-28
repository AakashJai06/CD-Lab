#include <stdio.h>
#include <string.h>

void gen(char *expr, char op, char *r) {
    char t[100]; int i = 0, j = 0;
    while (expr[i]) {
        if (expr[i] == op) {
            printf("%c\t%c\t%c\t%c\n", op, *r, expr[i-1], expr[i+1]);
            t[j-1] = *r; 
            i += 2;
            (*r)--;
        } else t[j++] = expr[i++];
    }
    t[j] = '\0';
    strcpy(expr, t);
}

int main() {
    char expr[100], r = 'Z';
    printf("Enter expression:\n");
    scanf("%s", expr);
    printf("Op\tDestn\tArg1\tArg2\n");

    for (char *ops = "/*+-="; *ops; ops++)
        gen(expr, *ops, &r);

    return 0;
}
