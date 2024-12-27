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

int sim_nao(Fila *inicio)
{
    if (fila_vazia(inicio))
    {
        printf("Fila vazia\n");
        exit(1);
    }

    No *atual = inicio->frente;

    int resultado = 1;

    while (atual->prox != NULL)
    {
        if (atual->num > atual->prox->num)
        {
            resultado = 0;
        }
        atual = atual->prox;
    }

    return resultado;
}

int main()
{
    Fila *fila = inicializar();
    int opcao, valor;

    do
    {
        printf("1. Adicionar elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Verificar se a fila esta vazia\n");
        printf("4. Printar fila\n");
        printf("5. Liberar fila\n");
        printf("6. Sair\n");
        printf("7. Verificar condicao sim_nao\n");
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
                printf("Elemento removido: %d\n", valor);
            }
            else
            {
                printf("Fila vazia\n");
            }
            break;
        case 3:
            if (fila_vazia(fila))
            {
                printf("Fila está vazia\n");
            }
            else
            {
                printf("Fila não está vazia\n");
            }
            break;
        case 4:
            printar(fila);
            break;
        case 5:
            liberar(&fila);
            printf("Fila liberada\n");
            break;
        case 6:
            liberar(&fila);
            printf("Saindo...\n");
            break;
        case 7:
            if (sim_nao(fila))
            {
                printf("Verdadeiro\n");
            }
            else
            {
                printf("Falso\n");
            }
            break;
            break;
        default:
            printf("Opção inválida\n");
        }
    } while (opcao != 6);

    return 0;
}