#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha
{
    int num;
    struct Pilha *prox;
} Pilha;

void adicionar(Pilha **pilha, int valor)
{
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = *pilha;
    *pilha = no;
}

void criar(Pilha **pilha)
{
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

int remover(Pilha **pilha)
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

void binario(int num){
    Pilha *pilha = NULL;
    if (num == 0) {
        adicionar(&pilha, 0);
    } else {
        while (num > 0) {
            adicionar(&pilha, num % 2);
            num /= 2;
        }
    }
    listar(pilha);
    while (pilha != NULL) {
        remover(&pilha);
    }
}
int main()
{
    Pilha *pilha = NULL;
    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento na pilha\n");
        printf("2. Listar elementos da pilha\n");
        printf("3. Remover elemento da pilha\n");
        printf("4. Converter numero para binario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um valor: ");
            criar(&pilha);
            break;
        case 2:
            listar(pilha);
            break;
        case 3:
            valor = remover(&pilha);
            if (valor != -1)
            {
                printf("Elemento removido: %d\n", valor);
            }
            break;
        case 4:
            printf("Digite um numero: ");
            scanf("%d", &valor);
            binario(valor);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}