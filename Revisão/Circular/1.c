#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    int posicao;
    struct Lista *prox;
} Lista;

void *iniciar()
{
    return NULL;
}

void adicionar(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    if (*lista == NULL)
    {
        no->posicao = 0;
        *lista = no;
        no->prox = *lista;
    }
    else
    {
        int cont = 1;
        Lista *atual = *lista;
        while (atual->prox != *lista)
        {
            cont++;
            atual = atual->prox;
        }
        no->posicao = cont;
        atual->prox = no;
        no->prox = *lista;
    }
}

void criar(Lista **lista)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        adicionar(lista, num);
    }
    while (getchar() != '\n')
        ;
}

int listar(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista Vazia\n");
        return 0;
    }

    int cont = 0;
    Lista *inicio = lista;
    do
    {
        cont++;
        printf("%d: %d -> ", lista->posicao, lista->num);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");

    return cont;
}

void remover(Lista **lista, int valor)
{
    if (*lista == NULL)
    {
        printf("Lista Vazia\n");
        return;
    }
    Lista *atual = *lista;
    Lista *ante = NULL;

    do
    {
        if (atual->num == valor)
        {
            if (ante == NULL)
            {
                Lista *temp = *lista;
                if (atual->prox == *lista)
                {
                    *lista = NULL;
                }
                else
                {
                    Lista *ultimo = *lista;
                    while (ultimo->prox != *lista)
                    {
                        ultimo = ultimo->prox;
                    }
                    *lista = atual->prox;
                    ultimo->prox = *lista;
                }
                free(temp);
            }
            else
            {
                ante->prox = atual->prox;
                free(atual);
            }
            return;
        }
        ante = atual;
        atual = atual->prox;
    } while (atual != *lista);
}

void liberar(Lista **lista)
{
    if (*lista == NULL)
    {
        return;
    }
    Lista *atual = *lista;
    Lista *proximo = NULL;
    do
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != *lista);

    *lista = NULL;
}

int pulo(Lista **lista, int n)
{
    if (*lista == NULL)
    {
        printf("Lista Vazia\n");
        return -1;
    }

    Lista *atual = *lista;
    Lista *ante = NULL;

    while ((*lista)->prox != *lista)
    {
        for (int i = 1; i <= n; i++)
        {
            ante = atual;
            atual = atual->prox;
        }
        remover(lista, atual->num);
        atual = ante->prox;
    }

    int last_position = (*lista)->num;
    printf("Last position is: %d\n", last_position);
    return last_position;
}

int main()
{
    Lista *lista = iniciar();
    int opcao, valor, n;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Listar elementos\n");
        printf("3. Remover elemento\n");
        printf("4. Liberar lista\n");
        printf("5. Pulo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um valor para adicionar: ");
            criar(&lista);
            break;
        case 2:
            listar(lista);
            break;
        case 3:
            printf("Digite um valor para remover: ");
            scanf("%d", &valor);
            remover(&lista, valor);
            break;
        case 4:
            liberar(&lista);
            printf("Lista liberada\n");
            break;
        case 5:
            printf("Digite o valor de n para o pulo: ");
            scanf("%d", &n);
            pulo(&lista, n);
            break;
        case 0:
            liberar(&lista);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}