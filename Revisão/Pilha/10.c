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
    while (atual != NULL) {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
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

int primo(int valor) {
    if (valor <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= valor; i++) {
        if (valor % i == 0) {
            return 0;
        }
    }
    return 1;
}

void primos_nao(Topo *topo) {
    Topo primos = {NULL};
    Topo original = {NULL};
    if (topo->topo == NULL) {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = topo->topo;
    while (atual != NULL) {
        if (primo(atual->num)) {
            adicionar(&primos, atual->num);
        } else {
            adicionar(&original, atual->num);
        }
        atual = atual->prox;
    }

    printf("Primos:\n");
    listar(&primos);
    printf("Nao Primos:\n");
    listar(&original);

    while (topo->topo != NULL) {
        remover(topo);
    }

    while (primos.topo != NULL) {
        remover(&primos);
    }
    while (original.topo != NULL) {
        remover(&original);
    }
}

int main() {
    Topo topo = {NULL};
    int opcao, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Listar elementos\n");
        printf("3. Remover elemento\n");
        printf("4. Separar primos e nao primos\n");
        printf("5. Sair\n");
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
                    printf("Elemento removido: %d\n", valor);
                }
                break;
            case 4:
                primos_nao(&topo);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
