//Implement the back end of the compiler which takes the three address code and produces the 8086 assembly language instructions that can be assembled and run using an 8086 assembler. The target assembly instructions can be simple move, add, sub, jump etc

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char icode[20][50];  
    char line[50];
    int i = 0;
    printf("Enter intermediate code (type 'exit' to finish):\n");
    while (1) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0; 
        if (strcmp(line, "exit") == 0) break;
        strcpy(icode[i++], line);
    }
    printf("\nTarget 8086 Assembly Code:\n");
    printf("************************\n");
    for (int k = 0; k < i; k++) {
        char dest, arg1, arg2, op = 0;
        int len = strlen(icode[k]);
        dest = icode[k][0];
        arg1 = icode[k][2];
        if (len > 3) { 
            op = icode[k][3];
            arg2 = icode[k][4];
        }

        printf("; %s\n", icode[k]);
        printf("MOV AX, %c\n", arg1);
        if (op == '+') printf("ADD AX, %c\n", arg2);
        else if (op == '-') printf("SUB AX, %c\n", arg2);
        else if (op == '*') {
            printf("MOV BX, %c\n", arg2);
            printf("MUL BX\n");
        }
        else if (op == '/') {
            printf("MOV BX, %c\n", arg2);
            printf("DIV BX\n");
        }
        printf("MOV %c, AX\n\n", dest);
    }
    return 0;
}
