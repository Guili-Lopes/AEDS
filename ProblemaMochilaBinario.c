#include <stdio.h>
#include <stdlib.h>


struct Item{
    int peso, valor;
    int estado;
};

int Solucao_Otima(struct Item *itens, int tam, int capacidade) {
    int **dp = malloc((tam + 1) * sizeof(int *));
    for (int i = 0; i <= tam; i++) {
        dp[i] = malloc((capacidade + 1) * sizeof(int));
    }

    for (int i = 0; i <= tam; i++) {
        for (int w = 0; w <= capacidade; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (itens[i - 1].peso <= w) {
                dp[i][w] = (itens[i - 1].valor + dp[i - 1][w - itens[i - 1].peso] > dp[i - 1][w])
                           ? itens[i - 1].valor + dp[i - 1][w - itens[i - 1].peso]
                           : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int melhorSolucao = dp[tam][capacidade];

    for (int i = 0; i <= tam; i++) {
        free(dp[i]);
    }
    free(dp);

    return melhorSolucao;
}

int Solucao_Nao_Otima(struct Item *itens, int tam, int valorMAX){
    int total_valor = 0;

    for (int i = 0; i < tam; i++){
        if (itens[i].estado == 1)
        {
            total_valor = total_valor + itens[i].valor;
        }
    }

    if (total_valor < valorMAX)
    {
        return 1;
    }

    return 0;
}

int Solucao_Inviavel(struct Item *itens, int tam, int pesoMAX){
    int total_peso = 0;

    for (int i = 0; i < tam; i++){
        if (itens[i].estado == 1)
        {
            total_peso = total_peso + itens[i].peso;
        }
    }

    if (total_peso <= pesoMAX)
    {
        return 0;
    }

    return 1;
}

int main(){

    int capacidade_mochila, num_itens, valorMax;

    scanf("%d", &capacidade_mochila);
    scanf("%d", &num_itens);

    struct Item  *mochila = malloc(num_itens * sizeof(struct Item));

    for (int i = 0; i < num_itens; i++)
    {
        scanf("%d %d", &mochila[i].peso, &mochila[i].valor);
    }

    for (int i = 0; i < num_itens; i++)
    {
        scanf("%d", &mochila[i].estado);
    }

    if(Solucao_Inviavel(mochila, num_itens, capacidade_mochila)){
        printf("Solucao inviavel.\n");
        return 0;
    }

    valorMax = Solucao_Otima(mochila, num_itens, capacidade_mochila);

    if(Solucao_Nao_Otima(mochila, num_itens, valorMax)){
        printf("Solucao viavel mas nao otima.\n");
        return 0;
    }

    printf("Solucao otima.\n");

    free(mochila);
    return 0;
}
