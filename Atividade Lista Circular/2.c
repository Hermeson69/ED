#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Lista
{
    int num;
    int posicao;
    struct Lista *prox;
} Lista;

void *inicio()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    if (*lista == NULL)
    {
        novo_no->posicao = 1;  
        *lista = novo_no;
        novo_no->prox = *lista;  
    }
    else
    {
        Lista *atual = *lista;
        int cont = 1;
        
        while (atual->prox != *lista)
        {
            cont++;
            atual = atual->prox;
        }
        novo_no->posicao = cont + 1;  
        atual->prox = novo_no;
        novo_no->prox = *lista;  
    }
}

int primo(int num)
{
    if (num <= 1)
        return 0; 
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0; 
    }
    return 1;
}

void criar_lista(Lista **lista, int TAM)
{
    int num = 2;  
    int count = 0;
    while (count < TAM)
    {
        if (primo(num))
        {
            adicionar_elemento(lista, num);
            count++;
        }
        num++;
    }
}

int printar(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista Vazia\n");
        return 0;
    }

    int cont = 0;
    Lista *inicio = lista;
    do
    {
        cont++;
        printf("%d: %d -> ", lista->posicao, lista->num);
        lista = lista->prox;
    } while (inicio != lista);

    printf("INICIO\n");
    return cont;
}

void liberar(Lista **lista)
{
    if (*lista == NULL)
    {
        return;
    }
    Lista *atual = *lista;
    Lista *prox_no;
    do
    {
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    } while (atual != *lista);
    *lista = NULL;
    printf("Lista Liberada\n");
}

void menu()
{
    printf("\nMenu:\n");
    printf("1. Criar lista\n");
    printf("2. Adicionar elemento\n");
    printf("3. Printar lista\n");
    printf("4. Liberar lista\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Lista *list_encadeda = inicio();
    int opcao, valor, tamanho;
    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Tamanho da Lista\n");
            scanf("%d", &tamanho);
            criar_lista(&list_encadeda, tamanho);
            break;
        case 2:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_elemento(&list_encadeda, valor);
            break;
        case 3:
            printf("\nLista: ");
            printar(list_encadeda);
            break;
        case 4:
            liberar(&list_encadeda);
            list_encadeda = inicio();
            break;
        case 0:
            liberar(&list_encadeda);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
