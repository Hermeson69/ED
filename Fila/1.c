#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da fila
typedef struct Node {
    int data;
    struct Node* next;
} Node;
 
// Estrutura para a fila
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Função para criar uma nova fila
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Função para adicionar um elemento à fila
void enqueue(Queue** queue, int data) {
    int data;
    printf("Digite um valor para enfileirar: ");
    scanf("%d", &data);

    Node* newNode = createNode(data);
    if ((*queue)->rear == NULL) {
        (*queue)->front = (*queue)->rear = newNode;
        return; 
    }
    (*queue)->rear->next = newNode;
    (*queue)->rear = newNode;
}

// Função para remover um elemento da fila
int dequeue(Queue** queue) {
    if ((*queue)->front == NULL) {
        printf("Fila vazia\n");
        return -1;
    }
    Node* temp = (*queue)->front;
    int data = temp->data;
    (*queue)->front = (*queue)->front->next;

    if ((*queue)->front == NULL) {
        (*queue)->rear = NULL;
    }

    free(temp);
    return data;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Função para imprimir a fila
void printQueue(Queue* queue) {
    Node* temp = queue->front;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Função para liberar a memória alocada para a fila
void liberarQueue(Queue** queue) {
    while (!isEmpty(*queue)) {
        dequeue(queue);
    }
    free(*queue);
    *queue = NULL;
}

int main() {
    Queue* queue = createQueue();

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Fila: ");
    printQueue(queue);

    printf("Desenfileirado: %d\n", dequeue(&queue));
    printf("Fila apos desenfileirar um elemento: ");
    printQueue(queue);

    liberarQueue(&queue);

    return 0;
}
void menu() {
    Queue* queue = createQueue();
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Enfileirar\n");
        printf("2. Desenfileirar\n");
        printf("3. Imprimir fila\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite um valor para enfileirar: ");
                scanf("%d", &value);
                enqueue(&queue, value);
                break;
            case 2:
                value = dequeue(&queue);
                if (value != -1) {
                    printf("Desenfileirado: %d\n", value);
                }
                break;
            case 3:
                printf("Fila: ");
                printQueue(queue);
                break;
            case 4:
                liberarQueue(&queue);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}