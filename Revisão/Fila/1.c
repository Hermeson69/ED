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
        exit(1);
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
        return;
    }
    atual->atras->prox = no;
    atual->atras = no;
}

int remover(Fila **inicio)
{
    Fila *atual = *inicio;
    if (atual->atras == NULL)
    {
        printf("Fila vazia\n");
        exit(-1);
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
    printf("NULL");
    printf("\n");
}

void liberar (Fila **inicio){
    while (!fila_vazia(*inicio))
    {
        remover(inicio);
    }

    free(*inicio);
    inicializar();
}

void impares_pares(Fila *inicio){
    Fila *pares = inicializar();
    Fila *impares = inicializar();

    while(!fila_vazia(inicio)){
        int valor = remover(&inicio);
        if (valor % 2 == 0)
        {
            adicionar_elemento(&pares, valor);
        }else{
            adicionar_elemento(&impares, valor);
        }
        
    }

    printar(impares);
    printar(pares);
}
int main()
{
    Fila *fila = inicializar();
    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Verificar se a fila esta vazia\n");
        printf("4. Printar fila\n");
        printf("5. Separar impares e pares\n");
        printf("6. Liberar fila\n");
        printf("0. Sair\n");
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
                printf("A fila esta vazia\n");
            }
            else
            {
                printf("A fila nao esta vazia\n");
            }
            break;
        case 4:
            printf("Fila: ");
            printar(fila);
            break;
        case 5:
            impares_pares(fila);
            break;
        case 6:
            liberar(&fila);
            printf("Fila liberada\n");
            break;
        case 0:
            liberar(&fila);
            printf("Saindo...\n");
            break;
        default:
            printf("Opção invalida\n");
        }
    } while (opcao != 0);

    return 0;
}
