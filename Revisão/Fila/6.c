#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    int num;
    struct No *prox;
} No;

typedef struct Fila
{
    No *frente;
    No *atras;
} Fila;

No *criar_no(int valor)
{
    No *no = (No *)malloc(sizeof(No));
    if (!no)
    {
        printf("Erro no Malloc\n");
        exit(-1);
    }
    no->num = valor;
    no->prox = NULL;
    return no;
}

Fila *inicializar()
{
    Fila *inicio = (Fila *)malloc(sizeof(Fila));
    if (!inicio)
    {
        printf("Erro no Malloc\n");
        exit(-1);
    }
    inicio->frente = inicio->atras = NULL;
    return inicio;
}

void adicionar_elemento(Fila **inicio, int valor)
{
    No *no = criar_no(valor);
    Fila *atual = *inicio;
    if (atual->atras == NULL)
    {
        atual->frente = atual->atras = no;
    }
    else
    {
        atual->atras->prox = no;
        atual->atras = no;
    }
}

int remover(Fila **inicio)
{
    Fila *atual = *inicio;
    if (atual->frente == NULL)
    {
        printf("VAZIA\n");
        exit(1);
    }

    No *temp = atual->frente;
    int temp_valor = temp->num;
    atual->frente = atual->frente->prox;
    if (atual->frente == NULL)
    {
        atual->atras = NULL;
    }
    free(temp);
    return temp_valor;
}

int fila_vazia(Fila *inicio)
{
    return inicio->frente == NULL;
}

void printar(Fila *inicio)
{
    No *temp = inicio->frente;
    while (temp)
    {
        printf("%d -> ", temp->num);
        temp = temp->prox;
    }
    printf("NULL\n");
}

void liberar(Fila **inicio)
{
    while (!fila_vazia(*inicio))
    {
        remover(inicio);
    }

    free(*inicio);
    *inicio = inicializar();
}


void duas_filas(Fila **fila1, Fila **fila2)
{
    if (*fila1 == NULL)
    {
        *fila1 = *fila2;
        *fila2 = NULL;
        return;
    }

    if (*fila2 == NULL)
    {
        return;
    }

    Fila *aux1 = *fila1;
    Fila *aux2 = *fila2;

    if (aux1->atras != NULL)
    {
        aux1->atras->prox = aux2->frente;
    }
    else
    {
        aux1->frente = aux2->frente;
    }

    aux1->atras = aux2->atras;

    free(aux2);
    aux2 = NULL;

    return;
}
int main()
{
    Fila *fila1 = inicializar();
    Fila *fila2 = inicializar();
    int escolha, valor;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento na Fila 1\n");
        printf("2. Adicionar elemento na Fila 2\n");
        printf("3. Remover elemento da Fila 1\n");
        printf("4. Remover elemento da Fila 2\n");
        printf("5. Combinar Filas\n");
        printf("6. Printar Fila 1\n");
        printf("7. Printar Fila 2\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("Digite o valor a ser adicionado na Fila 1: ");
            scanf("%d", &valor);
            adicionar_elemento(&fila1, valor);
            break;
        case 2:
            printf("Digite o valor a ser adicionado na Fila 2: ");
            scanf("%d", &valor);
            adicionar_elemento(&fila2, valor);
            break;
        case 3:
            if (!fila_vazia(fila1))
            {
                valor = remover(&fila1);
                printf("Elemento removido da Fila 1: %d\n", valor);
            }
            else
            {
                printf("Fila 1 esta vazia\n");
            }
            break;
        case 4:
            if (!fila_vazia(fila2))
            {
                valor = remover(&fila2);
                printf("Elemento removido da Fila 2: %d\n", valor);
            }
            else
            {
                printf("Fila 2 esta vazia\n");
            }
            break;
        case 5:
            duas_filas(&fila1, &fila2);
            printf("Filas combinadas\n");
            break;
        case 6:
            printf("Fila 1:\n");
            printar(fila1);
            break;
        case 7:
            printf("Fila 2:\n");
            printar(fila2);
            break;
        case 8:
            liberar(&fila1);
            liberar(&fila2);
            printf("Saindo...\n");
            exit(0);
        default:
            printf("Opcao invalida\n");
        }
    }

    return 0;
}
