#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct Lista {
    int num;
    struct Lista* prox;
    int posicao;
} Lista;

void *inicio() {
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor){
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    if (*lista == NULL){
        no->posicao = 0;
        *lista = no;
        no->prox = *lista;
    } else {
        Lista *atual = *lista;
        int cont = 1;
        while (atual->prox != *lista) {
            cont++;
            atual = atual->prox;
        }
        no->posicao = cont;
        atual->prox = no;
        no->prox = *lista;
    }
}
void criar_lista(Lista **lista) {
    int valor;
    for (int i = 0; i < TAM; i++) {
        printf("Valor do no: %d: ", i + 1);
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }
}

int printar(Lista *lista){
    if (lista == NULL) {
        printf("Lista Vazia");
        return 0;
    }
    int cont = 0;
    Lista *inicio = lista;
    do {
        cont++;
        printf("%d: %d -> ", lista->posicao, lista->num);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");
    return cont;
}


void remover_repetidos(Lista **lista) {
    if (*lista == NULL) {
        printf("Lista Vazia\n");
        return;
    } else {
        Lista *atual = *lista;
        do {
            Lista *precorrer = atual;
            Lista *proximo = atual->prox;
            while (proximo != *lista) {
                if (atual->num == proximo->num) {
                    precorrer->prox = proximo->prox;
                    free(proximo);
                    proximo = precorrer->prox;
                } else {
                    precorrer = proximo;
                    proximo = proximo->prox;
                }
            }
            atual = atual->prox;
        } while (atual != *lista);
    }
}

void liberar(Lista **lista) {
    if (*lista == NULL) {
        return;
    }

    Lista *atual = *lista;
    Lista *prox_no;

    do {
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    } while (atual != *lista);

    *lista = NULL;
    printf("Lista Liberada\n");
}

void menu() {
    printf("1. Criar Lista\n");
    printf("2. Adicionar Elemento\n");
    printf("3. Printar Lista\n");
    printf("4. Remover Repetidos\n");
    printf("5. Liberar Lista\n");
    printf("6. Sair\n");
}

int main() {
    Lista *lista = inicio();
    int opcao, valor;

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_lista(&lista);
                break;
            case 2:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                adicionar_elemento(&lista, valor);
                break;
            case 3:
                printar(lista);
                break;
            case 4:
                remover_repetidos(&lista);
                printar(lista);
                break;
            case 5:
                liberar(&lista);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}