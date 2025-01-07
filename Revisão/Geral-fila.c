#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    int num;
    struct No *prox;
} No;

typedef struct Fila
{
    No *frente;
    No *atras;
} Fila;

No *criar_no(int num)
{
    No *no = (No *)malloc(sizeof(No));
    if (!no)
    {
        printf("Erro no Malloc\n");
        return;
    }
    no->num = num;
    no->prox = NULL;
    return no;
}

Fila *inicializar()
{
    Fila *inicio = (Fila *)malloc(sizeof(Fila));
    if (!inicio)
    {
        printf("Erro no Malloc\n");
        return;
    }
    inicio->frente = inicio->atras = NULL;
    return inicio;
}

void add(Fila **inicio, int num)
{
    No *no = criar_no(num);
    Fila *atual = *inicio;
    while (atual == NULL)
    {
        atual->frente = atual->atras = no;
    }
    atual->atras->prox = no;
    atual->atras = no;
}

int remove(Fila **inicio)
{
    Fila *atual = *inicio;
    if (atual->atras == NULL)
    {
        printf("Fila vazia\n");
        exit(-1);
    }
    No *temp = atual->frente;
    int temp_valor = temp->num;
    atual->frente = atual->frente->prox;
    if (atual->frente == NULL)
    {
        atual->atras = NULL;
    }
    free(temp);
    return temp_valor;
}

int fila_vazia(Fila *fila)
{
    return fila->frente == NULL;
}

void printar(Fila *inicio)
{
    No *temp = inicio->frente;
    while (temp)
    {
        printf("%d -> ", temp->num);
        temp = temp->prox;
    }
    printf("NULL");
    printf("\n");
}


void liberar(Fila **inicio){
    while (!fila_vazia(*inicio))
    {
        remove(inicio);
    }
    free(*inicio);
    inicializar();
}
void impares_pares(Fila *inicio)
{
    Fila *pares = inicializar();
    Fila *impares = inicializar();
    while (!fila_vazia(inicio))
    {
        int num = remove(&inicio);
        if (num % 2 == 0)
        {
            add(&pares, num);
        }
        else
        {
            add(&impares, num);
        }
    }
}

void soma(Fila *fila){
    int soma = 0;
    No *atual = fila->frente;
    while (atual != NULL)
    {
        soma += atual->num;
        atual = atual->prox;
    }
    printf("Soma: %d",soma);
}