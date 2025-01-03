#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    struct Lista *prox;
} Lista;

void add(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    if (*lista == NULL)
    {
        *lista = no;
        no->prox = *lista;
    }
    else
    {
        Lista *atual = *lista;
        while (atual->prox != *lista)
        {
            atual = atual->prox;
        }
        atual->prox = no;
        no->prox = *lista;
    }
}

void criar(Lista **lista)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        add(lista, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Lista *lista)
{
    if (lista == NULL)
    {
        return;
    }
    Lista *inicio = lista;
    do
    {
        printf("%d -> ", lista->num);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");
}

void remover(Lista **lista, int num)
{
    if (*lista == NULL)
    {
        return;
    }
    Lista *atual = *lista;
    Lista *ante = NULL;
    do
    {
        if (atual->num == num)
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

int primo(int n)
{
    if (n < 2)
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void criar_lista_primos(Lista **lista, int tamanho)
{
    liberar(lista); // Clear the existing list
    int num = 2;
    int cont = 0;

    while (cont < tamanho)
    {
        if (primo(num))
        {
            add(lista, num);
            cont++;
        }
        num++;
    }
}

int main()
{
    Lista *lista = NULL;
    int opcao, valor, tamanho;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Listar elementos\n");
        printf("3. Remover elemento\n");
        printf("4. Criar lista de primos\n");
        printf("5. Liberar lista\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Clear input buffer

        switch (opcao)
        {
        case 1:
            printf("Digite um valor para adicionar: ");
            scanf("%d", &valor);
            while (getchar() != '\n'); // Clear input buffer
            add(&lista, valor);
            break;
        case 2:
            listar(lista);
            break;
        case 3:
            printf("Digite um valor para remover: ");
            scanf("%d", &valor);
            while (getchar() != '\n'); // Clear input buffer
            remover(&lista, valor);
            break;
        case 4:
            printf("Digite o tamanho da lista de primos: ");
            scanf("%d", &tamanho);
            while (getchar() != '\n'); // Clear input buffer
            criar_lista_primos(&lista, tamanho);
            break;
        case 5:
            liberar(&lista);
            printf("Lista liberada.\n");
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
