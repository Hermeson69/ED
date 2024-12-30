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





int buscar(Pilha *pilha, int valor)
{
    if (pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return 0;
    }

    Pilha *atual = pilha;
    while (atual != NULL)
    {
        if (atual->num == valor)
        {
            printf("Valor: %d aquii\n", valor);
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}
void remover_buscados(Pilha **pilha, int valor)
{
    if (*pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *temp = NULL;
    int encontrado = 0;

    while (*pilha != NULL)
    {
        int topo = pop(pilha);
        if (topo != valor)
        {
            adicionar(&temp, topo);
        }
        else
        {
            encontrado = 1;
        }
    }

    while (temp != NULL)
    {
        adicionar(pilha, pop(&temp));
    }

    if (!encontrado)
    {
        printf("Valor não encontrado na pilha\n");
    }
}
int main()
{
    Pilha *pilha = NULL;
    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar valor\n");
        printf("2. Listar pilha\n");
        printf("3. Buscar valor\n");
        printf("4. Remover valor\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar(&pilha);
            break;
        case 2:
            listar(pilha);
            break;
        case 3:
            printf("Digite um valor para buscar: ");
            scanf("%d", &valor);
            buscar(pilha, valor);
            break;
        case 4:
            printf("Digite um valor para remover: ");
            scanf("%d", &valor);
            remover_buscados(&pilha, valor);
            break;
        case 5:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}