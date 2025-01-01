#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha {
    char caracter;
    struct Pilha* prox;
} Pilha;

void adicionar(Pilha** topo, char caracter) {
    Pilha* novo = (Pilha*)malloc(sizeof(Pilha));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->caracter = caracter;
    novo->prox = *topo;
    *topo = novo;
}

Pilha* remover(Pilha* topo, char* caractere) {
    if (topo != NULL) {
        *caractere = topo->caracter;
        Pilha* novo_topo = topo->prox;
        free(topo);
        return novo_topo;
    }
    return NULL;
}

void inverterPalavra(Pilha** topo) {
    char caractere;
    while (*topo != NULL) {
        *topo = remover(*topo, &caractere);
        printf("%c", caractere);
    }
}

void inverteFrase(char* frase) {
    Pilha* pilha = NULL;

    printf("\nFrase Invertida: ");

    while (*frase != '\0') {
        if (*frase != ' ') {
            adicionar(&pilha, *frase); // Empilha o caractere da palavra
        } else {
            inverterPalavra(&pilha); // Desempilha e imprime a palavra invertida
            printf(" ");             // Imprime o espaço entre palavras
        }
        frase++;
    }
    inverterPalavra(&pilha); // Desempilha e imprime a última palavra
    printf("\n");
}

int main() {
    char frase[100];

    printf("Digite uma frase: ");
    fgets(frase, sizeof(frase), stdin);

    // Remove o caractere de nova linha, se presente
    frase[strcspn(frase, "\n")] = '\0';

    inverteFrase(frase);

    return 0;
}
