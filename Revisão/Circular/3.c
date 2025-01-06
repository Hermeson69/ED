#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    char nome[100];
    struct Lista *prox;
} Lista;

void add(Lista **lista, char *palavra)
{
    Lista *pala = (Lista *)malloc(sizeof(Lista));
    strcpy(pala->nome, palavra);
    if (*lista == NULL)
    {
        *lista = pala;
        pala->prox = *lista;
    }
    else
    {
        Lista *atual = *lista;
        while (atual->prox != *lista)
        {
            atual = atual->prox;
        }
        atual->prox = pala;
        pala->prox = *lista;
    }
}

void criar(Lista **lista)
{
    char palavra[100];
    while (scanf("%s", palavra) == 1 && strcmp(palavra, "fim") != 0)
    {
        add(lista, palavra);
    }
    getchar();
}

void remover(Lista **lista, char *palavra)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista *atual = *lista;
    Lista *ante = NULL;
    do
    {
        if (strcmp(atual->nome, palavra) == 0)
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
                return;
            }
            else
            {
                ante->prox = atual->prox;
                free(atual);
                return;
            }
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

void listar(Lista *lista)
{
    if (lista == NULL)
    {
        return;
    }
    Lista *inicio = lista;
    do
    {
        printf("%s -> ", lista->nome);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");
}

void inverter(Lista **lista)
{
    if (*lista == NULL || (*lista)->prox == *lista)
    {
        return;
    }

    Lista *ante = NULL;
    Lista *atual = *lista;
    Lista *prox = NULL;
    Lista *inicio = *lista;

    do
    {
        prox = atual->prox;
        atual->prox = ante;
        ante = atual;
        atual = prox;
    } while (atual != inicio);

    inicio->prox = ante;
    *lista = ante;
}

int main()
{
    Lista *lista = NULL;
    int opcao;
    char palavra[100];

    do
    {
        printf("1. Adicionar palavra\n");
        printf("2. Remover palavra\n");
        printf("3. Listar palavras\n");
        printf("4. Liberar lista\n");
        printf("5. Inverter lista\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao)
        {
        case 1:
            printf("Digite a palavra: ");
            scanf("%s", palavra);
            add(&lista, palavra);
            break;
        case 2:
            printf("Digite a palavra a ser removida: ");
            scanf("%s", palavra);
            remover(&lista, palavra);
            break;
        case 3:
            listar(lista);
            break;
        case 4:
            liberar(&lista);
            break;
        case 5:
            inverter(&lista);
            break;
        case 6:
            liberar(&lista);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
