#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct Lista
{
    int numero;
    struct Lista *proximo;
} Lista;

void *iniciar()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->numero = valor;

    if (*lista == NULL)
    {
        *lista = novo_no;
        novo_no->proximo = *lista;
    }
    else
    {
        Lista *atual = *lista;

        while (atual->proximo != *lista)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;
        novo_no->proximo = *lista;
    }
}

void criar_lista(Lista **lista)
{
    for (int i = 0; i < TAM; i++)
    {
        adicionar_elemento(lista, i + 1);
    }
}

void remover_elemento(Lista **lista, int valor)
{
    if (*lista == NULL)
        return;
    Lista *atual = *lista;
    Lista *anterior = NULL;
    do
    {
        if (atual->numero == valor)
        {
            if (anterior == NULL)
            {
                Lista *ultimo = *lista;
                while (ultimo->proximo != *lista)
                {
                    ultimo = ultimo->proximo;
                }
                if (atual == atual->proximo)
                {
                    *lista = NULL;
                }
                else
                {
                    ultimo->proximo = atual->proximo;
                    *lista = atual->proximo;
                }
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }


        anterior = atual;
        atual = atual->proximo;

    } while (atual != *lista);
     printf("Valor nao ta na lista\n");
}

int printar_lista(Lista *lista)
{
    if (lista == NULL)
        return 0;

    Lista *inicio = lista;
    int cont = 0;

    do
    {
        cont++;
        printf("%d ", lista->numero);
        lista = lista->proximo;
    } while (lista != inicio);

    return cont;
}


int main()
{
    Lista *lista_encadeada = iniciar();
    int opcao, valor;

    do
    {
        printf("\nMenu:\n");
        printf("1. Criar lista\n");
        printf("2. Adicionar elemento\n");
        printf("3. Remover elemento\n");
        printf("4. Printar lista\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar_lista(&lista_encadeada);
            break;
        case 2:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista_encadeada, valor);
            break;
        case 3:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            remover_elemento(&lista_encadeada, valor);
            break;
        case 4:
            printf("\nTem %d Nos\n", printar_lista(lista_encadeada));
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