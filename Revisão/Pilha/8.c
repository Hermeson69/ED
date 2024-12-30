#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha {
    int num;
    struct Pilha *prox;
} Pilha;

void adicionar(Pilha **pilha, int valor) {
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = *pilha;
    *pilha = no;
}

void criar(Pilha **pilha) {
    int num;
    while (scanf("%d", &num) == 1) {
        adicionar(pilha, num);
    }
    while (getchar() != '\n');
}

void listar(Pilha *pilha) {
    if (pilha == NULL) {
        printf("Pilha Vazia\n");
        return;
    }
    Pilha *atual = pilha;
    do {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    } while (atual != NULL);
    printf("INICIO\n");
}

int remover(Pilha **pilha) {
    if (*pilha == NULL) {
        printf("Pilha Vazia\n");
        return -1;
    }
    Pilha *atual = *pilha;
    int valor = atual->num;
    *pilha = atual->prox;
    free(atual);
    return valor;
}

void num_mod(int n) {
    Pilha *mods = NULL;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            adicionar(&mods, i);
        }
    }
    listar(mods);
    while (mods != NULL) {
        remover(&mods);
    }
}

int main() {
    Pilha *pilha = NULL;
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
                criar(&pilha);
                break;
            case 2:
                listar(pilha);
                break;
            case 3:
                valor = remover(&pilha);
                if (valor != -1) {
                    printf("Valor removido: %d\n", valor);
                }
                break;
            case 4:
                printf("Digite os valores (Ctrl+D para finalizar): ");
                criar(&pilha);
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

    while (pilha != NULL) {
        remover(&pilha);
    }

    return 0;
}