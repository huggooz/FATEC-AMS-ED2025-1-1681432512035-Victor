#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_EXPR_LEN 400

typedef struct {
    char expressao[MAX_SIZE][MAX_EXPR_LEN]; 
    double data[MAX_SIZE]; 
    int top;
} Pilha;

void criar_pilha(Pilha *p) {
    p->top = -1;
}

int vazia(Pilha *p) {
    return p->top == -1;
}

int cheia(Pilha *p) {
    return p->top == MAX_SIZE - 1;
}

void push(Pilha *p, double dado, const char *expr) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->data[++p->top] = dado;
    strncpy(p->expressao[p->top], expr, MAX_EXPR_LEN - 1);
    p->expressao[p->top][MAX_EXPR_LEN - 1] = '\0'; 
}

double pop(Pilha *p, char *expr) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    strncpy(expr, p->expressao[p->top], MAX_EXPR_LEN - 1);
    expr[MAX_EXPR_LEN - 1] = '\0'; 
    return p->data[p->top--];
}

void calcular_rpn(char *entrada) {
    Pilha pilha;
    criar_pilha(&pilha);
    char *tokens[MAX_SIZE];
    int count = 0;

    char *token = strtok(entrada, " ");
    while (token != NULL) {
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < count; i++) {
        token = tokens[i];

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pilha, atof(token), token);
        } else {
            if (pilha.top < 1) {
                printf("Erro: Expressao invalida!\n");
                return;
            }
            char expr1[MAX_EXPR_LEN], expr2[MAX_EXPR_LEN];
            double b = pop(&pilha, expr2);
            double a = pop(&pilha, expr1);

            char novaExpr[MAX_EXPR_LEN];
            if (snprintf(novaExpr, sizeof(novaExpr), "(%s %c %s)", expr1, token[0], expr2) >= MAX_EXPR_LEN) {
                printf("Erro: Expressao muito longa!\n");
                return;
            }

            switch (token[0]) {
                case '+': push(&pilha, a + b, novaExpr); break;
                case '-': push(&pilha, a - b, novaExpr); break;
                case '*': push(&pilha, a * b, novaExpr); break;
                case '/':
                    if (b == 0) {
                        printf("Erro: Divisao por zero!\n");
                        return;
                    }
                    push(&pilha, a / b, novaExpr);
                    break;
                default:
                    printf("Erro: Operador invalido!\n");
                    return;
            }
        }
    }

    if (pilha.top != 0) {
        printf("Erro: Expressao invalida!\n");
        return;
    }

    char resultadoExpr[MAX_EXPR_LEN];
    double resultado = pop(&pilha, resultadoExpr);
    printf("Expressao algébrica: %s\n", resultadoExpr);
    printf("Resultado: %.2f\n", resultado);
}

int main() {
    char expressao[256];

    while (1) {
        printf("Digite a expressao RPN (ou 'sair' para encerrar): ");
        fgets(expressao, sizeof(expressao), stdin);
        expressao[strcspn(expressao, "\n")] = 0;

        if (strcmp(expressao, "sair") == 0) {
            printf("Encerrando a calculadora...\n");
            break;
        }

        calcular_rpn(expressao);
        printf("\n");
    }

    return 0;
}
