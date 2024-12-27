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

void inverter(Fila *inicio)
{
    if (!inicio)
    {
        printf("Erro no Malloc\n");
        exit(-1);
    }

    No *atual = inicio->frente;
    No *anterior = NULL;
    No *proximo = NULL;

    while (atual != NULL)
    {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    inicio->atras = inicio->frente;
    inicio->frente = anterior;
}
int main()
{
    Fila *fila = inicializar();
    int opcao, valor;

    do
    {
        printf("\n1. Adicionar elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Printar fila\n");
        printf("4. Inverter fila\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_elemento(&fila, valor);
            break;
        case 2:
            if (!fila_vazia(fila))
            {
                valor = remover(&fila);
                printf("Valor removido: %d\n", valor);
            }
            else
            {
                printf("Fila vazia!\n");
            }
            break;
        case 3:
            printf("Fila: ");
            printar(fila);
            break;
        case 4:
            inverter(fila);
            printf("Fila invertida!\n");
            printar(fila);
            break;
        case 5:
            liberar(&fila);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}