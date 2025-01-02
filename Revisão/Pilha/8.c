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
    while (getchar() != '\n');
}

void listar(Topo *topo) {
    if (topo->topo == NULL) {
        printf("Pilha Vazia\n");
        return;
    }
    Pilha *atual = topo->topo;
    do {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    } while (atual != NULL);
    printf("INICIO\n");
}

int remover(Topo *topo) {
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

void num_mod(int n) {
    Topo mods = {NULL};
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            adicionar(&mods, i);
        }
    }
    listar(&mods);
    while (mods.topo != NULL) {
        remover(&mods);
    }
}

int main() {
    Topo topo = {NULL};
    int opcao, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar valor na pilha\n");
        printf("2. Listar pilha\n");
        printf("3. Remover valor da pilha\n");
        printf("4. Criar pilha\n");
        printf("5. Numeros pares ate N\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor: ");
                criar(&topo);
                break;
            case 2:
                listar(&topo);
                break;
            case 3:
                valor = remover(&topo);
                if (valor != -1) {
                    printf("Valor removido: %d\n", valor);
                }
                break;
            case 4:
                printf("Digite os valores (Ctrl+D para finalizar): ");
                criar(&topo);
                break;
            case 5:
                printf("Digite um valor N: ");
                scanf("%d", &valor);
                num_mod(valor);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    while (topo.topo != NULL) {
        remover(&topo);
    }

    return 0;
}