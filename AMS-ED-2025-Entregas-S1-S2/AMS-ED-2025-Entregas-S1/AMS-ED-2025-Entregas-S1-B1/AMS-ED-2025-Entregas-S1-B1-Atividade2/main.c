/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                                                                                  */
/*             Id da Atividade: Atividade B1-2-Manipulação de Array com ponteiro    */
/*                                                                                  */
/*             Objetivo: Programa para cadastrar candidatos, calcular suas notas    */
/*                       finais com base em diferentes avaliações e exibir os       */
/*                       cinco melhores classificados.                              */
/*                                                                                  */
/*                                  Autor: Victor Hugo Gonçalves                    */
/*                                                                  Data:12/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50
#define MAX_NOTAS_PE 4
#define MAX_NOTAS_AC 5
#define MAX_NOTAS_PP 10
#define MAX_NOTAS_EB 3

struct Candidato {
    char nome[100];
    float notas_PE[MAX_NOTAS_PE];
    float notas_AC[MAX_NOTAS_AC];
    float notas_PP[MAX_NOTAS_PP];
    float notas_EB[MAX_NOTAS_EB];
    float nota_final;
};

// Função para validar notas entre 0.0 e 10.0, com no máximo uma casa decimal
int validar_nota(float *nota) {
    if (*nota < 0 || *nota > 10) {
        return 0;
    }
    int parte_inteira = (int)(*nota * 10);
    float parte_decimal = *nota * 10 - parte_inteira;
    return parte_decimal == 0;
}

// Função para ler notas de um candidato
void ler_notas(float notas[], int quantidade, const char *tipo) {
    for (int i = 0; i < quantidade; i++) {
        do {
            printf("%s - Nota %d: ", tipo, i + 1);
            scanf("%f", &notas[i]);
            if (!validar_nota(&notas[i])) {
                printf("Erro: Digite uma nota válida entre 0.0 e 10.0 com no máximo uma casa decimal.\n");
            }
        } while (!validar_nota(&notas[i]));
    }
}

// Função para calcular a soma excluindo a maior e a menor nota
float soma_central(float notas[], int tamanho) {
    float maior = notas[0], menor = notas[0], soma = 0;
    int i, idx_maior = 0, idx_menor = 0;

    // Encontrar maior e menor nota
    for (i = 1; i < tamanho; i++) {
        if (notas[i] > maior) {
            maior = notas[i];
            idx_maior = i;
        }
        if (notas[i] < menor) {
            menor = notas[i];
            idx_menor = i;
        }
    }

    // Somar todas as notas, excluindo a maior e a menor
    for (i = 0; i < tamanho; i++) {
        if (i != idx_maior && i != idx_menor) {
            soma += notas[i];
        }
    }

    return soma;
}

// Função para calcular a nota final do candidato
float calcular_nota_final(float notas_PE[], float notas_AC[], float notas_PP[], float notas_EB[]) {
    float soma_PE = soma_central(notas_PE, MAX_NOTAS_PE);
    float soma_AC = soma_central(notas_AC, MAX_NOTAS_AC);
    float soma_PP = soma_central(notas_PP, MAX_NOTAS_PP);
    float soma_EB = soma_central(notas_EB, MAX_NOTAS_EB);

    return (soma_PE * 0.3) + (soma_AC * 0.1) + (soma_PP * 0.4) + (soma_EB * 0.2);
}

// Função de comparação para qsort (ordena por nota final decrescente)
int comparar_candidatos(const void *a, const void *b) {
    struct Candidato *c1 = (struct Candidato *)a;
    struct Candidato *c2 = (struct Candidato *)b;
    return (c2->nota_final > c1->nota_final) - (c2->nota_final < c1->nota_final);
}

// Função para exibir os cinco melhores candidatos
void exibir_classificacao(struct Candidato candidatos[], int num_candidatos) {
    printf("\nClassificação dos 5 melhores candidatos:\n");
    printf("------------------------------------------------------------\n");

    // Ordenar os candidatos pelo maior NF usando qsort
    qsort(candidatos, num_candidatos, sizeof(struct Candidato), comparar_candidatos);

    for (int i = 0; i < 5 && i < num_candidatos; i++) {
        printf("Posição: %d\n", i + 1);
        printf("Nome: %s\n", candidatos[i].nome);
        printf("Nota Final: %.2f\n\n", candidatos[i].nota_final);
    }
}

int main() {
    struct Candidato candidatos[MAX_CANDIDATOS];
    int num_candidatos = 0;
    char nome[100];

    while (num_candidatos < MAX_CANDIDATOS) {
        printf("Digite o nome do candidato %d (ou 'fim' para terminar): ", num_candidatos + 1);
        scanf(" %[^\n]", nome); // Evita problemas de buffer

        if (strcmp(nome, "fim") == 0) break;

        strcpy(candidatos[num_candidatos].nome, nome);

        printf("Digite as notas da Prova Escrita (PE):\n");
        ler_notas(candidatos[num_candidatos].notas_PE, MAX_NOTAS_PE, "PE");

        printf("Digite as notas da Análise Curricular (AC):\n");
        ler_notas(candidatos[num_candidatos].notas_AC, MAX_NOTAS_AC, "AC");

        printf("Digite as notas da Prova Prática (PP):\n");
        ler_notas(candidatos[num_candidatos].notas_PP, MAX_NOTAS_PP, "PP");

        printf("Digite as notas da Entrevista em Banca Avaliadora (EB):\n");
        ler_notas(candidatos[num_candidatos].notas_EB, MAX_NOTAS_EB, "EB");

        candidatos[num_candidatos].nota_final = calcular_nota_final(
            candidatos[num_candidatos].notas_PE,
            candidatos[num_candidatos].notas_AC,
            candidatos[num_candidatos].notas_PP,
            candidatos[num_candidatos].notas_EB
        );

        num_candidatos++;
    }

    exibir_classificacao(candidatos, num_candidatos);

    return 0;
}
