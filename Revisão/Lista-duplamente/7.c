#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    struct Lista *prox;
    struct Lista *ante;
    int num;
} Lista;

void *iniciar()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    no->ante = iniciar();
    no->prox = iniciar();

    if (*lista == NULL)
    {
        *lista = no;
    }
    else
    {
        Lista *atual = *lista;
        while (atual != NULL && atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = no;
        no->ante = atual;
    }
}

void criar_lista(Lista **lista)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        adicionar_elemento(lista, num);
    }
    while (getchar() != '\n')
        ;
}

Lista *percorrer(Lista **lista)
{
    Lista *atual = *lista;
    if (atual == NULL)
    {
        exit(-1);
    }
    else
    {
        while (atual != NULL && atual->prox != NULL)
        {
            atual = atual->prox;
        }
    }
    return atual;
}

int imprimir_normal(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia!\n");
        return 0;
    }

    int cont = 0;
    while (lista != NULL)
    {
        cont++;
        printf(" -> %d ", lista->num);
        lista = lista->prox;
    }
    printf("NULL\n");
    return cont;
}

int imprimir_contrario(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia!\n");
        return 0;
    }

    Lista *ultimo = percorrer(&lista);
    if (ultimo == NULL)
        return 0;

    int cont = 0;
    while (ultimo != NULL)
    {
        cont++;
        printf("NULL ");
        printf(" %d <- ", ultimo->num);
        ultimo = ultimo->ante;
    }
    printf("NULL\n");
    return cont;
}

void remover_repetido(Lista **lista)
{
    Lista *atual = *lista;
    Lista *comp;

    while (atual != NULL)
    {
        comp = atual->prox;
        while (comp != NULL)
        {
            if (comp->num == atual->num)
            {
                Lista *temp = comp;
                if (comp->ante != NULL)
                {
                    comp->ante->prox = comp->prox;
                }
                if (comp->prox != NULL)
                {
                    comp->prox->ante = comp->ante;
                }
                comp = comp->prox;
                free(temp);
            }
            else
            {
                comp = comp->prox;
            }
        }
        atual = atual->prox;
    }
}

void liberar(Lista **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista *atual = *lista;
    Lista *proximo;
    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *lista = iniciar();
    printf("Lista vazia\n");
}

int polindrioma(Lista *lista)
{
    if (lista == NULL)
    {
        exit(-1);
    }
    else
    {
        Lista *fim = percorrer(&lista);
        while (lista != fim && lista->ante != fim)
        {
            if (lista->num != fim->num)
            {
                return 0;
            }
            lista = lista->prox;
            fim = fim->ante;
        }
    }
    return 1;
}

void inverter_intervalo(Lista **lista, int x, int y)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista *atual = *lista;
    Lista *inicio = NULL;
    Lista *fim = NULL;

    while (atual != NULL)
    {
        if (atual->num == x)
        {
            inicio = atual;
        }
        if (atual->num == y)
        {
            fim = atual;
        }

        atual = atual->prox;
    }

    if (inicio == NULL || fim == NULL || inicio == fim)
    {
        return;
    }

    Lista *proximo = inicio->ante;
    Lista *anterior = fim->prox;
    atual = inicio;
    Lista *temp = NULL;

    while (atual != anterior)
    {
        temp = atual->prox;
        atual->prox = atual->ante;
        atual->ante = temp;
        atual = temp;
    }

    if (proximo != NULL)
    {
        proximo->prox = fim;
    }
    else
    {
        *lista = fim;
    }

    if (anterior != NULL)
    {
        anterior->ante = inicio;
    }

    inicio->prox = anterior;
    fim->ante = proximo;
}

int main()
{
    Lista *lista = iniciar();
    printf("Digite os elementos da lista (termina com EOF):\n");
    criar_lista(&lista);

    printf("Lista normal:\n");
    imprimir_normal(lista);

    printf("Lista invertida:\n");
    imprimir_contrario(lista);

    printf("Removendo elementos repetidos:\n");
    remover_repetido(&lista);
    imprimir_normal(lista);

    printf("Verificando se a lista e um palindromo:\n");
    if (polindrioma(lista))
    {
        printf("A lista e um palindromo.\n");
    }
    else
    {
        printf("A lista nao e um palindromo.\n");
    }

    printf("Invertendo intervalo entre dois valores:\n");
    int x, y;
    printf("Digite o valor inicial do intervalo: ");
    scanf("%d", &x);
    printf("Digite o valor final do intervalo: ");
    scanf("%d", &y);
    inverter_intervalo(&lista, x, y);
    imprimir_normal(lista);

    liberar(&lista);
    return 0;
}