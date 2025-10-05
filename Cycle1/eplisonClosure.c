#include <stdio.h>

#define MAX 10

int eps[MAX][MAX];   // epsilon transition table
int visited[MAX];    // to track visited states
int n;               // number of states

// function to find epsilon closure using DFS
void findClosure(int state) {
    visited[state] = 1;
    printf("q%d ", state);

    for (int i = 0; i < n; i++) {
        // if epsilon transition exists and not visited
        if (eps[state][i] && !visited[i]) {
            findClosure(i);
        }
    }
}

int main() {
    int e, from, to;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);

    // initialize the epsilon table
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            eps[i][j] = 0;

    printf("Enter each epsilon transition (from to):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &from, &to);
        eps[from][to] = 1;
    }

    printf("\nEpsilon closures:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            visited[j] = 0;  // reset visited

        printf("ε-closure(q%d): { ", i);
        findClosure(i);
        printf("}\n");
    }

    return 0;
}
