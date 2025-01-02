#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{int num; struct No*prox}No;
typedef struct Fila{No *frente; No *atras}Fila;

No *criar(int num){
    No *no = (No *)malloc(sizeof(No));
    if (!no)
    {
        printf("Erro Malloc\n");
        exit(-1);
    }
    no->num = num;
    no->prox = NULL;
    return no;
}

Fila *iniciar(){
    Fila *inicio = (Fila *)malloc(sizeof(Fila));
    if (!inicio)
    {
        printf("Erro Malloc\n");
        exit(-1);
    }
    inicio->frente = inicio->atras =  NULL;
    return inicio;
}

void add(Fila **fila, int valor){
    No *no = criar(valor);
    Fila *atual = *fila;
    if(atual->frente == NULL){
        atual->frente = atual->atras = no;
    }else{
        atual->atras->prox = no;
        atual->atras = no;
    }
}


int fila_vazia(Fila *inicio)
{
    return inicio->frente == NULL;
}

void printar(Fila *fila){
    No *temp = fila->frente;
    while (temp)
    {
        printf("%d -> ", temp->num);
        temp = temp->prox;
    }
    printf("NULL\n");
}


int remover(Fila **inicio){
    Fila *atual = *inicio;
    if (atual->frente == NULL)
    {
        printf("Vazia1\n");
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

void liberar(Fila **inicio)
{
    while (!fila_vazia(*inicio))
    {
        remover(inicio);
    }

    free(*inicio);
    *inicio = iniciar();
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


int main() {
    Fila *fila = iniciar();
    int n, valor;

    printf("Digite a quantidade de elementos a serem somados: ");
    scanf("%d", &n);

    printf("Digite os valores para adicionar na fila (digite -1 para parar):\n");
    while (1) {
        scanf("%d", &valor);
        if (valor == -1) {
            break;
        }
        add(&fila, valor);
    }

    printf("Fila: ");
    printar(fila);

    nona(&fila, n);

    liberar(&fila);

    return 0;
}