/*-----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                     */
/*                                                                                   */
/*       Id da Atividade: Atividade B1-4-Manipulação de Pilha - Implementado HP12c   */
/*                                                                                   */
/*     Objetivo: O programa simula o funcionamento da calculadora financeira HP12c   */
/*               utilizando a notação polonesa reversa (RPN) e uma estrutura de      */
/*               pilha. Ele recebe uma expressão matemática no formato RPN, armazena */
/*               e processa os valores na pilha, realizando operações básicas como   */
/*               soma, subtração, multiplicação e divisão. Ao final, exibe o         */
/*               resultado da operação e a fórmula algébrica correspondente,         */
/*               garantindo que a expressão seja resolvida corretamente seguindo a   */
/*               lógica da pilha.                                                    */
/*                                                                                   */
/*                                  Autor: Victor Hugo Gonçalves                     */
/*                                                                  Data:30/04/2025  */
/*-----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    double data[MAX_SIZE];
    char expr[MAX_SIZE][50];
    int top;
} Pilha;

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->top = -1;
    return p;
}

int vazia(Pilha* p) {
    return p->top == -1;
}

int cheia(Pilha* p) {
    return p->top == MAX_SIZE - 1;
}

void push(Pilha* p, double valor, const char* expr) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->top++;
    p->data[p->top] = valor;
    strcpy(p->expr[p->top], expr);
}

double pop(Pilha* p, char* expr) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(expr, p->expr[p->top]);
    return p->data[p->top--];
}

double top(Pilha* p, char* expr) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(expr, p->expr[p->top]);
    return p->data[p->top];
}

void calcular_RPN(char* expressao) {
    Pilha* pilha = criar_pilha();
    char* token = strtok(expressao, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            double num = atof(token);
            char temp[20];
            sprintf(temp, "%.2f", num);
            push(pilha, num, temp);
        } else {
            if (pilha->top < 1) {
                printf("Erro: Expressão inválida!\n");
                return;
            }
            char exprX[50], exprY[50];
            double y = pop(pilha, exprY);
            double x = pop(pilha, exprX);
            double t;
            char z = token[0];
            char novaExpr[150];
            
            switch (z) {
                case '+': t = x + y; break;
                case '-': t = x - y; break;
                case '*': t = x * y; break;
                case '/':
                    if (y == 0) {
                        printf("Erro: Divisão por zero!\n");
                        return;
                    }
                    t = x / y;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    return;
            }
            
            snprintf(novaExpr, sizeof(novaExpr), "(%s %c %s)", exprX, z, exprY);
            push(pilha, t, novaExpr);
        }
        token = strtok(NULL, " ");
    }
    
    if (pilha->top != 0) {
        printf("Erro: Expressão inválida!\n");
        return;
    }
    
    char resultadoExpr[100];
    double resultadoFinal = pop(pilha, resultadoExpr);
    printf("Resultado: %.2f\n", resultadoFinal);
    printf("Expressão algebrica: %s\n", resultadoExpr);
    
    free(pilha);
}

int main() {
    char expressao[MAX_SIZE];

    while (1) {
        printf("\nDigite a expressão RPN (ou 'sair' para encerrar): ");
        fgets(expressao, MAX_SIZE, stdin);
        expressao[strcspn(expressao, "\n")] = 0;

        if (strcmp(expressao, "sair") == 0) {
            printf("Encerrando o programa...\n");
            break;
        }

        calcular_RPN(expressao);
    }

    return 0;
}
