/*
    Nomes: Guilherme Lopes e João Manoel
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* ========================================================================= */

typedef int TipoChave;

typedef struct
{
    int Chave;
    int Tipo;
    int NumElementos;
    int PontoMedio; //  (p+q)/2, onde p e q são as posições do início e do fim do segmento
                    /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
        return;
    }
    q = p->Prox;
    *Item = q->Item;
    p->Prox = q->Prox;
    if (p->Prox == NULL)
        Lista->Ultimo = p;
    free(q);
}

void Imprime(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%d %d %d %d\n", Aux->Item.Chave, Aux->Item.Tipo, Aux->Item.NumElementos, Aux->Item.PontoMedio);
        Aux = Aux->Prox;
    }
}

/* ========================================================================== */
int verificarSequencia(TipoLista lista)
{
    TipoApontador Aux;
    Aux = lista.Primeiro->Prox;

    int cont = 0;
    int sequencia[5] = {1, 3, 2, 3, 1};

    while (Aux != NULL)
    {
        if (Aux->Item.Tipo == sequencia[cont])
        {
            cont++;
            if (cont == 5)
            {
                return 1;
            }
        }
        else
        {
            if (Aux->Item.Tipo == sequencia[0])
            {
                cont = 1;
            }
            else
            {
                cont = 0;
            }
        }
        Aux = Aux->Prox;
    }

    return 0; 
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int *arr, int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}

void imprimirMatriz(int **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (j == colunas - 1)
            {
                printf("%d", matriz[i][j]);
            }
            else
            {
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    int numElem;
    scanf("%d", &numElem);

    int *vetor = (int *)malloc(numElem * sizeof(int));
    int *valoresEncontrados = (int *)malloc(sizeof(int));

    int naoCoincidente = 1;
    int numElementosNaoCoincidentes = 0;

    for (int i = 0; i < numElem; i++)
    {
        scanf("%d", &vetor[i]);
        for (int j = 0; j < i; j++)
        {
            if (vetor[j] == vetor[i])
            {
                naoCoincidente = 0;
                break;
            }
        }
        if (naoCoincidente)
        {
            numElementosNaoCoincidentes++;
            valoresEncontrados = (int *)realloc(valoresEncontrados, numElementosNaoCoincidentes * sizeof(int));
            valoresEncontrados[numElementosNaoCoincidentes - 1] = vetor[i];
        }
        naoCoincidente = 1;
    }

    bubbleSort(valoresEncontrados, numElementosNaoCoincidentes);

    int **resposta = (int **)malloc(2 * sizeof(int *));
    resposta[0] = (int *)malloc(numElem * sizeof(int));
    resposta[1] = (int *)malloc(numElem * sizeof(int));

    int temp = -1;
    int i2 = 1;
    resposta[0][0] = 1;

    for (int i = 0; i < numElem; i++)
    {
        if (vetor[i] != temp)
        {
            for (int j = 0; j < numElementosNaoCoincidentes; j++)
            {
                if (vetor[i] == valoresEncontrados[j])
                {
                    resposta[0][i2 - 1] = j + 1;
                    i2++;
                    break;
                }
            }
        }
        temp = vetor[i];
    }

    resposta[0] = (int *)realloc(resposta[0], i2 * sizeof(int));

    resposta[1][0] = 1;
    i2 = 1;
    temp = vetor[0];
    for (int i = 1; i < numElem; i++)
    {
        if (vetor[i] == temp)
        {
            resposta[1][i2 - 1]++;
        }
        else
        {
            i2++;
            resposta[1] = (int *)realloc(resposta[1], i2 * sizeof(int));
            resposta[1][i2 - 1] = 1;
            temp = vetor[i];
        }
    }

    TipoLista lista;
    FLVazia(&lista);
    int p = 0;
    for (int i = 0, cont = 1; i < i2; i++, cont++)
    {
        TipoItem item;
        item.Chave = cont;
        item.NumElementos = resposta[1][i];
        item.Tipo = resposta[0][i];
        item.PontoMedio = (p + (p + resposta[1][i] - 1)) / 2;
        p += resposta[1][i];
        Insere(item, &lista);
    }

    if(verificarSequencia(lista)){
        printf("Resultado: Padrao encontrado.\n");
    }else{
        printf("Resultado: Padrao nao encontrado.\n");
    }

    free(resposta[0]);
    free(resposta[1]);
    free(resposta);
    free(vetor);
    free(valoresEncontrados);

    return 0;
}
