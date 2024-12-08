#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int num;
    struct No *prox;
} No;

typedef struct fila
{
    No *frente;
    No *atras;
} fila;

No *criar_no(int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (!novo)
    {
        printf("Erro no Malloc\n");
        exit(1);
    }
    novo->num = valor;
    novo->prox = NULL;
    return novo;
}

fila *inicializar()
{
    fila *inicio = (fila *)malloc(sizeof(fila));
    if (!inicio)
    {
        printf("Erro Malloc\n");
        exit(1);
    }

    inicio->frente = inicio->atras = NULL;
    return inicio;
}

void adicionar_elemento(fila **inicio, int valor)
{
    No *novo = criar_no(valor);

    fila *atual = *inicio;

    if (atual->atras == NULL)
    {
        atual->frente = atual->atras = novo;
        return;
    }

    atual->atras->prox = novo;
    atual->atras = novo;
}

int remover(fila **inicio)
{
    fila *atual = *inicio;
    if (atual->frente == NULL)
    {
        printf("Fila Vazia\n");
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

int fila_vazia(fila *inicio)
{
    return inicio->frente == NULL;
}

void printar(fila *inicio)
{
    No *temp = inicio->frente;
    while (temp)
    {
        printf("%d ", temp->num);
        temp = temp->prox;
    }
    printf("\n");
}

void liberar(fila **inicio)
{
    while (!fila_vazia(*inicio))
    {
        remover(inicio);
    }
    free(*inicio);
    inicializar();
}

void menu(){
    fila* inicio = inicializar();
    int op, valor;
    do
    {
        printf("\nMenu:\n");
        printf("1. Enfileirar\n");
        printf("2. Desenfileirar\n");
        printf("3. Imprimir fila\n");
        printf("4. Sair\n");
        printf("Escolha uma op: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Digite um valor para enfileirar: ");
                scanf("%d", &valor);
                adicionar_elemento(&inicio, valor);
                break;
            case 2:
                valor = remover(&inicio);
                if (valor != -1) {
                    printf("Desenfileirado: %d\n", valor);
                }
                break;
            case 3:
                printf("Fila: ");
                printar(inicio);
                break;
            case 4:
                liberar(&inicio);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (op != 4);
}
     

int main() {
    menu();
    return 0;
}