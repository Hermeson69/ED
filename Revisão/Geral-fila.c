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

typedef struct Pilha
{
    int num;
    struct Pilha *prox;
} Pilha;

typedef struct Topo
{
    Pilha *topo;
} Topo;

No *criar_no(int num)
{
    No *no = (No *)malloc(sizeof(No));
    if (!no)
    {
        printf("Erro no Malloc\n");
        return NULL;
    }
    no->num = num;
    no->prox = NULL;
    return no;
}

Fila *inicializar()
{
    Fila *inicio = (Fila *)malloc(sizeof(Fila));
    if (!inicio)
    {
        printf("Erro no Malloc\n");
        return NULL;
    }
    inicio->frente = inicio->atras = NULL;
    return inicio;
}

void adicionar_fila(Fila **inicio, int num)
{
    No *no = criar_no(num);
    if (!no) return;
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

void criar_fila(Fila **inicio){
    int num;
    while (scanf("%d", &num) == 1)
    {
        adicionar_fila(inicio, num);
    }
    while (getchar() != '\n')
        ;
}

int remove_fila(Fila **inicio)
{
    Fila *atual = *inicio;
    if (atual->frente == NULL)
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

int fila_vazia(Fila *fila)
{
    return fila->frente == NULL;
}

int pilha_vazia(Pilha *pilha)
{
    return (pilha == NULL);
}

void inicializar_pilha(Pilha **pilha)
{
    *pilha = NULL;
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
        remove_fila(inicio);
    }
    free(*inicio);
    *inicio = NULL;
}

//////////////////PILHA/////////////////////////////////////
void adicionar(Topo *topo, int valor)
{
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = topo->topo;
    topo->topo = no;
}

void criar_pilha(Topo *topo)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        adicionar(topo, num);
    }
    while (getchar() != '\n')
        ;
}

int pop(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return -1;
    }
    Pilha *atual = topo->topo;
    int valor = atual->num;
    topo->topo = atual->prox;
    free(atual);
    return valor;
}

//////////////////////////////////////////////////////////////

void impares_pares(Fila *inicio)
{
    Fila *pares = inicializar();
    Fila *impares = inicializar();
    while (!fila_vazia(inicio))
    {
        int num = remove_fila(&inicio);
        if (num % 2 == 0)
        {
            adicionar_fila(&pares, num);
        }
        else
        {
            adicionar_fila(&impares, num);
        }
    }
    printf("Pares: ");
    printar(pares);
    printf("Impares: ");
    printar(impares);
    liberar(&pares);
    liberar(&impares);
}

void soma(Fila *fila)
{
    int soma = 0;
    No *atual = fila->frente;
    while (atual != NULL)
    {
        soma += atual->num;
        atual = atual->prox;
    }
    printf("Soma: %d\n", soma);
}

void inverter_fila_com_pilha(Fila **inicio, Topo *topo)
{
    if (*inicio == NULL)
    {
        return;
    }
    while (!fila_vazia(*inicio))
    {
        int n = remove_fila(inicio);
        adicionar(topo, n);
    }

    while (!pilha_vazia(topo->topo))
    {
        int x = pop(topo);
        adicionar_fila(inicio, x);
    }
}


int ordem(Fila **fila){
    if (*fila == NULL || (*fila)->frente == NULL)
    {
        return 1;
    }
    No *atual = (*fila)->frente;
    while (atual->prox != NULL)
    {
        if (atual->num > atual->prox->num)
        {
            return 0;
        }
        atual = atual->prox;
    }
    return 1;
}

Fila *concatenar_filas(Fila *fila1, Fila *fila2) {
    Fila *nova_fila = inicializar();
    No *atual = fila1->frente;

    while (atual != NULL) {
        adicionar_fila(&nova_fila, atual->num);
        atual = atual->prox;
    }

    atual = fila2->frente;
    while (atual != NULL) {
        adicionar_fila(&nova_fila, atual->num);
        atual = atual->prox;
    }

    return nova_fila;
}


void nona(Fila **inicio, int n) {
    No *atual = (*inicio)->frente;
    Fila *FilaSoma = iniciar();
    No *temp = atual;
    int soma = 0;
    int count = 0;

    while (temp != NULL && count < n) {
        soma += temp->num;
        temp = temp->prox;
        count++;
    }

    if (count == n) {
        add(&FilaSoma, soma);
    }

    while (temp != NULL) {
        soma += temp->num - atual->num;
        add(&FilaSoma, soma);
        atual = atual->prox;
        temp = temp->prox;
    }

    printar(FilaSoma);
}



int main()
{
    Fila *fila = inicializar();
    Topo topo;
    inicializar_pilha(&topo.topo);

    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar na fila\n");
        printf("2. Remover da fila\n");
        printf("3. Imprimir fila\n");
        printf("4. Verificar se a fila esta vazia\n");
        printf("5. Separar impares e pares\n");
        printf("6. Somar elementos da fila\n");
        printf("7. Inverter fila com pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um valor: ");
            criar_fila(&fila);
            break;
        case 2:
            if (!fila_vazia(fila))
            {
                valor = remove_fila(&fila);
                printf("Valor removido: %d\n", valor);
            }
            else
            {
                printf("Fila vazia\n");
            }
            break;
        case 3:
            printar(fila);
            break;
        case 4:
            if (fila_vazia(fila))
            {
                printf("Fila esta vazia\n");
            }
            else
            {
                printf("Fila nao esta vazia\n");
            }
            break;
        case 5:
            impares_pares(fila);
            break;
        case 6:
            soma(fila);
            break;
        case 7:
            inverter_fila_com_pilha(&fila, &topo);
            break;
        case 0:
            liberar(&fila);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}