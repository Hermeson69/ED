#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct LISTA{
    int num;
    int posi;
    struct LISTA* prox;
} LISTA;

void *inicio(){
    return NULL;
}

void adicionar_elemento(LISTA **lista, int valor){
    LISTA *no = (LISTA *)malloc(sizeof(LISTA));
    no->num = valor;
    if (*lista == NULL){
        no->posi = 0;
        *lista = no;
        no->prox = *lista;
    } else {
        LISTA *atual = *lista;
        int cont = 1;
        while (atual->prox != *lista) {
            cont++;
            atual = atual->prox;
        }
        no->posi = cont;
        atual->prox = no;
        no->prox = *lista;
    }
}

void criar_lista(LISTA **lista){
    int valor;
    for (int i = 0; i < TAM; i++) {
        printf("Digite o valor para o elemento %d: ", i + 1);
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }
}

int printar(LISTA *lista){
    if (lista == NULL) {
        printf("Lista Vazia");
        return 0;
    }
    int cont = 0;
    LISTA *inicio = lista;
    do {
        cont++;
        printf("%d: %d -> ", lista->posi, lista->num);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");
    return cont;
}

void bubble_sort(LISTA **lista){
    if (*lista == NULL)
        return;
    int trocado;
    do {
        trocado = 0;
        LISTA *atual = *lista;
        while (atual->prox != *lista) {
            if (atual->num > atual->prox->num) {
                int temp = atual->num;
                atual->num = atual->prox->num;
                atual->prox->num = temp;
                trocado = 1;
            }
            atual = atual->prox;
        }
    } while (trocado);
}

void duas_listas_ordenadas(LISTA **lista1, LISTA **lista2){
    if (*lista1 == NULL || *lista2 == NULL) {
        printf("Uma das listas está vazia.\n");
        return;
    }

    LISTA *atual1 = *lista1;
    while (atual1->prox != *lista1) {
        atual1 = atual1->prox;
    }

    LISTA *atual2 = *lista2;
    while (atual2->prox != *lista2) {
        atual2 = atual2->prox;
    }

    atual1->prox = *lista2;
    atual2->prox = *lista1;

    bubble_sort(lista1);
}

void liberar(LISTA **lista){
    if (*lista == NULL) {
        return;
    }

    LISTA *atual = *lista;
    LISTA *prox_no;

    do {
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    } while (atual != *lista);

    *lista = NULL;
    printf("Lista Liberada");
}

void menu(){
    printf("\nMenu:\n");
    printf("1. Criar lista 1\n");
    printf("2. Criar lista 2\n");
    printf("3. Adicionar elemento na lista 1\n");
    printf("4. Adicionar elemento na lista 2\n");
    printf("5. Printar lista 1\n");
    printf("6. Printar lista 2\n");
    printf("7. Ordenar e combinar listas\n");
    printf("8. Liberar lista 1\n");
    printf("9. Liberar lista 2\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(){
    LISTA *lista1 = inicio();
    LISTA *lista2 = inicio();
    int opcao, valor;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            criar_lista(&lista1);
            break;
        case 2:
            criar_lista(&lista2);
            break;
        case 3:
            printf("Digite o valor a ser adicionado na lista 1: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista1, valor);
            break;
        case 4:
            printf("Digite o valor a ser adicionado na lista 2: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista2, valor);
            break;
        case 5:
            printf("\nLista 1: ");
            printar(lista1);
            break;
        case 6:
            printf("\nLista 2: ");
            printar(lista2);
            break;
        case 7:
            duas_listas_ordenadas(&lista1, &lista2);
            printf("\nLista combinada e ordenada: ");
            printar(lista1);
            break;
        case 8:
            liberar(&lista1);
            lista1 = inicio();
            break;
        case 9:
            liberar(&lista2);
            lista2 = inicio();
            break;
        case 0:
            liberar(&lista1);
            liberar(&lista2);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}