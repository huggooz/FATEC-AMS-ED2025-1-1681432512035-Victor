#include <stdio.h>

void aplicarDesconto(float *preco, float desconto, int *tipoDesconto, float *valorDesconto, float *preco_final) {
    if (*tipoDesconto == 1) {
        *valorDesconto = *preco * (desconto / 100);
        *preco_final = *preco - *valorDesconto; 
    } else {
        *valorDesconto = desconto;
        *preco_final = *preco - *valorDesconto; 
    }
}

int main() {
    float preco, desconto, valorDesconto = 0, preco_final;
    int aplicar, tipoDesconto;
    
    printf("Informe o preço do produto: ");
    scanf("%f", &preco);
    
    printf("Deseja aplicar algum desconto? (1 - Sim, 0 - Não): ");
    scanf("%d", &aplicar);
    
    if (aplicar == 1) {
        printf("Qual o tipo de desconto (1 - Percentual, 2 - Em reais): ");
        scanf("%d", &tipoDesconto);
        
        printf("Informe o valor do desconto: ");
        scanf("%f", &desconto);
        
        aplicarDesconto(&preco, desconto, &tipoDesconto, &valorDesconto, &preco_final);
    }
    else{
        
        aplicarDesconto(&preco, desconto, &tipoDesconto, &valorDesconto, &preco_final);
    }
    
    printf("\nPreço original: R$ %.2f", preco);
    printf("\nValor do desconto: R$ %.2f\n", valorDesconto);
    printf("Preço final: R$ %.2f\n", preco_final);
    
    return 0;
}
