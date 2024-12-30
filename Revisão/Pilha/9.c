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
    while (scanf("%d", &num) == 1)
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
    while (atual != NULL)
    {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("INICIO\n");
}

int remover(Pilha **pilha)
{
    if (*pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return 1;
    }
    Pilha *atual = *pilha;
    int valor = atual->num;
    *pilha = atual->prox;
    free(atual);
    return valor;
}

void positivos_negativos(Pilha **pilha)
{
    Pilha *positivos = NULL;
    Pilha *negativos = NULL;
    if (*pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = *pilha;
    while (atual != NULL)
    {
        if (atual->num > 0)
        {
            adicionar(&positivos, atual->num);
        }
        if(atual->num < 0)
        {
            adicionar(&negativos, atual->num);
        }
        atual = atual->prox;
    }

    listar(positivos);
    listar(negativos);
    while (*pilha != NULL)
    {
        remover(pilha);
    }

    while (positivos != NULL)
    {
        remover(&positivos);
    }
    while (negativos != NULL)
    {
        remover(&negativos);
    }
}

int main()
{
    Pilha *pilha = NULL;
    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Listar elementos\n");
        printf("3. Remover elemento\n");
        printf("4. Separar positivos e negativos\n");
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
            positivos_negativos(&pilha);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    while (pilha != NULL)
    {
        remover(&pilha);
    }

    return 0;
}