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

// int contem(Pilha *pilha, int valor)
// {
//     while (pilha != NULL)
//     {
//         if (pilha->num == valor)
//         {
//             return 1;
//         }
//         pilha = pilha->prox;
//     }
//     return 0;
// }
// void remover_repetidos(Pilha **pilha)
// {
//     if (*pilha == NULL)
//     {
//         printf("Pilha Vazia\n");
//         return;
//     }

//     Pilha *temp = NULL;
//     Pilha *valores = NULL;

//     while (*pilha != NULL)
//     {
//         int topo = pop(pilha);
//         if (!contem(valores, topo))
//         {
//             adicionar(&valores, topo);
//             adicionar(&temp, topo);
//         }
//     }

//     while (temp != NULL)
//     {
//         adicionar(pilha, pop(&temp));
//     }
// }

void remover_repetidos(Pilha **pilha)
{
    if (*pilha == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = *pilha;
    while (atual != NULL && atual->prox != NULL)
    {
        Pilha *anterior = atual;
        Pilha *comparar = atual->prox;
        while (comparar != NULL)
        {
            if (atual->num == comparar->num)
            {
                anterior->prox = comparar->prox;
                free(comparar);
                comparar = anterior->prox;
            }
            else
            {
                anterior = comparar;
                comparar = comparar->prox;
            }
        }
        atual = atual->prox;
    }
}

int main()
{
    Pilha *minhaPilha = NULL;
    int opcao;

    do
    {
        printf("\nMenu:\n");
        printf("1. Criar Pilha\n");
        printf("2. Listar Pilha\n");
        printf("3. Remover Repetidos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os valores para a pilha (Ctrl+D para terminar):\n");
            criar(&minhaPilha);
            break;
        case 2:
            listar(minhaPilha);
            break;
        case 3:
            remover_repetidos(&minhaPilha);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}