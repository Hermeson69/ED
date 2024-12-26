#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct LISTA
{
    int num;
    int posi;
    struct LISTA *prox;
} LISTA;

void *inicio()
{
    return NULL;
}

void adicionar_elemento(LISTA **lista, int valor)
{
    LISTA *no = (LISTA *)malloc(sizeof(LISTA));
    no->num = valor;
    if (*lista == NULL)
    {
        no->posi = 0;
        *lista = no;
        no->prox = *lista;
    }
    else
    {
        LISTA *atual = *lista;
        int cont = 0;
        do
        {
            cont++;
            atual = atual->prox;
        } while (atual != *lista);
        no->posi = cont;
        atual->prox = no;
        no->prox = *lista;
    }
}

void criar_lista(LISTA **lista)
{
    int valor;
    for (int i = 0; i < TAM; i++)
    {
        printf("Valor do no: %d: ", i + 1);
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }
}

int printar(LISTA *lista)
{

    if (lista == NULL)
    {
        printf("Lista Vazia");
        return 0;
    }
    int cont = 0;
    LISTA *inicio = lista;
    do
    {
        cont++;
        printf("%d: %d -> ", lista->posi, lista->num);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");

    return cont;
}

void insercao(LISTA **lista1, LISTA **lista2)
{
    if (*lista1 == NULL || *lista2 == NULL)
    {
        printf("Uma das listas está vazia.\n");
        return;
    }

    LISTA *temp1 = *lista1;
    LISTA *temp2 = *lista2;
    int found = 0;

    do
    {
        temp2 = *lista2;
        do
        {
            if (temp1->num == temp2->num)
            {
                found = 1;
                break;
            }
            temp2 = temp2->prox;
        } while (temp2 != *lista2);

        if (!found)
        {
            printf("Numero %d da lista 1 nao encontrado na lista 2.\n", temp1->num);
        }
        temp1 = temp1->prox;
    } while (temp1 != *lista1);

    if (found)
    {
        printf("Todos os numeros da lista 1 foram encontrados na lista 2.\n");
    }
}


void liberar(LISTA **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    LISTA *atual = *lista;
    LISTA *prox_no;

    do
    {
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    } while (atual != *lista);

    *lista = NULL;
    printf("Lista Liberada");
}

void menu()
{
    printf("\nMenu:\n");
    printf("1. Criar lista 1\n");
    printf("2. Criar lista 2\n");
    printf("3. Adicionar elemento na lista 1\n");
    printf("4. Adicionar elemento na lista 2\n");
    printf("5. Printar lista 1\n");
    printf("6. Printar lista 2\n");
    printf("7. Inserir elementos de lista 1 em lista 2\n");
    printf("8. Liberar lista 1\n");
    printf("9. Liberar lista 2\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    LISTA *lista1 = inicio();
    LISTA *lista2 = inicio();
    int opcao, valor;

    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar_lista(&lista1);
            break;
        case 2:
            criar_lista(&lista2);
            break;
        case 3:
            printf("Digite o valor a ser adicionado na lista 1: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista1, valor);
            break;
        case 4:
            printf("Digite o valor a ser adicionado na lista 2: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista2, valor);
            break;
        case 5:
            printf("\nLista 1: ");
            printar(lista1);
            break;
        case 6:
            printf("\nLista 2: ");
            printar(lista2);
            break;
        case 7:
            insercao(&lista1, &lista2);
            break;
        case 8:
            liberar(&lista1);
            lista1 = inicio();
            break;
        case 9:
            liberar(&lista2);
            lista2 = inicio();
            break;
        case 0:
            liberar(&lista1);
            liberar(&lista2);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}