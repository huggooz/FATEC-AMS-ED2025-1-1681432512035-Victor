#include <stdio.h>

void aplicarDesconto(float *preco, float desconto, int *tipoDesconto, float *valorDesconto) {
    if (*tipoDesconto == 1) {
        *valorDesconto = *preco * (desconto / 100);
        *preco -= *valorDesconto; // Desconto em porcentagem
    } else {
        *valorDesconto = desconto;
        *preco -= *valorDesconto; // Desconto em reais
    }
}

int main() {
    float preco, desconto, valorDesconto = 0;
    int aplicar, tipoDesconto;
    
    printf("Informe o preço do produto: ");
    scanf("%f", &preco);
    
    printf("Deseja aplicar algum desconto? (1 - Sim, 0 - Não): ");
    scanf("%d", &aplicar);
    
    if (aplicar) {
        printf("Qual o tipo de desconto (1 - Percentual, 2 - Em reais): ");
        scanf("%d", &tipoDesconto);
        
        printf("Informe o valor do desconto: ");
        scanf("%f", &desconto);
        
        aplicarDesconto(&preco, desconto, &tipoDesconto, &valorDesconto);
    }
    
    printf("\nValor do desconto: R$ %.2f\n", valorDesconto);
    printf("Preço final: R$ %.2f\n", preco);
    
    return 0;
}
