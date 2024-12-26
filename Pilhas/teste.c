#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Função para criar um novo nó
Node* criarNo(int data) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->data = data;
    novoNo->next = NULL;
    return novoNo;
}

// Função para empilhar (push)
void push(Node** top, int data) {
    Node* novoNo = criarNo(data);
    novoNo->next = *top;
    *top = novoNo;
}

// Função para desempilhar (pop)
int pop(Node** top) {
    if (*top == NULL) {
        return -1; // Pilha vazia
    }
    Node* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

// Função para exibir a pilha
void exibirPilha(Node* top) {
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

// Função para remover números menores que um valor fornecido
void removerMenores(Node** pilha, int valor) {
    Node* pilhaAux = NULL;

    // Move os elementos maiores ou iguais para a pilha auxiliar
    while (*pilha != NULL) {
        int elemento = pop(pilha);
        if (elemento >= valor) {
            push(&pilhaAux, elemento);
        }
    }

    // Move os elementos de volta para a pilha original
    while (pilhaAux != NULL) {
        push(pilha, pop(&pilhaAux));
    }
}

// Função principal para teste
int main() {
    Node* pilha = NULL;

    // Exemplo de entrada
    push(&pilha, 2);
    push(&pilha, 7);
    push(&pilha, 3);
    push(&pilha, 5);
    push(&pilha, 1);

    printf("Pilha original: ");
    exibirPilha(pilha);

    int valor;
    printf("Digite o valor limite: ");
    scanf("%d", &valor);

    removerMenores(&pilha, valor);

    printf("Pilha após remover elementos menores que %d: ", valor);
    exibirPilha(pilha);

    return 0;
}
