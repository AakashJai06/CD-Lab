#include <stdio.h>
#define MAX 20

int numStates, numSymbols;
int dfa[MAX][MAX];          // DFA transition table
int finalStates[MAX], numFinal;
int distinguishable[MAX][MAX]; // Mark distinguishable pairs

// Check if a state is final
int isFinal(int state) {
    for (int i = 0; i < numFinal; i++)
        if (finalStates[i] == state)
            return 1;
    return 0;
}

void minimizeDFA() {
    // Step 1: Mark pairs (p,q) where one is final and other is not
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < i; j++) {
            if (isFinal(i) != isFinal(j))
                distinguishable[i][j] = 1;
            else
                distinguishable[i][j] = 0;
        }
    }

    // Step 2: Keep marking pairs that are indirectly distinguishable
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < numStates; i++) {
            for (int j = 0; j < i; j++) {
                if (distinguishable[i][j]) continue; // already marked

                for (int k = 0; k < numSymbols; k++) {
                    int a = dfa[i][k];
                    int b = dfa[j][k];
                    if (a == b) continue;
                    if (a < b) { int tmp = a; a = b; b = tmp; }
                    if (distinguishable[a][b]) {
                        distinguishable[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    } while (changed);

    // Step 3: Group equivalent (non-distinguishable) states
    int group[MAX];
    for (int i = 0; i < numStates; i++)
        group[i] = -1;

    int g = 0; // number of groups
    for (int i = 0; i < numStates; i++) {
        if (group[i] == -1) {
            group[i] = g;
            for (int j = 0; j < numStates; j++) {
                if (i != j && !distinguishable[i > j ? i : j][i > j ? j : i])
                    group[j] = g;
            }
            g++;
        }
    }

    // Step 4: Print minimized DFA
    printf("\nMinimized DFA Groups:\n");
    for (int i = 0; i < g; i++) {
        printf("Group %d: ", i);
        for (int j = 0; j < numStates; j++)
            if (group[j] == i) printf("q%d ", j);
        printf("\n");
    }

    // Step 5: Print transitions between groups
    printf("\nTransitions between groups:\n");
    for (int i = 0; i < g; i++) {
        int rep = -1; // representative of the group
        for (int j = 0; j < numStates; j++) {
            if (group[j] == i) { rep = j; break; }
        }

        printf("Group %d: ", i);
        for (int k = 0; k < numSymbols; k++) {
            printf("--%c--> Group %d ", 'a' + k, group[dfa[rep][k]]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &numStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);

    printf("Enter transition table (to_state for each symbol):\n");
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            scanf("%d", &dfa[i][j]);
        }
    }

    printf("Enter number of final states: ");
    scanf("%d", &numFinal);

    printf("Enter final states: ");
    for (int i = 0; i < numFinal; i++)
        scanf("%d", &finalStates[i]);

    minimizeDFA();
    return 0;
}
