#include <stdio.h>
#include <string.h>

#define MAX 20

int numStates, numSymbols, startState;
int finalStates[MAX], numTransitions, numFinalStates;
int nfaTransitions[MAX][MAX][MAX], nfaTransCount[MAX][MAX];
int dfaStates[MAX][MAX], dfaStateCount = 0;
char symbols[MAX];

int main() {
    int i, j, k, fromState, toState;
    char inputSymbol;

    // Input: number of states and symbols
    printf("Enter the number of states and symbols: ");
    scanf("%d %d", &numStates, &numSymbols);

    // Input: start state
    printf("Enter the start state: ");
    scanf("%d", &startState);

    // Input: alphabet symbols
    printf("Enter the symbols: ");
    for (i = 0; i < numSymbols; i++)
        scanf(" %c", &symbols[i]);

    // Input: final states
    printf("Enter the number of final states: ");
    scanf("%d", &numFinalStates);

    printf("Enter the final states: ");
    for (i = 0; i < numFinalStates; i++)
        scanf("%d", &finalStates[i]);

    // Input: NFA transitions
    printf("Enter the number of transitions: ");
    scanf("%d", &numTransitions);

    printf("Enter transitions (format: from symbol to):\n");
    for (i = 0; i < numTransitions; i++) {
        scanf("%d %c %d", &fromState, &inputSymbol, &toState);

        // Find symbol index
        for (j = 0; j < numSymbols; j++)
            if (symbols[j] == inputSymbol)
                break;

        // Store the transition
        nfaTransitions[fromState][j][nfaTransCount[fromState][j]++] = toState;
    }

    // Initialize the first DFA state (start state of NFA)
    dfaStates[0][startState] = 1;
    dfaStateCount = 1;

    // Subset construction (convert NFA → DFA)
    for (i = 0; i < dfaStateCount; i++) {
        for (j = 0; j < numSymbols; j++) {
            int newStateSet[MAX] = {0};

            // For each NFA state in the current DFA state
            for (k = 0; k < numStates; k++) {
                if (dfaStates[i][k]) {
                    // Add all reachable states for this symbol
                    for (int l = 0; l < nfaTransCount[k][j]; l++)
                        newStateSet[nfaTransitions[k][j][l]] = 1;
                }
            }

            // Check if this new DFA state already exists
            int existingIndex = -1;
            for (int m = 0; m < dfaStateCount; m++) {
                if (memcmp(dfaStates[m], newStateSet, sizeof(newStateSet)) == 0) {
                    existingIndex = m;
                    break;
                }
            }

            // If not found, add it as a new DFA state
            if (existingIndex == -1) {
                memcpy(dfaStates[dfaStateCount], newStateSet, sizeof(newStateSet));
                dfaStateCount++;
            }
        }
    }

    // Print all DFA states (each subset of NFA states)
    printf("\nDFA States:\n");
    for (i = 0; i < dfaStateCount; i++) {
        printf("Q%d = {", i);
        for (j = 0; j < numStates; j++)
            if (dfaStates[i][j])
                printf("q%d ", j);
        printf("}\n");
    }

    // Print DFA final states (any DFA state containing an NFA final state)
    printf("\nFinal DFA States: ");
    for (i = 0; i < dfaStateCount; i++) {
        for (j = 0; j < numStates; j++) {
            for (k = 0; k < numFinalStates; k++) {
                if (dfaStates[i][j] && finalStates[k] == j) {
                    printf("Q%d ", i);
                    j = numStates; // break out of inner loop
                    break;
                }
            }
        }
    }

    printf("\n");
    return 0;
}