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
    while (atual != NULL) {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
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

void primos_nao(Pilha **pilha) {
    Pilha *primos = NULL;
    Pilha *original = NULL;
    if (*pilha == NULL) {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = *pilha;
    while (atual != NULL) {
        if (primo(atual->num)) {
            adicionar(&primos, atual->num);
        } else {
            adicionar(&original, atual->num);
        }
        atual = atual->prox;
    }

    printf("Primos:\n");
    listar(primos);
    printf("Nao Primos:\n");
    listar(original);

    while (*pilha != NULL) {
        remover(pilha);
    }

    while (primos != NULL) {
        remover(&primos);
    }
    while (original != NULL) {
        remover(&original);
    }
}

int main() {
    Pilha *pilha = NULL;
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
                criar(&pilha);
                break;
            case 2:
                listar(pilha);
                break;
            case 3:
                valor = remover(&pilha);
                if (valor != -1) {
                    printf("Elemento removido: %d\n", valor);
                }
                break;
            case 4:
                primos_nao(&pilha);
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