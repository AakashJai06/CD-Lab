#include <stdio.h>
#define MAX 20
#define SYMBOLS 10

int nStates, nSymbols;
char symbols[SYMBOLS];

// Transition tables
int eps[MAX][MAX];                  // ε transitions
int trans[MAX][SYMBOLS][MAX];       // Normal transitions
int newTrans[MAX][SYMBOLS][MAX];    // After removing ε
int eClosure[MAX][MAX];             // ε-closure of each state
int closureSize[MAX];

// Find index of symbol
int getSymbolIndex(char ch) {
    for (int i = 0; i < nSymbols; i++)
        if (symbols[i] == ch)
            return i;
    return -1;
}

// DFS to find ε-closure
void dfs(int state, int visited[]) {
    if (visited[state]) return;
    visited[state] = 1;
    for (int i = 0; i < nStates; i++) {
        if (eps[state][i])
            dfs(i, visited);
    }
}

// Compute ε-closure for every state
void computeEClosures() {
    for (int i = 0; i < nStates; i++) {
        int visited[MAX] = {0};
        dfs(i, visited);

        closureSize[i] = 0;
        for (int j = 0; j < nStates; j++) {
            if (visited[j])
                eClosure[i][closureSize[i]++] = j;
        }
    }
}

// Build transitions without ε
void removeEpsilonTransitions() {
    for (int s = 0; s < nStates; s++) {
        for (int sym = 0; sym < nSymbols; sym++) {
            int added[MAX] = {0};

            for (int i = 0; i < closureSize[s]; i++) {
                int p = eClosure[s][i]; // state reachable through ε
                for (int j = 0; j < nStates; j++) {
                    if (trans[p][sym][j]) { // transition on symbol
                        // Add ε-closure of j
                        for (int k = 0; k < closureSize[j]; k++) {
                            int q = eClosure[j][k];
                            newTrans[s][sym][q] = 1;
                            added[q] = 1;
                        }
                    }
                }
            }
        }
    }
}

// Print transition table
void printTransitions(int t[MAX][SYMBOLS][MAX], const char *title) {
    printf("\n%s:\n", title);
    for (int s = 0; s < nStates; s++) {
        for (int sym = 0; sym < nSymbols; sym++) {
            printf("q%d -- %c --> ", s, symbols[sym]);
            int flag = 0;
            for (int j = 0; j < nStates; j++) {
                if (t[s][sym][j]) {
                    printf("q%d ", j);
                    flag = 1;
                }
            }
            if (!flag) printf("∅");
            printf("\n");
        }
    }
}

int main() {
    int numET, numNT;

    printf("Enter number of states: ");
    scanf("%d", &nStates);

    printf("Enter number of input symbols (excluding ε): ");
    scanf("%d", &nSymbols);

    printf("Enter the symbols (e.g., a b): ");
    for (int i = 0; i < nSymbols; i++)
        scanf(" %c", &symbols[i]);

    printf("Enter number of ε-transitions: ");
    scanf("%d", &numET);
    printf("Enter ε-transitions (from to):\n");
    for (int i = 0; i < numET; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        eps[from][to] = 1;
    }

    printf("Enter number of normal transitions: ");
    scanf("%d", &numNT);
    printf("Enter transitions (from symbol to):\n");
    for (int i = 0; i < numNT; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int idx = getSymbolIndex(sym);
        trans[from][idx][to] = 1;
    }

    computeEClosures();
    removeEpsilonTransitions();

    printTransitions(trans, "Original NFA Transitions");
    printTransitions(newTrans, "NFA without ε-transitions");

    return 0;
}
