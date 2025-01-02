#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha {
    int num;
    struct Pilha *prox;
} Pilha;

typedef struct Topo {
    Pilha *topo;
} Topo;

void adicionar(Topo *topo, int valor) {
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = topo->topo;
    topo->topo = no;
}

void criar(Topo *topo) {
    int num;
    while (scanf("%d", &num) == 1) {
        adicionar(topo, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Topo *topo) {
    if (topo->topo == NULL) {
        printf("Pilha Vazia\n");
        return;
    }
    Pilha *atual = topo->topo;
    while (atual != NULL) {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("INICIO\n");
}

int pop(Topo *topo) {
    if (topo->topo == NULL) {
        printf("Pilha Vazia\n");
        return -1;
    }
    Pilha *atual = topo->topo;
    int valor = atual->num;
    topo->topo = atual->prox;
    free(atual);
    return valor;
}

void remover_repetidos(Topo *topo) {
    if (topo->topo == NULL) {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = topo->topo;
    while (atual != NULL && atual->prox != NULL) {
        Pilha *anterior = atual;
        Pilha *comparar = atual->prox;
        while (comparar != NULL) {
            if (atual->num == comparar->num) {
                anterior->prox = comparar->prox;
                free(comparar);
                comparar = anterior->prox;
            } else {
                anterior = comparar;
                comparar = comparar->prox;
            }
        }
        atual = atual->prox;
    }
}

int main() {
    Topo minhaPilha;
    minhaPilha.topo = NULL;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Criar Pilha\n");
        printf("2. Listar Pilha\n");
        printf("3. Remover Repetidos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite os valores para a pilha (Ctrl+D para terminar):\n");
            criar(&minhaPilha);
            break;
        case 2:
            listar(&minhaPilha);
            break;
        case 3:
            remover_repetidos(&minhaPilha);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
