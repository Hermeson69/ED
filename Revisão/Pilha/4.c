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

void ver_tam(Pilha **pilha1, Pilha **pilha2, int *tam1, int *tam2) {
    Pilha *atual1 = *pilha1;
    Pilha *atual2 = *pilha2;
    int cont1 = 0;
    int cont2 = 0;
    while (atual1 != NULL) {
        cont1++;
        atual1 = atual1->prox;
    }
    while (atual2 != NULL) {
        cont2++;
        atual2 = atual2->prox;
    }
    *tam1 = cont1;
    *tam2 = cont2;
}

int pilhas_iguais(Pilha **pilha1, Pilha **pilha2) {
    int tam1, tam2;
    ver_tam(pilha1, pilha2, &tam1, &tam2);
    if (tam1 != tam2) {
        return 0;
    }
    Pilha *atual1 = *pilha1;
    Pilha *atual2 = *pilha2;
    while (atual1 != NULL && atual2 != NULL) {
        if (atual1->num != atual2->num) {
            return 0;
        }
        atual1 = atual1->prox;
        atual2 = atual2->prox;
    }
    return 1;
}

void maiores_que(Pilha **pilha, int valor){
    if (*pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = *pilha;
    Pilha *maiores = NULL;
    while (atual != NULL)
    {
        if (atual->num > valor)
        {
            adicionar(&maiores, atual->num);
        }
        atual = atual->prox;
    }

    listar(maiores);
}

int main() {
    Pilha *pilha1 = NULL;
    Pilha *pilha2 = NULL;
    int opcao, valor;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar na Pilha 1\n");
        printf("2. Adicionar na Pilha 2\n");
        printf("3. Listar Pilha 1\n");
        printf("4. Listar Pilha 2\n");
        printf("5. Remover do topo da Pilha 1\n");
        printf("6. Remover do topo da Pilha 2\n");
        printf("7. Verificar se as pilhas sao iguais\n");
        printf("8. Sair\n");
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
                valor = pop(&pilha1);
                if (valor != -1) {
                    printf("Valor removido da Pilha 1: %d\n", valor);
                }
                break;
            case 6:
                valor = pop(&pilha2);
                if (valor != -1) {
                    printf("Valor removido da Pilha 2: %d\n", valor);
                }
                break;
            case 7:
                if (pilhas_iguais(&pilha1, &pilha2)) {
                    printf("As pilhas sao iguais\n");
                } else {
                    printf("As pilhas sao diferentes\n");
                }
                break;
            case 8:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}