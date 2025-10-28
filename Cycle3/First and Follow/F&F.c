#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20], first[20][20], follow[20][20];
int n;

void add(char *res, char c) {
    if (c == '\0') return;
    for (int i = 0; res[i]; i++) if (res[i] == c) return;
    int len = strlen(res);
    res[len] = c;
    res[len + 1] = '\0';
}

void findFirst(char *res, char c) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            int j = 3; // Skip A-> part
            if (!prod[i][j]) continue;
            if (!isupper(prod[i][j])) add(res, prod[i][j]);
            else findFirst(res, prod[i][j]);
        }
    }
}

void findFollow(char *res, char c) {
    if (c == prod[0][0]) add(res, '$');
    for (int i = 0; i < n; i++) {
        for (int j = 3; prod[i][j]; j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] && !isupper(prod[i][j + 1]))
                    add(res, prod[i][j + 1]);
                else if (prod[i][j + 1])
                    findFirst(res, prod[i][j + 1]);
                else if (prod[i][0] != c)
                    findFollow(res, prod[i][0]);
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (e.g. E->E+T):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    for (int i = 0; i < n; i++) findFirst(first[i], prod[i][0]);
    for (int i = 0; i < n; i++) findFollow(follow[i], prod[i][0]);

    printf("\nFIRST sets:\n");
    for (int i = 0; i < n; i++)
        printf("FIRST(%c) = { %s }\n", prod[i][0], first[i]);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < n; i++)
        printf("FOLLOW(%c) = { %s }\n", prod[i][0], follow[i]);
}
