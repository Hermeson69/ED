#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    struct Lista *prox;
    struct Lista *ante;
    int num;
} Lista;

void *inicio()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    no->ante = inicio();
    no->prox = inicio();

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

void inverter_intervalo(Lista **lista, int x, int y) {
    if (*lista == NULL) {
        return;
    }

    Lista *inicio = NULL, *fim = NULL, *atual = *lista;

    // Encontrar os nós correspondentes a x e y
    while (atual != NULL) {
        if (atual->num == x) {
            inicio = atual;
        }
        if (atual->num == y) {
            fim = atual;
        }
        atual = atual->prox;
    }

    // Verificar se ambos os nós foram encontrados
    if (inicio == NULL || fim == NULL) {
        return;
    }

    // Inverter os nós entre x e y
    Lista *prev = inicio->ante;
    Lista *next = fim->prox;
    atual = inicio;
    Lista *temp = NULL;

    while (atual != next) {
        temp = atual->prox;
        atual->prox = atual->ante;
        atual->ante = temp;
        atual = temp;
    }

    // Ajustar os ponteiros
    if (prev != NULL) {
        prev->prox = fim;
    } else {
        *lista = fim;
    }
    inicio->prox = next;
    if (next != NULL) {
        next->ante = inicio;
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
            }else{
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
    *lista = inicio();
    printf("Lista vazia\n");
}

int main()
{
    Lista *lista = inicio();
    printf("Digite os elementos da lista (pressione Ctrl+D para terminar):\n");
    criar_lista(&lista);

    printf("Lista na ordem normal:\n");
    imprimir_normal(lista);

    printf("Lista na ordem inversa:\n");
    imprimir_contrario(lista);

    printf("Removendo elementos repetidos...\n");
    remover_repetido(&lista);

    printf("Lista apos remover elementos repetidos:\n");
    imprimir_normal(lista);

    liberar(&lista);

    return 0;
}
