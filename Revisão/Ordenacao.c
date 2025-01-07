#include <stdio.h>
#include <stdlib.h>

// Definição do nó da lista duplamente encadeada
typedef struct No {
    int dado;
    struct No* anterior;
    struct No* proximo;
} No;

// Função para criar um nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->anterior = NULL;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para inserir no final da lista
void inserirNoFinal(No** cabeca, int dado) {
    No* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        No* atual = *cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
        novoNo->anterior = atual;
    }
}

// Função para imprimir a lista
void imprimirLista(No* cabeca) {
    if (!cabeca) {
        printf("Lista vazia\n");
        return;
    }
    No* atual = cabeca;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para trocar os dados entre dois nós
void trocarDados(No* a, No* b) {
    int temp = a->dado;
    a->dado = b->dado;
    b->dado = temp;
}

// Ordenação Bubble Sort
void ordenacaoBolha(No* cabeca) {
    if (!cabeca) return;

    int trocou;
    No* atual;
    No* fim = NULL;

    do {
        trocou = 0;
        atual = cabeca;

        while (atual->proximo != fim) {
            if (atual->dado > atual->proximo->dado) {
                trocarDados(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
        fim = atual;
    } while (trocou);
}

// Ordenação Selection Sort Recursiva
void ordenacaoSelecaoRecursiva(No* cabeca) {
    if (!cabeca || !cabeca->proximo) return;

    No* minimo = cabeca;
    No* atual = cabeca->proximo;

    // Encontra o menor elemento na sublista
    while (atual != NULL) {
        if (atual->dado < minimo->dado) {
            minimo = atual;
        }
        atual = atual->proximo;
    }

    // Troca o menor elemento com o primeiro elemento
    trocarDados(minimo, cabeca);

    // Chama recursivamente para o restante da lista
    ordenacaoSelecaoRecursiva(cabeca->proximo);
}

// Ordenação Insertion Sort Recursiva
void inserirOrdenado(No** cabecaOrdenada, No* novoNo) {
    if (*cabecaOrdenada == NULL || (*cabecaOrdenada)->dado >= novoNo->dado) {
        novoNo->proximo = *cabecaOrdenada;
        if (*cabecaOrdenada != NULL) {
            (*cabecaOrdenada)->anterior = novoNo;
        }
        *cabecaOrdenada = novoNo;
    } else {
        No* atual = *cabecaOrdenada;
        while (atual->proximo != NULL && atual->proximo->dado < novoNo->dado) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        if (atual->proximo != NULL) {
            atual->proximo->anterior = novoNo;
        }
        atual->proximo = novoNo;
        novoNo->anterior = atual;
    }
}

void ordenacaoInsercaoRecursiva(No** cabeca) {
    if (*cabeca == NULL || (*cabeca)->proximo == NULL) return;

    No* atual = (*cabeca)->proximo;
    atual->anterior->proximo = NULL;
    atual->anterior = NULL;

    ordenacaoInsercaoRecursiva(cabeca);

    inserirOrdenado(cabeca, atual);
}

// Função para dividir a lista para o Merge Sort
No* dividir(No* cabeca) {
    No* rapido = cabeca;
    No* lento = cabeca;

    while (rapido->proximo != NULL && rapido->proximo->proximo != NULL) {
        rapido = rapido->proximo->proximo;
        lento = lento->proximo;
    }

    No* segundaMetade = lento->proximo;
    lento->proximo = NULL;
    if (segundaMetade != NULL) {
        segundaMetade->anterior = NULL;
    }

    return segundaMetade;
}

// Função para mesclar duas listas para o Merge Sort
No* mesclar(No* lista1, No* lista2) {
    if (!lista1) return lista2;
    if (!lista2) return lista1;

    if (lista1->dado <= lista2->dado) {
        lista1->proximo = mesclar(lista1->proximo, lista2);
        lista1->proximo->anterior = lista1;
        lista1->anterior = NULL;
        return lista1;
    } else {
        lista2->proximo = mesclar(lista1, lista2->proximo);
        lista2->proximo->anterior = lista2;
        lista2->anterior = NULL;
        return lista2;
    }
}

// Merge Sort Recursivo
No* ordenacaoMerge(No* cabeca) {
    if (!cabeca || !cabeca->proximo) return cabeca;

    No* segundaMetade = dividir(cabeca);

    cabeca = ordenacaoMerge(cabeca);
    segundaMetade = ordenacaoMerge(segundaMetade);

    return mesclar(cabeca, segundaMetade);
}

// Função auxiliar para particionar (sem usar for)
No* particionar(No* inicio, No* fim) {
    int pivo = fim->dado;
    No* i = inicio->anterior;
    No* j = inicio;

    // Percorre a lista até chegar no nó "fim"
    while (j != fim) {
        if (j->dado <= pivo) {
            i = (i == NULL) ? inicio : i->proximo;
            trocarDados(i, j);
        }
        j = j->proximo;
    }
    i = (i == NULL) ? inicio : i->proximo;
    trocarDados(i, fim);
    return i;
}

// Quick Sort Recursivo (inalterado)
void ordenacaoQuick(No* inicio, No* fim) {
    if (fim != NULL && inicio != fim && inicio != fim->proximo) {
        No* pivo = particionar(inicio, fim);
        ordenacaoQuick(inicio, pivo->anterior);
        ordenacaoQuick(pivo->proximo, fim);
    }
}

// Função principal para teste
int main() {
    No* lista = NULL;

    inserirNoFinal(&lista, 4);
    inserirNoFinal(&lista, 2);
    inserirNoFinal(&lista, 8);
    inserirNoFinal(&lista, 1);
    inserirNoFinal(&lista, 5);

    printf("Lista original: ");
    imprimirLista(lista);

    printf("\nBubble Sort: ");
    ordenacaoBolha(lista);
    imprimirLista(lista);

    printf("\nSelection Sort: ");
    ordenacaoSelecaoRecursiva(lista);
    imprimirLista(lista);

    printf("\nInsertion Sort: ");
    ordenacaoInsercaoRecursiva(&lista);
    imprimirLista(lista);

    printf("\nMerge Sort: ");
    lista = ordenacaoMerge(lista);
    imprimirLista(lista);

    printf("\nQuick Sort: ");
    ordenacaoQuick(lista, lista->anterior); // Passa o início e o final da lista
    imprimirLista(lista);

    return 0;
}
