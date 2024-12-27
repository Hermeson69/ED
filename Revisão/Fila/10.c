#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int num;
    struct No *prox;
}No;

typedef struct Fila{
    No *atras;
    No *frente;
}Fila;

No *criar_no(int valor){
    No *no = (No *)malloc(sizeof(No));
    if (!no)
    {
        printf("Erro no Malloc!\n");
        exit(-1);
    }
    no->num = valor;
    no->prox = NULL;
    return no;
}

Fila *inicializar(){
    Fila *inicio = (Fila *)malloc(sizeof(Fila));
    if (!inicio)
    {
        printf("Erro Malloc");
        exit(-1);
    }
    inicio->frente = inicio->atras = NULL;
    return inicio;
}

int fila_vazia(Fila *inicio)
{
    return inicio->frente == NULL;
}


void adicionar_elemento(Fila **inicio, int valor){
    No *no = criar_no(valor);
    Fila *atual = *inicio;
    if (atual->atras == NULL)
    {
        atual->frente = atual->atras = no;
    }else{
        atual->atras->prox = no;
        atual->atras = no;
    }
}

void adicionar_elemento_ordenado(Fila **inicio, int valor){
    No *no = criar_no(valor);
    Fila *atual = *inicio;
    if (fila_vazia(atual))
    {
        atual->frente = atual->atras = no;
        return;
    }

    No *temp = atual->frente;
    No *proximo = NULL;

    while (temp != NULL && temp->num < valor)
    {
        proximo = temp;
        temp = temp->prox;
    }

    if (proximo == NULL)
    {
        no->prox = atual->frente;
        atual->frente = no;
    }
    else
    {
        no->prox = proximo->prox;
        proximo->prox = no;
    }

    if (no->prox == NULL)
    {
        atual->atras = no;
    }
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
    *inicio = inicializar();
}

int e_primo(int num) {
    if (num <= 1) return 0;
    if (num % 2 == 0) return 0;
    for (int i = 2; i * i <= num; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}
void primos(Fila *inicio){
    Fila *primos = inicializar();
    Fila *nao_primos = inicializar();
    while (!fila_vazia(inicio))
    {
        int valor = remover(&inicio);
        if (e_primo(valor))
        {
            adicionar_elemento(&primos, valor);
        }else{
            adicionar_elemento(&nao_primos, valor);
        }
    }

    printar(primos);
    printar(nao_primos);
    
}

int main() {
    Fila *fila = inicializar();
    int opcao, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Adicionar elemento ordenado\n");
        printf("3. Remover elemento\n");
        printf("4. Imprimir fila\n");
        printf("5. Separar primos e nao primos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                adicionar_elemento(&fila, valor);
                break;
            case 2:
                printf("Digite o valor a ser adicionado ordenado: ");
                scanf("%d", &valor);
                adicionar_elemento_ordenado(&fila, valor);
                break;
            case 3:
                if (fila_vazia(fila)) {
                    printf("Fila vazia!\n");
                } else {
                    valor = remover(&fila);
                    printf("Elemento removido: %d\n", valor);
                }
                break;
            case 4:
                printar(fila);
                break;
            case 5:
                primos(fila);
                break;
            case 6:
                liberar(&fila);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}
