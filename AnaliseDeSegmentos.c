#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void AjeitarVetor(int **vetor, int *tamanho) {
    int *vetor_unico = (int *)malloc(*tamanho * sizeof(int));
    int index = 0;

    bubble_sort(*vetor, *tamanho);
    
    vetor_unico[index++] = (*vetor)[0];

    for (int i = 1; i < *tamanho; i++) {
        if ((*vetor)[i] != (*vetor)[i - 1]) {
            vetor_unico[index++] = (*vetor)[i];
        }
    }

    *tamanho = index;
    *vetor = (int *)realloc(*vetor, index * sizeof(int));

    for (int i = 0; i < index; i++) {
        (*vetor)[i] = vetor_unico[i];
    }

    free(vetor_unico);
}

int main() {
    int tamanho_vetor, num_segmentos = 0, cont = 0, aux = 0;
    int *vetor, *vetor_pos, *vetor_elementos, **matriz_resultado;

    scanf("%d", &tamanho_vetor);

    vetor = (int *)malloc(tamanho_vetor * sizeof(int));
    vetor_pos = (int *)malloc(sizeof(int));
    vetor_elementos = (int *)malloc(sizeof(int));

    for (int i = 0; i < tamanho_vetor; i++) {
        scanf("%d", &vetor[i]);

        if (i == tamanho_vetor - 1) {
            vetor_pos[num_segmentos] = i;
            num_segmentos++;
        } else if (i != 0 && vetor[i - 1] != vetor[i]) {
            vetor_pos[num_segmentos] = i - 1;
            num_segmentos++;
            vetor_pos = (int *)realloc(vetor_pos, (num_segmentos + 1) * sizeof(int));
        }
    }

    matriz_resultado = (int **)calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
        matriz_resultado[i] = (int *)calloc(num_segmentos, sizeof(int));
    }

    for (int i = 0; i < num_segmentos; i++) {
        vetor_elementos[aux++] = vetor[vetor_pos[i]];
        vetor_elementos = (int *)realloc(vetor_elementos, (aux + 1) * sizeof(int));
    }

    AjeitarVetor(&vetor_elementos, &aux);

    for (int i = 0; i < num_segmentos; i++) {
        for (int j = 0; j < aux; j++) {
            if (vetor[vetor_pos[i]] == vetor_elementos[j]) {
                matriz_resultado[0][i] = j + 1;
                break;
            }
        }
    } 

    for (int i = 0; i < num_segmentos; i++) {
        if (cont == 0) {
            matriz_resultado[1][i] = vetor_pos[cont] + 1;
        } else {
            matriz_resultado[1][i] = vetor_pos[cont] - vetor_pos[cont - 1];
        }
        cont++;
    }
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num_segmentos; j++) {
            if (j == num_segmentos - 1) {
                printf("%d", matriz_resultado[i][j]);
            }
            else{
                printf("%d ", matriz_resultado[i][j]);
            }
        }
        printf("\n");
    }
    
    for (int i = 0; i < 2; i++) {
        free(matriz_resultado[i]);
    }
    free(matriz_resultado);
    free(vetor);
    free(vetor_pos);

    return 0;
}
