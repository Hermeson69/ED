#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha
{
    int num;
    struct Pilha *prox;
} Pilha;

typedef struct Topo
{
    Pilha *topo;
} Topo;

void add(Topo *topo, int valor)
{
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = topo->topo;
    topo->topo = no;
}

void criar(Topo *topo)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        add(topo, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Topo *topo)
{
    Pilha *atual = topo->topo;
    if (atual == NULL)
    {
        return;
    }
    while (atual != NULL)
    {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("INICIO\n");
}

void remover(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("VAZIA\n");
        return;
    }

    Pilha *atual = topo->topo;
    topo->topo = atual->prox;
    free(atual);
}

void liberar(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("VAZIA\n");
        return;
    }

    while (topo->topo != NULL)
    {
        remover(topo);
    }
    free(topo);
    topo->topo = NULL;
}

void binario(int num)
{
    Topo binario = {NULL};
    if (num == 0)
    {
        add(&binario, num);
    }
    else
    {
        while (num > 0)
        {
            add(&binario, num % 2);
            num /= 2;
        }
    }

    listar(&binario);
    while (binario.topo != NULL)
    {
        remover(&binario);
    }
    
}

