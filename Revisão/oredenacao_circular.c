#include <stdio.h>
#include <stdlib.h>

// Definição do nó da lista circular
typedef struct No {
    int dado;
    struct No* proximo;
} No;

// Função para criar um nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

// Inserir nó no final da lista circular
No* inserir(No* ultimo, int dado) {
    No* novoNo = criarNo(dado);
    if (ultimo == NULL) {
        novoNo->proximo = novoNo;
        return novoNo;
    }
    novoNo->proximo = ultimo->proximo;
    ultimo->proximo = novoNo;
    return novoNo;
}

// Imprimir a lista circular
void imprimir(No* ultimo) {
    if (ultimo == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    No* atual = ultimo->proximo;
    do {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    } while (atual != ultimo->proximo);
    printf("CIRCULO\n");
}

// Trocar os dados de dois nós
void trocarDados(No* a, No* b) {
    int temp = a->dado;
    a->dado = b->dado;
    b->dado = temp;
}

// 1. Bubble Sort
void bubbleSort(No* ultimo) {
    if (ultimo == NULL) return;
    int trocou;
    No* atual;
    No* limite = NULL;

    do {
        trocou = 0;
        atual = ultimo->proximo;
        while (atual->proximo != limite) {
            if (atual->dado > atual->proximo->dado) {
                trocarDados(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
        limite = atual;
    } while (trocou);
}

// 2. Selection Sort
void selectionSort(No* ultimo) {
    if (ultimo == NULL) return;

    No* i = ultimo->proximo;
    do {
        No* menor = i;
        No* j = i->proximo;
        while (j != ultimo->proximo) {
            if (j->dado < menor->dado) {
                menor = j;
            }
            j = j->proximo;
        }
        trocarDados(i, menor);
        i = i->proximo;
    } while (i != ultimo->proximo);
}

// 3. Insertion Sort
void insertionSort(No** ultimo) {
    if (*ultimo == NULL) return;

    No* sorted = NULL;
    No* atual = (*ultimo)->proximo;

    do {
        No* proximo = atual->proximo;
        if (sorted == NULL || sorted->dado >= atual->dado) {
            atual->proximo = sorted == NULL ? atual : sorted;
            sorted = atual;
        } else {
            No* temp = sorted;
            while (temp->proximo != NULL && temp->proximo->dado < atual->dado) {
                temp = temp->proximo;
            }
            atual->proximo = temp->proximo;
            temp->proximo = atual;
        }
        atual = proximo;
    } while (atual != (*ultimo)->proximo);

    // Ajustar o último nó
    No* temp = sorted;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    *ultimo = temp;
}

// 4. Merge Sort
No* merge(No* esquerda, No* direita) {
    if (esquerda == NULL) return direita;
    if (direita == NULL) return esquerda;

    if (esquerda->dado <= direita->dado) {
        esquerda->proximo = merge(esquerda->proximo, direita);
        return esquerda;
    } else {
        direita->proximo = merge(esquerda, direita->proximo);
        return direita;
    }
}

void mergeSort(No** ultimo) {
    if (*ultimo == NULL || (*ultimo)->proximo == *ultimo) return;

    No* meio = *ultimo;
    No* anterior = NULL;
    No* atual = *ultimo;
    while (atual != *ultimo) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = NULL;

    mergeSort(&(*ultimo)->proximo);
    mergeSort(&atual);

    *ultimo = merge(*ultimo, atual);
}

// 5. Quick Sort
No* particionar(No* inicio, No* fim) {
    int pivo = fim->dado;
    No* i = inicio;

    while (i != fim) {
        if (i->dado <= pivo) {
            i = i->proximo;
        }
    }

    trocarDados(i, fim);
    return i;
}

void ordenacaoQuick(No* inicio, No* fim) {
    if (fim != NULL && inicio != fim && inicio != fim->proximo) {
        No* pivo = particionar(inicio, fim);
        ordenacaoQuick(inicio, pivo->proximo);
        ordenacaoQuick(pivo->proximo, fim);
    }
}

int main() {
    No* ultimo = NULL;

    // Inserir alguns dados na lista circular
    ultimo = inserir(ultimo, 10);
    ultimo = inserir(ultimo, 20);
    ultimo = inserir(ultimo, 30);
    ultimo = inserir(ultimo, 50);
    ultimo = inserir(ultimo, 40);

    // Exibir a lista original
    printf("Lista original: ");
    imprimir(ultimo);

    // Ordenação com Bubble Sort
    bubbleSort(ultimo);
    printf("Bubble Sort: ");
    imprimir(ultimo);

    // Recriar a lista
    ultimo = NULL;
    ultimo = inserir(ultimo, 10);
    ultimo = inserir(ultimo, 20);
    ultimo = inserir(ultimo, 30);
    ultimo = inserir(ultimo, 50);
    ultimo = inserir(ultimo, 40);

    // Ordenação com Selection Sort
    selectionSort(ultimo);
    printf("Selection Sort: ");
    imprimir(ultimo);

    // Recriar a lista
    ultimo = NULL;
    ultimo = inserir(ultimo, 10);
    ultimo = inserir(ultimo, 20);
    ultimo = inserir(ultimo, 30);
    ultimo = inserir(ultimo, 50);
    ultimo = inserir(ultimo, 40);

    // Ordenação com Insertion Sort
    insertionSort(&ultimo);
    printf("Insertion Sort: ");
    imprimir(ultimo);

    // Recriar a lista
    ultimo = NULL;
    ultimo = inserir(ultimo, 10);
    ultimo = inserir(ultimo, 20);
    ultimo = inserir(ultimo, 30);
    ultimo = inserir(ultimo, 50);
    ultimo = inserir(ultimo, 40);

    // Ordenação com Merge Sort
    mergeSort(&ultimo);
    printf("Merge Sort: ");
    imprimir(ultimo);

    // Recriar a lista
    ultimo = NULL;
    ultimo = inserir(ultimo, 10);
    ultimo = inserir(ultimo, 20);
    ultimo = inserir(ultimo, 30);
    ultimo = inserir(ultimo, 50);
    ultimo = inserir(ultimo, 40);

    // Ordenação com Quick Sort
    No* fim = ultimo;
    while (fim->proximo != ultimo) {
        fim = fim->proximo;
    }
    ordenacaoQuick(ultimo->proximo, fim);
    printf("Quick Sort: ");
    imprimir(ultimo);

    return 0;
}
