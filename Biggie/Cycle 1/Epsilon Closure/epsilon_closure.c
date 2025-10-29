#include <stdio.h>
#define MAX 20

int numStates;
int eTransition[MAX][MAX];   // epsilon transitions
int eClosure[MAX][MAX];      // epsilon closure of each state
int closureSize[MAX];        // size of closure for each state

// DFS to compute epsilon-closure
void dfs(int state, int closure[], int *size) {
    if (closure[state]) return;   // already visited
    closure[state] = 1;           // mark state as included
    (*size)++;                    // increase closure size

    for (int i = 0; i < numStates; i++) {
        if (eTransition[state][i]) {
            dfs(i, closure, size);
        }
    }
}

// Compute epsilon-closures for all states
void computeEClosures() {
    for (int i = 0; i < numStates; i++) {
        int closure[MAX] = {0};
        int size = 0;
        dfs(i, closure, &size);

        int k = 0;
        for (int j = 0; j < numStates; j++) {
            if (closure[j]) {
                eClosure[i][k++] = j;
            }
        }
        closureSize[i] = k;
    }
}

// Print epsilon-closures
void printEClosures() {
    printf("\nEpsilon-closures:\n");
    for (int i = 0; i < numStates; i++) {
        printf("E-closure(q%d) = { ", i);
        for (int j = 0; j < closureSize[i]; j++) {
            printf("q%d ", eClosure[i][j]);
        }
        printf("}\n");
    }
}

int main() {
    int numET;
    printf("Enter Number of States: ");
    scanf("%d", &numStates);

    printf("Enter Number of Epsilon Transitions: ");
    scanf("%d", &numET);

    printf("Enter Epsilon Transitions (from to):\n");
    for (int i = 0; i < numET; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        eTransition[from][to] = 1;
    }

    computeEClosures();
    printEClosures();

    return 0;
}