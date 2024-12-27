#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    struct Lista *prox;
    struct Lista *ante;
} Lista;

Lista *iniciar()
{
    return NULL;
}

int is_null(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia!\n");
        return 1;
    }
    return 0;
}

Lista *percorrer(Lista **lista)
{
    Lista *atual = *lista;
    if (is_null(atual) == 1) {
        return NULL;
    }

    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    return atual;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    no->ante = NULL;
    no->prox = NULL;

    if (is_null(*lista) == 1)
    {
        *lista = no;
        return;
    }

    Lista *atual = percorrer(lista);
    atual->prox = no;
    no->ante = atual;
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

int printar(Lista *lista)
{
    if (is_null(lista) == 1) {
        return 0;
    }

    int cont = 0;
    while (lista != NULL)
    {
        cont++;
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
    printf("NULL\n");

    return cont;
}

void liberar(Lista **lista)
{
    if (is_null(*lista) == 1) {
        return;
    }

    Lista *atual = *lista;
    while (atual != NULL)
    {
        Lista *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
    printf("Lista vazia!\n");
}

int primo(int num)
{
    if (num <= 1)
    {
        return 0;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

void inserir_primo(Lista **lista, int valor)
{
    if (is_null(*lista) == 1) {
        return;
    }

    Lista *atual = *lista;
    while (atual != NULL)
    {
        if (primo(atual->num))
        {
            Lista *novo_no = (Lista *)malloc(sizeof(Lista));
            novo_no->num = valor;
            novo_no->prox = atual->prox;
            novo_no->ante = atual;
            if (atual->prox != NULL)
            {
                atual->prox->ante = novo_no;
            }
            atual->prox = novo_no;
            atual = novo_no->prox;
        }
        else
        {
            atual = atual->prox;
        }
    }
}

int main()
{
    Lista *lista = iniciar();
    printf("Digite os elementos da lista (pressione Enter para finalizar):\n");
    criar_lista(&lista);

    printf("Lista original:\n");
    printar(lista);
    printf("\n");

    int valor;
    printf("Digite o valor a ser inserido apos os numeros primos:\n");
    scanf("%d", &valor);

    inserir_primo(&lista, valor);

    printf("Lista apos inserção:\n");
    printar(lista);
    printf("\n");

    liberar(&lista);

    return 0;
}
