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
    int temp_num = temp->num;
    atual->frente = atual->frente->prox;
    if (atual->frente == NULL)
    {
        atual->atras = NULL;
    }
    free(temp);
    return temp_num;
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

void filas_intersecao(Fila **fila1, Fila **fila2){
    Fila *fila_intersecao = inicializar();
    No *temp1 = (*fila1)->frente;

    while (temp1 != NULL)
    {
       No *temp2 = (*fila2)->frente;
       while (temp2 != NULL)
       {
        if (temp1->num == temp2->num)
        {
            adicionar_elemento(&fila_intersecao, temp1->num);
        }
        temp2 = temp2->prox;
       }
        temp1 = temp1->prox;
    }
    
    printar(fila_intersecao);
}
int main()
{
    Fila *fila1 = inicializar();
    Fila *fila2 = inicializar();
    int opcao, valor;

    while (1)
    {
        printf("1. Adicionar elemento na fila 1\n");
        printf("2. Adicionar elemento na fila 2\n");
        printf("3. Remover elemento da fila 1\n");
        printf("4. Remover elemento da fila 2\n");
        printf("5. Verificar se a fila 1 esta vazia\n");
        printf("6. Verificar se a fila 2 esta vazia\n");
        printf("7. Imprimir fila 1\n");
        printf("8. Imprimir fila 2\n");
        printf("9. Intersecao das filas\n");
        printf("10. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser adicionado na fila 1: ");
            scanf("%d", &valor);
            adicionar_elemento(&fila1, valor);
            break;
        case 2:
            printf("Digite o valor a ser adicionado na fila 2: ");
            scanf("%d", &valor);
            adicionar_elemento(&fila2, valor);
            break;
        case 3:
            if (!fila_vazia(fila1))
            {
                valor = remover(&fila1);
                printf("Valor removido da fila 1: %d\n", valor);
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
                printf("Valor removido da fila 2: %d\n", valor);
            }
            else
            {
                printf("Fila 2 esta vazia\n");
            }
            break;
        case 5:
            if (fila_vazia(fila1))
            {
                printf("Fila 1 esta vazia\n");
            }
            else
            {
                printf("Fila 1 nao esta vazia\n");
            }
            break;
        case 6:
            if (fila_vazia(fila2))
            {
                printf("Fila 2 esta vazia\n");
            }
            else
            {
                printf("Fila 2 nao esta vazia\n");
            }
            break;
        case 7:
            printf("Fila 1: ");
            printar(fila1);
            break;
        case 8:
            printf("Fila 2: ");
            printar(fila2);
            break;
        case 9:
            printf("Intersecao das filas: ");
            filas_intersecao(&fila1, &fila2);
            break;
        case 10:
            liberar(&fila1);
            liberar(&fila2);
            exit(0);
        default:
            printf("Opcao invalida\n");
        }
    }

    return 0;
}