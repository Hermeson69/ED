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

void ver_tam(Topo *topo1, Topo *topo2, int *tam1, int *tam2) {
    Pilha *atual1 = topo1->topo;
    Pilha *atual2 = topo2->topo;
    int cont1 = 0;
    int cont2 = 0;
    while (atual1 != NULL) {
        cont1++;
        atual1 = atual1->prox;
    }
    while (atual2 != NULL) {
        cont2++;
        atual2 = atual2->prox;
    }
    *tam1 = cont1;
    *tam2 = cont2;
}

int pilhas_iguais(Topo *topo1, Topo *topo2) {
    int tam1, tam2;
    ver_tam(topo1, topo2, &tam1, &tam2);
    if (tam1 != tam2) {
        return 0;
    }
    Pilha *atual1 = topo1->topo;
    Pilha *atual2 = topo2->topo;
    while (atual1 != NULL && atual2 != NULL) {
        if (atual1->num != atual2->num) {
            return 0;
        }
        atual1 = atual1->prox;
        atual2 = atual2->prox;
    }
    return 1;
}

void maiores_que(Topo *topo, int valor) {
    if (topo->topo == NULL) {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = topo->topo;
    Topo maiores = {NULL};
    while (atual != NULL) {
        if (atual->num > valor) {
            adicionar(&maiores, atual->num);
        }
        atual = atual->prox;
    }

    listar(&maiores);
}

int main() {
    Topo pilha1 = {NULL};
    Topo pilha2 = {NULL};
    int opcao, valor;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar na Pilha 1\n");
        printf("2. Adicionar na Pilha 2\n");
        printf("3. Listar Pilha 1\n");
        printf("4. Listar Pilha 2\n");
        printf("5. Remover do topo da Pilha 1\n");
        printf("6. Remover do topo da Pilha 2\n");
        printf("7. Verificar se as pilhas sao iguais\n");
        printf("8. Listar elementos maiores que um valor na Pilha 1\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar(&pilha1);
                break;
            case 2:
                criar(&pilha2);
                break;
            case 3:
                printf("Pilha 1: ");
                listar(&pilha1);
                break;
            case 4:
                printf("Pilha 2: ");
                listar(&pilha2);
                break;
            case 5:
                valor = pop(&pilha1);
                if (valor != -1) {
                    printf("Valor removido da Pilha 1: %d\n", valor);
                }
                break;
            case 6:
                valor = pop(&pilha2);
                if (valor != -1) {
                    printf("Valor removido da Pilha 2: %d\n", valor);
                }
                break;
            case 7:
                if (pilhas_iguais(&pilha1, &pilha2)) {
                    printf("As pilhas sao iguais\n");
                } else {
                    printf("As pilhas sao diferentes\n");
                }
                break;
            case 8:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                printf("Elementos maiores que %d na Pilha 1: ", valor);
                maiores_que(&pilha1, valor);
                break;
            case 9:
                printf("Saindo...\n");
                while (pilha1.topo != NULL) {
                    pop(&pilha1);
                }
                while (pilha2.topo != NULL) {
                    pop(&pilha2);
                }
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
