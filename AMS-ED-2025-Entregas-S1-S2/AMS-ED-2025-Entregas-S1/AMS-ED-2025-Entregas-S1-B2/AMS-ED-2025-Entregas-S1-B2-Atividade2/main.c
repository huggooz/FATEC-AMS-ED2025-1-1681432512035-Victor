/*----------------------------------------------------------------------------------/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    /
/                         Id da Atividade: S1-B2-2                                  /
/             Objetivo: << BubbleSort >>                                            /
/                                                                                   /
/                                  Autor: Fernando Alcantara D'Avila                /
/                                                                  Data:06/05/2025  /
/----------------------------------------------------------------------------------*/
#include <stdio.h>

void bubbleSort(int array[], int N) {
    int i, j, temp;

    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main() {
    int N;


    printf("Digite o número de elementos: ");
    scanf("%d", &N);

    int array[N];


    printf("Digite os %d elementos:\n", N);
    for (int i = 0; i < N; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    printf("\nVetor original: ");
    printArray(array, N);

    bubbleSort(array, N);

    printf("Vetor ordenado: ");
    printArray(array, N);

    return 0;
}
