#include <stdio.h>
#define MAX 10

int nfa[MAX][MAX][MAX]; // NFA[from][symbol][to]
int numStates, numSymbols;
char symbols[MAX];

int dfa[1 << MAX][MAX];       // DFA transitions
int dfaStates[1 << MAX][MAX]; // Each DFA state = a set of NFA states
int dfaCount = 0;

// Get index of symbol
int symbolIndex(char c) {
    for (int i = 0; i < numSymbols; i++)
        if (symbols[i] == c)
            return i;
    return -1;
}

// Check if a DFA state (set) already exists
int findDFAState(int newSet[], int size) {
    for (int i = 0; i < dfaCount; i++) {
        int same = 1;
        for (int j = 0; j < size; j++) {
            if (dfaStates[i][j] != newSet[j]) {
                same = 0;
                break;
            }
        }
        if (same) return i;
    }
    return -1;
}

int main() {
    int numTrans;
    printf("Enter number of NFA states: ");
    scanf("%d", &numStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);

    printf("Enter symbols (e.g., a b): ");
    for (int i = 0; i < numSymbols; i++)
        scanf(" %c", &symbols[i]);

    printf("Enter number of transitions: ");
    scanf("%d", &numTrans);
    printf("Enter transitions (from symbol to):\n");
    for (int i = 0; i < numTrans; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int s = symbolIndex(sym);
        nfa[from][s][to] = 1;
    }

    // Initialize DFA with start state {0}
    for (int i = 0; i < numStates; i++)
        dfaStates[0][i] = (i == 0) ? 1 : 0;
    dfaCount = 1;

    // Subset construction
    for (int curr = 0; curr < dfaCount; curr++) {
        for (int s = 0; s < numSymbols; s++) {
            int newSet[MAX] = {0};

            // For each NFA state in the current DFA set
            for (int i = 0; i < numStates; i++) {
                if (dfaStates[curr][i]) {
                    // Check NFA transitions
                    for (int j = 0; j < numStates; j++) {
                        if (nfa[i][s][j])
                            newSet[j] = 1;
                    }
                }
            }

            // If new set is non-empty and new, add to DFA states
            int exists = findDFAState(newSet, numStates);
            if (exists == -1) {
                for (int j = 0; j < numStates; j++)
                    dfaStates[dfaCount][j] = newSet[j];
                dfa[curr][s] = dfaCount;
                dfaCount++;
            } else {
                dfa[curr][s] = exists;
            }
        }
    }

    // Print DFA transition table
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfaCount; i++) {
        printf("DFA state %d: ", i);
        for (int s = 0; s < numSymbols; s++) {
            printf(" --%c--> %d ", symbols[s], dfa[i][s]);
        }
        printf("\n");
    }

    return 0;
}
