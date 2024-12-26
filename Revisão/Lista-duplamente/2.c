#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    struct Lista *prox;
    struct Lista *ante;
} Lista;

Lista *inicio()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    no->ante = NULL;
    no->prox = NULL;

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

void percorrer_ao_contrario(Lista **lista)
{
    if (*lista == NULL)
    {
        printf("Nem um elemento na lista!!\n");
        exit(1);
    }

    Lista *atual = *lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }

    *lista = atual;
}

int imprimir_normal(Lista *lista)
{
    int cont = 0;
    if (lista == NULL)
    {
        printf("Nao tem lista!\n");
        exit(1);
    }
    else
    {
        Lista *atual = lista;
        while (atual != NULL)
        {
            cont++;
            printf(" -> %d ", atual->num);
            atual = atual->prox;
        }
        printf("NULL \n");
        return cont;
    }
}

int imprimir_contrario(Lista *lista)
{
    int cont = 0;
    percorrer_ao_contrario(&lista);
    while (lista != NULL)
    {
        cont++;
        printf(" %d <-  ", lista->num);
        lista = lista->ante;
    }
    printf("NULL \n");
    return cont;
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

void liberar_segundo_maior(Lista **lista)
{
    Lista *atual = *lista;
    if (atual == NULL || atual->prox == NULL)
    {
        printf("Lista não possue elementos!\n");
        return;
    }

    int maior = atual->num;
    atual = atual->prox;
    while (atual != NULL)
    {
        if (atual->num > maior)
        {
            maior = atual->num;
        }
        atual = atual->prox;
    }

    int segundo = -1;
    atual = *lista;
    while (atual != NULL)
    {
        if (atual->num != maior && atual->num > segundo)
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
            free(atual);
            break;
        }
        atual = atual->prox;
    }
}

void mesclagem(Lista **lista1, Lista **lista2)
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

    Lista *atual1 = *lista1;
    Lista *atual2 = *lista2;
    Lista *prox1, *prox2;

    while (atual1 != NULL && atual2 != NULL)
    {
        prox1 = atual1->prox;
        prox2 = atual2->prox;

        atual1->prox = atual2;
        atual2->ante = atual1;

        if (prox1 != NULL)
        {
            atual2->prox = prox1;
            prox1->ante = atual2;
        }

        atual1 = prox1;
        atual2 = prox2;
    }

    *lista2 = NULL;
}

int main()
{
    Lista *lista = inicio();
    int opcao, valor;
    Lista *lista2 = inicio();

    do
    {
        printf("Menu:\n");
        printf("1. Criar lista 1\n");
        printf("2. Criar lista 2\n");
        printf("3. Adicionar elemento na lista 1\n");
        printf("4. Adicionar elemento na lista 2\n");
        printf("5. Imprimir lista 1\n");
        printf("6. Imprimir lista 2\n");
        printf("7. Imprimir lista 1 ao contrario\n");
        printf("8. Imprimir lista 2 ao contrario\n");
        printf("9. Liberar segundo maior elemento da lista 1\n");
        printf("10. Liberar segundo maior elemento da lista 2\n");
        printf("11. Liberar lista 1\n");
        printf("12. Liberar lista 2\n");
        printf("13. Mesclar listas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar_lista(&lista);
            break;
        case 2:
            criar_lista(&lista2);
            break;
        case 3:
            printf("Digite o valor a ser adicionado na lista 1: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista, valor);
            break;
        case 4:
            printf("Digite o valor a ser adicionado na lista 2: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista2, valor);
            break;
        case 5:
            imprimir_normal(lista);
            break;
        case 6:
            imprimir_normal(lista2);
            break;
        case 7:
            imprimir_contrario(lista);
            break;
        case 8:
            imprimir_contrario(lista2);
            break;
        case 9:
            liberar_segundo_maior(&lista);
            break;
        case 10:
            liberar_segundo_maior(&lista2);
            break;
        case 11:
            liberar(&lista);
            break;
        case 12:
            liberar(&lista2);
            break;
        case 13:
            mesclagem(&lista, &lista2);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}