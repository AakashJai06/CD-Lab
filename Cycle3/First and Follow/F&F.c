#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20], first[20][20], follow[20][20];
int n;

void add(char *res, char c) {
    for (int i = 0; res[i]; i++) if (res[i] == c) return;
    int len = strlen(res); res[len] = c; res[len + 1] = '\0';
}

void findFirst(char *res, char c) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (!isupper(prod[i][2])) add(res, prod[i][2]);
            else findFirst(res, prod[i][2]);
        }
    }
}

void findFollow(char *res, char c) {
    if (c == prod[0][0]) add(res, '$');
    for (int i = 0; i < n; i++) {
        for (int j = 2; prod[i][j]; j++) {
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
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    printf("Enter productions:\n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);

    for (int i = 0; i < n; i++) findFirst(first[i], prod[i][0]);
    for (int i = 0; i < n; i++) findFollow(follow[i], prod[i][0]);

    printf("\nFirsts:\n");
    for (int i = 0; i < n; i++)
        printf("%c : %s\n", prod[i][0], first[i]);

    printf("\nFollows:\n");
    for (int i = 0; i < n; i++)
        printf("%c : %s\n", prod[i][0], follow[i]);
}
