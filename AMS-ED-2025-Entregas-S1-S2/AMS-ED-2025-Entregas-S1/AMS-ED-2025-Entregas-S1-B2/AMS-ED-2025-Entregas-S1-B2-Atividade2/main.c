/*-----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                     */
/*                                                                                   */
/*                                      Id da Atividade: Atividade B2-2-Bubblesort   */
/*                                                                                   */
/*   Objetivo: Programa em C que lê 5 números inteiros, os ordena usando o           */
/*             algoritmo Bubble Sort (com estrutura de repetição while) e exibe o    */
/*             vetor antes e depois da ordenação. A ordenação é feita comparando     */
/*             pares de elementos vizinhos e trocando-os se estiverem fora de ordem. */                                                   */
/*                                                                                   */
/*                                  Autor: Victor Hugo Gonçalves                     */
/*                                                                  Data:06/05/2025  */
/*-----------------------------------------------------------------------------------*/

#include <stdio.h>

void bubbleSort(int vet[]) {
    int i, n = 5, cont = 0;

    while (cont < n) {
        i = 0;
        while (i < n - 1 - cont) {
            if (vet[i] > vet[i + 1]) {
                int temp = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = temp;
            }
            i++;
        }
        cont++;
    }
}

int main() {
    int vet[5];
    int i;

    printf("Digite 5 números inteiros: (ex: 3 2 4 1 5)\n");
    i = 0;
    while (i < 5) {
        scanf("%d", &vet[i]);
        i++;
    }

    printf("\nAntes da ordenação:\n");
    i = 0;
    while (i < 5) {
        printf("%d ", vet[i]);
        i++;
    }

    bubbleSort(vet);

    printf("\nDepois da ordenação:\n");
    i = 0;
    while (i < 5) {
        printf("%d ", vet[i]);
        i++;
    }

    return 0;
}

