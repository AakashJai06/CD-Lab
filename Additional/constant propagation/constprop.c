//Write a program to perform constant propagation

#include <stdio.h>
#include <string.h>

int main() {
    char var[10][10], val[10][10], expr[10][30];
    int n, i, j;

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements (e.g. a=5 or b=a+3):\n");
    for (i = 0; i < n; i++)
        scanf("%s", expr[i]);

    for (i = 0; i < n; i++) {
        // Extract variable name (LHS)
        var[i][0] = expr[i][0];
        var[i][1] = '\0';

        // Extract RHS value
        strcpy(val[i], strchr(expr[i], '=') + 1);

        // Replace known constants in later expressions
        for (j = i + 1; j < n; j++) {
            char *pos = strstr(expr[j], var[i]);
            if (pos) {
                char temp[30];
                strncpy(temp, expr[j], pos - expr[j]);
                temp[pos - expr[j]] = '\0';
                strcat(temp, val[i]);
                strcat(temp, pos + strlen(var[i]));
                strcpy(expr[j], temp);
            }
        }
    }

    printf("\nAfter Constant Propagation:\n");
    for (i = 0; i < n; i++)
        printf("%s\n", expr[i]);

    return 0;
}
