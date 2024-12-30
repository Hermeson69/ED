#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha{
    int num;
    struct Pilha *prox;
}Pilha;

void adicionar (Pilha **pilha, int valor){
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = *pilha;
    *pilha = no;
}

void criar(Pilha **pilha){
    int num;
    while (scanf("%d\n", &num) == 1)
    {
        adicionar(pilha, num);
    }
    while (getchar() != '\n')
        ;
}


void listar(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("Pilha Vazia");
        return;
    }
    Pilha *atual = pilha;
    do
    {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    } while (atual != NULL);
    printf("INICIO\n");
}

int pop(Pilha **pilha)
{
    if (*pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return -1; 
    }
    Pilha *atual = *pilha;
    int valor = atual->num;
    *pilha = atual->prox;
    free(atual);
    return valor;
}

void aaaa(Pilha **pilha1, Pilha **pilha2) {
    if (*pilha1 == NULL || *pilha2 == NULL) {
        printf("Uma das pilhas está vazia\n");
        return;
    }

    Pilha *atual1 = *pilha1;
    Pilha *anterior1 = NULL;

    while (atual1 != NULL) {
        Pilha *atual2 = *pilha2;

        while (atual2 != NULL) {
            if (atual1->num == atual2->num) {
                Pilha *temp = atual1;
                if (anterior1 == NULL) {
                    *pilha1 = atual1->prox;
                } else {
                    anterior1->prox = atual1->prox;
                }
                atual1 = atual1->prox;
                free(temp);
                break;
            }
            atual2 = atual2->prox;
        }

        if (atual2 == NULL) {
            anterior1 = atual1;
            atual1 = atual1->prox;
        }
    }

    listar(*pilha1);
}

int main() {
    Pilha *pilha1 = NULL;
    Pilha *pilha2 = NULL;
    int opcao;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar na Pilha 1\n");
        printf("2. Adicionar na Pilha 2\n");
        printf("3. Listar Pilha 1\n");
        printf("4. Listar Pilha 2\n");
        printf("5. Remover elementos comuns\n");
        printf("6. Sair\n");
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
                listar(pilha1);
                break;
            case 4:
                printf("Pilha 2: ");
                listar(pilha2);
                break;
            case 5:
                aaaa(&pilha1, &pilha2);
                break;
            case 6:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
