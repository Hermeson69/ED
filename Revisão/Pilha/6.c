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

void remover_comuns(Topo *topo1, Topo *topo2) {
    if (topo1->topo == NULL || topo2->topo == NULL) {
        printf("Uma das pilhas está vazia\n");
        return;
    }

    Pilha *atual1 = topo1->topo;
    Pilha *anterior1 = NULL;

    while (atual1 != NULL) {
        Pilha *atual2 = topo2->topo;

        while (atual2 != NULL) {
            if (atual1->num == atual2->num) {
                Pilha *temp = atual1;
                if (anterior1 == NULL) {
                    topo1->topo = atual1->prox;
                } else {
                    anterior1->prox = atual1->prox;
                }
                atual1 = atual1->prox;
                free(temp);
                break;
            }
            atual2 = atual2->prox;
        }

        if (atual2 == NULL) {
            anterior1 = atual1;
            atual1 = atual1->prox;
        }
    }

    listar(topo1);
}

int main() {
    Topo topo1 = {NULL};
    Topo topo2 = {NULL};
    int opcao;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar na Pilha 1\n");
        printf("2. Adicionar na Pilha 2\n");
        printf("3. Listar Pilha 1\n");
        printf("4. Listar Pilha 2\n");
        printf("5. Remover elementos comuns\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar(&topo1);
                break;
            case 2:
                criar(&topo2);
                break;
            case 3:
                printf("Pilha 1: ");
                listar(&topo1);
                break;
            case 4:
                printf("Pilha 2: ");
                listar(&topo2);
                break;
            case 5:
                remover_comuns(&topo1, &topo2);
                break;
            case 6:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
