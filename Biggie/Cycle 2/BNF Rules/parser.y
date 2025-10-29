%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AST {
    char *nodeType;
    int value;
    struct AST *left, *right;
} AST;

AST* makeNode(char *type, AST *l, AST *r) {
    AST *node = (AST*) malloc(sizeof(AST));
    node->nodeType = strdup(type);
    node->value = 0;
    node->left = l;
    node->right = r;
    return node;
}

AST* makeNodeNum(int val) {
    AST *node = (AST*) malloc(sizeof(AST));
    node->nodeType = strdup("NUM");
    node->value = val;
    node->left = node->right = NULL;
    return node;
}

void printAST(AST *root, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) 
        printf("  ");
    if (strcmp(root->nodeType, "NUM") == 0)
        printf("%s(%d)\n", root->nodeType, root->value);
    else
        printf("%s\n", root->nodeType);
    printAST(root->left, level + 1);
    printAST(root->right, level + 1);
}
%}

%union {
    int num;
    struct AST *node;
}

%token <num> NUMBER
%type <node> expr

%left '+' '-'
%left '*' '/'
%left UMINUS

%%

start : expr { 
            printf("\nAbstract Syntax Tree:\n"); 
            printAST($1, 0); 
        }
      ;

expr  : expr '+' expr           { $$ = makeNode("+", $1, $3); }
      | expr '-' expr           { $$ = makeNode("-", $1, $3); }
      | expr '*' expr           { $$ = makeNode("*", $1, $3); }
      | expr '/' expr           { $$ = makeNode("/", $1, $3); }
      | '-' expr %prec UMINUS   { $$ = makeNode("NEG", $2, NULL); }
      | '(' expr ')'            { $$ = $2; }
      | NUMBER                  { $$ = makeNodeNum($1); }
      ;

%%

int main() {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}