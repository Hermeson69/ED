#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LISTA
{
    int num;
    struct LISTA *prox;
    struct LISTA *ant;
} LISTA;

void *iniciar()
{
    return NULL;
}

void adicionar_elemento(LISTA **lista, int valor)
{
    LISTA *no = (LISTA *)malloc(sizeof(LISTA));
    no->num = valor;
    no->prox = NULL;
    no->ant = NULL;

    if (*lista == NULL)
    {
        *lista = no;
    }
    else
    {
        LISTA *atual = *lista;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = no;
        no->ant = atual;
    }
}

int imprimir_normal(LISTA *lista)
{
    int cont = 0;
    if (lista == NULL)
    {
        printf("Nem um elemento na lista!!\n");
        exit(1);
    }

    LISTA *atual = lista;
    do
    {
        cont++;
        printf(" %d -> ", atual->num);
        atual = atual->prox;
    } while (atual != NULL);
    printf("NULL \n");
    return cont;
}

int imprimir_contrario(LISTA *lista)
{
    int cont = 0;
    if (lista == NULL)
    {
        printf("Nem um elemento na lista!!\n");
        exit(1);
    }

    LISTA *atual = lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    while (atual != NULL)
    {
        cont++;
        printf(" %d <-  ", atual->num);
        atual = atual->ant;
    }
    printf("NULL \n");
    return cont;
}

void liberar(LISTA **lista)
{
    if (*lista == NULL)
    {
        exit(-1);
    }

    LISTA *atual = *lista;
    LISTA *proximo;
    do
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != NULL);
    free(*lista);
    *lista = iniciar();
    printf("Lista vazia\n");
}

void liberar_segundo_maior(LISTA **lista)
{
    LISTA *atual = *lista;
    if (atual == NULL || atual->prox == NULL)
    {
        printf("Lista nao possui elementos suficientes!\n");
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
            if (atual->ant != NULL)
            {
                atual->ant->prox = atual->prox;
            }
            else
            {
                *lista = atual->prox;
            }

            if (atual->prox != NULL)
            {
                atual->prox->ant = atual->ant;
            }
            free(atual);
            printf("Elemento %d removido.\n", segundo);
            return;
        }
        atual = atual->prox;
    }
    printf("Segundo maior elemento nao encontrado.\n");
}
void inserir_valores(LISTA **lista) {
    int valor;
    printf("Digite um valor (ou -1 para parar): ");
    while (scanf("%d", &valor) && valor != -1) {
        adicionar_elemento(lista, valor);
        printf("Digite um valor (ou -1 para parar): ");
    }
}

int main() {
    LISTA *lista = iniciar();
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir valores\n");
        printf("2. Imprimir lista\n");
        printf("3. Imprimir lista ao contrario\n");
        printf("4. Liberar segundo maior elemento\n");
        printf("5. Liberar lista\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserir_valores(&lista);
                break;
            case 2:
                imprimir_normal(lista);
                break;
            case 3:
                imprimir_contrario(lista);
                break;
            case 4:
                liberar_segundo_maior(&lista);
                break;
            case 5:
                liberar(&lista);
                break;
            case 6:
                liberar(&lista);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}