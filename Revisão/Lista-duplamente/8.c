#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    struct Lista *ante;
    struct Lista *prox;
} Lista;

Lista *iniciar()
{
    return NULL;
}

int null(Lista *lista)
{
    return (lista == NULL) ? 1 : 0;
}

Lista *percorrer(Lista **lista)
{
    Lista *atual = *lista;
    if (null(atual))
        return NULL;

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

    if (null(*lista))
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

int printar_normal(Lista *lista)
{
    if (null(lista))
    {
        printf("Lista vazia!\n");
        return 0;
    }

    int cont = 0;
    printf("NULL -> ");
    while (lista != NULL)
    {
        cont++;
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
    printf("NULL\n");

    return cont;
}

int imprimir_contrario(Lista *lista)
{
    if (null(lista))
    {
        printf("Lista vazia!\n");
        return 0;
    }

    Lista *atual = percorrer(&lista);
    int cont = 0;

    while (atual != NULL)
    {
        cont++;
        printf("%d <- ", atual->num);
        atual = atual->ante;
    }
    printf("NULL\n");

    return cont;
}

void remover_repetido(Lista **lista)
{
    Lista *atual = *lista;
    while (atual != NULL)
    {
        Lista *comp = atual->prox;
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
    if (null(*lista))
    {
        printf("Lista ja esta vazia.\n");
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
    printf("Lista liberada.\n");
}

void remover_intervalo(Lista **lista, int x, int y)
{
    if (null(*lista))
    {
        printf("Lista vazia\n");
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

    if (inicio == NULL || fim == NULL)
    {
        printf("Intervalo [%d, %d] nao encontrado na lista\n", x, y);
        return;
    }

    Lista *temp = inicio;
    while (temp != fim->prox)
    {
        Lista *proximo = temp->prox;

        if (temp->ante != NULL)
        {
            temp->ante->prox = temp->prox;
        }
        else
        {
            *lista = temp->prox;
        }

        if (temp->prox != NULL)
        {
            temp->prox->ante = temp->ante;
        }

        free(temp);
        temp = proximo;
    }

    printf("Intervalo [%d, %d] removido com sucesso\n", x, y);
}

int main()
{
    Lista *lista = iniciar();
    int opcao, valor, x, y;

    do
    {
        printf("\nMenu:\n");
        printf("1. Criar lista\n");
        printf("2. Adicionar elemento\n");
        printf("3. Imprimir lista\n");
        printf("4. Imprimir lista ao contrario\n");
        printf("5. Remover repetidos\n");
        printf("6. Remover intervalo\n");
        printf("7. Liberar lista\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os elementos da lista (terminar com EOF):\n");
            criar_lista(&lista);
            break;
        case 2:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista, valor);
            break;
        case 3:
            printf("Lista: ");
            printar_normal(lista);
            break;
        case 4:
            printf("Lista ao contrario: ");
            imprimir_contrario(lista);
            break;
        case 5:
            remover_repetido(&lista);
            printf("Repetidos removidos\n");
            break;
        case 6:
            printf("Digite o valor inicial do intervalo: ");
            scanf("%d", &x);
            printf("Digite o valor final do intervalo: ");
            scanf("%d", &y);
            remover_intervalo(&lista, x, y);
            break;
        case 7:
            liberar(&lista);
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
