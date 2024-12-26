#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    struct Lista *ante;
    struct Lista *prox;
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
        while (atual->prox != NULL)
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

Lista *percorrer(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Nenhum elemento na lista!\n");
        return NULL;
    }

    Lista *atual = lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
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

    Lista *ultimo = percorrer(lista);
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

void remover_buscado(Lista **lista, int valor)
{
    if (*lista == NULL)
    {
        exit(-1);
    }
    else
    {
        Lista *atual = *lista;
        while (atual != NULL)
        {
            if (atual->num == valor)
            {
                if (atual->ante != NULL)
                {
                    atual->ante->prox = atual->prox;
                }
                else
                {
                    *lista = atual->prox;
                }
                if (atual->prox != NULL)
                {
                    atual->prox->ante = atual->ante;
                }
                Lista *temp;
                temp = atual;
                atual = atual->prox;
                free(temp);
            }
            else
            {
                atual = atual->prox;
            }
        }
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
    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Imprimir lista (normal)\n");
        printf("3. Imprimir lista (contrario)\n");
        printf("4. Remover elemento\n");
        printf("5. Liberar lista\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar_lista(&lista);
            break;
        case 2:
            imprimir_normal(lista);
            break;
        case 3:
            imprimir_contrario(lista);
            break;
        case 4:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            remover_buscado(&lista, valor);
            break;
        case 5:
            liberar(&lista);
            break;
        case 0:
            liberar(&lista);
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}