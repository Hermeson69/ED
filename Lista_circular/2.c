#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct Lista
{
    int num;
    struct Lista *prox;
} Lista;

void *inicio()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    if (*lista == NULL)
    {
        *lista = novo_no;
        novo_no->prox = *lista;
    }
    else
    {
        Lista *atual = *lista;
        while (atual->prox != *lista)
        {
            atual = atual->prox;
        }

        atual->prox = novo_no;
        novo_no->prox = *lista;
    }
}

void criar_lista(Lista **lista)
{
    int valor;
    for (int i = 0; i < TAM; i++)
    {
        printf("Digite o valor para o elemento %d: ", i + 1);
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }
}

int printar(Lista *lista)
{
    int cont = 0;
    Lista *inicio = lista;
    while (lista != inicio)
    {
        cont++;
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
    printf("INICIO\n");

    return cont;
}

void adicionar_apos(Lista **lista, int valor, int posicao)
{
    if (*lista == NULL)
    {
        printf("Lista Vazia!\n");
    }

    Lista *atual = *lista;
    int cont = 0;
    do
    {
        if (cont == posicao - 1)
        {
            Lista *novo_no = (Lista *)malloc(sizeof(Lista));
            novo_no->num = valor;
            novo_no->prox = atual->prox;
            atual->prox = novo_no;
            return;
        }
        atual = atual->prox;
        cont++;

    } while (atual != lista);
}

void busca(Lista *lista, int valor)
{
    if (lista == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    Lista *busca = lista;
    int cont = 0;
    do
    {
        if (busca->num == valor)
        {
            printf("Elemento encontrado: %d, posicao: %d", valor, cont + 1);
            break;
        }
        busca = busca->prox;
        cont++;

    } while (busca != lista);
    printf("Elemento nao encontrado");
}

void soma_lista(Lista *lista){
    int soma = 0;
    Lista *atual = lista;
    float media = 0;
    int cont = 0;
    do
    {
        soma += atual->num;
        atual = atual->prox;
        cont++;
    } while (atual != lista);

    media = soma/cont;
    printf("\nSoma: %d, Media: %.2f\n", soma, media);
    
}

void concatenar(Lista **lista1, Lista **lista2){
    if (*lista1 == NULL)
    {
        *lista1 = *lista2;
    }
    else if (*lista2 != NULL)
    {
        Lista *atual1 = *lista1;
        while (atual1->prox != *lista1)
        {
            atual1 = atual1->prox;
        }

        Lista *atual2 = *lista2;
        while (atual2->prox != *lista2)
        {
            atual2 = atual2->prox;
        }

        atual1->prox = *lista2;
        atual2->prox = *lista1;

        printf("\nLista concatenada: ");
        printar(*lista1);
    }
}