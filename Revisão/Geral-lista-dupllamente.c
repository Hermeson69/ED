#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lsd
{
    int num;
    struct Lsd *prox;
    struct Lsd *anter;
} Lsd;

void add(Lsd **lista, int num)
{
    Lsd *no = (Lsd *)malloc(sizeof(Lsd));
    no->num = num;
    no->anter = NULL;
    no->prox = NULL;
    if (*lista == NULL)
    {
        *lista = no;
    }
    Lsd *atual = *lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    atual->prox = no;
    no->anter = atual;
}

void criar(Lsd **lista)
{
    int num;
    while (scanf("%d", num) == 1)
    {
        add(lista, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Lsd *lista)
{
    if (lista == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    while (lista != NULL)
    {
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
}
// PRIMEIRA
void liberar_segundo_maior(Lsd **lista)
{
    Lsd *atual = *lista;
    if (atual == NULL)
    {
        return;
    }

    int maior = atual->num;
    int segundo = atual->num;
    atual = atual->prox;

    while (atual != NULL)
    {
        if (atual->num > maior)
        {
            segundo = maior;
            maior = atual->num;
        }
        else if (atual->num > segundo && atual->num < maior)
        {
            segundo = atual->num;
        }
        atual = atual->prox;
    }

    atual = *lista;
    while (atual != NULL)
    {
        if (atual->num == segundo)
        {
            if (atual->anter != NULL)
            {
                atual->anter->prox = atual->prox;
            }
            else
            {
                *lista = atual->prox;
            }
            if (atual->prox != NULL)
            {
                atual->prox->anter = atual->anter;
            }
            free(atual);
            printf("%d removido \n", segundo);
            return;
        }
        atual = atual->prox;
    }
}
// SEGUNDA
void mesclagem(Lsd **lista1, Lsd **lista2)
{
    if (*lista1 == NULL)
    {
        *lista1 = *lista2;
        *lista2 = NULL;
        return;
    }
    if (*lista2 == NULL)
    {
        exit(-1);
    }

    Lsd *atual1 = *lista1;
    Lsd *atual2 = *lista2;
    Lsd *prox1, *prox2;

    while (atual1 != NULL || atual2 != NULL)
    {
        prox1 = atual1->prox;
        prox2 = atual2->prox;

        atual1->prox = atual2;
        atual2->prox = atual1;

        if (prox1 != NULL)
        {
            atual2->prox = prox1;
            prox1->anter = atual2;
        }
        atual1 = prox1;
        atual2 = prox2;
    }
    *lista2 = NULL;
}
// TERCEIRA
void remover_buscado(Lsd **lista, int num)
{
    Lsd *atual = *lista;
    if (atual == NULL)
    {
        return;
    }

    while (atual != NULL)
    {
        if (atual->num == num)
        {
            if (atual->anter != NULL)
            {
                atual->anter->prox = atual->prox;
            }
            else
            {
                *lista = atual->prox;
            }
            if (atual->prox != NULL)
            {
                atual->prox->anter = atual->anter;
            }
            Lsd *temp;
            temp = atual;
            atual = atual->anter;
            free(temp);
        }
        atual = atual->prox;
    }
}
// QUARTA
void remover_todos_os_repetidos(Lsd **lista)
{
    Lsd *atual = *lista;
    Lsd *comparador = NULL;
    while (atual != NULL)
    {
        comparador = atual->prox;
        while (comparador != NULL)
        {
            if (comparador->num == atual->num)
            {
                Lsd *temp = comparador;
                if (comparador->anter != NULL)
                {
                    comparador->anter->prox = comparador->prox;
                }
                else
                {
                    *lista = comparador->prox;
                }
                if (comparador->prox != NULL)
                {
                    comparador->prox->anter = comparador->anter;
                }
                comparador = comparador->prox;
                free(temp);
            }
            comparador = comparador->prox;
        }
        atual = atual->prox;
    }
}
// QUINTA
void rotacionar(Lsd **lista, int n)
{
    Lsd *atual = *lista;
    int cont = 1;
    while (atual != NULL)
    {
        cont++;
        atual = atual->prox;
    }

    atual->prox = *lista;
    (*lista)->anter = atual;
    n = n % cont;

    for (int i = 1; i < cont - n; i++)
    {
        atual = atual->prox;
    }
    *lista = atual->prox;
    (*lista)->anter = NULL;
    atual->prox = NULL;
}
// SEXTA
int polidromia(Lsd *lista)
{
    if (lista == NULL)
    {
        return -1;
    }
    Lsd *fim = lista;
    while (fim->prox != NULL)
    {
        fim = fim->prox;
    }

    while (lista != NULL && lista != fim && lista->anter != fim)
    {
        if (lista->num != fim->num)
        {
            return 0;
        }
        lista = lista->prox;
        fim = fim->anter;
    }
    return 1;
}
// SETIMA

void inverter_intervalo(Lsd **lista, int x, int y)
{
    if (*lista == NULL)
    {
        exit(-1);
    }
    Lsd *atual = *lista;
    Lsd *inicio = NULL;
    Lsd *fim = NULL;

    while (atual != NULL)
    {
        if (atual->num = x)
        {
            inicio = atual;
        }
        if (atual->num = y)
        {
            fim = atual;
        }

        atual = atual->prox;
    }

    if (inicio == NULL || fim == NULL || inicio == fim)
    {
        return;
    }

    Lsd *prox = inicio->anter;
    Lsd *anter = fim->prox;
    atual = inicio;
    Lsd *temp = NULL;

    while (atual != NULL)
    {
         temp = atual->prox;
        atual->prox = atual->anter;
        atual->anter = temp;
        atual = temp;
    }
    
    if (prox != NULL)
    {
        prox->prox = fim;
    }else{
        *lista = fim;
    }
    if (anter != NULL)
    {
        anter->anter = inicio;
    }
    
    inicio->prox = anter;
    fim->anter = prox;
}