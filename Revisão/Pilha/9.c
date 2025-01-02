#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha {
    int num;
    struct Pilha *prox;
} Pilha;

typedef struct Topo {
    Pilha *topo;
} Topo;

void adicionar(Topo *topo, int valor)
{
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = topo->topo;
    topo->topo = no;
}

void criar(Topo *topo)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        adicionar(topo, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }
    Pilha *atual = topo->topo;
    while (atual != NULL)
    {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("INICIO\n");
}

int remover(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return -1;
    }
    Pilha *atual = topo->topo;
    int valor = atual->num;
    topo->topo = atual->prox;
    free(atual);
    return valor;
}

void positivos_negativos(Topo *topo)
{
    Topo positivos = {NULL};
    Topo negativos = {NULL};
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = topo->topo;
    while (atual != NULL)
    {
        if (atual->num > 0)
        {
            adicionar(&positivos, atual->num);
        }
        if (atual->num < 0)
        {
            adicionar(&negativos, atual->num);
        }
        atual = atual->prox;
    }

    listar(&positivos);
    listar(&negativos);
    while (topo->topo != NULL)
    {
        remover(topo);
    }

    while (positivos.topo != NULL)
    {
        remover(&positivos);
    }
    while (negativos.topo != NULL)
    {
        remover(&negativos);
    }
}

int main()
{
    Topo topo = {NULL};
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
            criar(&topo);
            break;
        case 2:
            listar(&topo);
            break;
        case 3:
            valor = remover(&topo);
            if (valor != -1)
            {
                printf("Elemento removido: %d\n", valor);
            }
            break;
        case 4:
            positivos_negativos(&topo);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    while (topo.topo != NULL)
    {
        remover(&topo);
    }

    return 0;
}