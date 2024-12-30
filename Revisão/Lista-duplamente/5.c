#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int num;
    struct Lista *prox;
    struct Lista *ante;

} Lista;

Lista *iniciar()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->num = valor;
    no->ante = iniciar();
    no->prox = iniciar();
    if (*lista == NULL)
    {
        *lista = no;
    }
    else
    {
        Lista *atual = *lista;
        while (atual != NULL && atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = no;
        no->ante = atual;
    }
}

void criar(Lista **lista)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        adicionar_elemento(lista, num);
    }
    while (getchar() != '\n')
        ;
}

int imprimir(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia!\n");
        exit(1);
    }

    int cont = 0;
    printf("NULL ");
    while (lista != NULL)
    {
        cont++;
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
    printf("NULL\n");

    return cont;
}

void liberar(Lista **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista *atual = *lista;
    Lista *proximo;
    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *lista = iniciar();
    printf("Lista vazia\n");
}

void rotaciona(Lista **lista, int rotacoes)
{
    // Verifico se é null
    if (*lista == NULL)
    {
        printf("Lista vazia!\n");
        exit(1);
    }

    Lista *atual = *lista;
    int cont = 1;

    // Ver o tamanho da lista
    while (atual->prox != NULL)
    {
        atual = atual->prox;
        cont++;
    }
    
    // temporariamente fazer uma circular
    atual->prox = *lista;
    (*lista)->ante = atual;
    
    // ver se numero de rotacoes nao é maior que a lista
    rotacoes = rotacoes % cont;
    
    // tamanho da lista - numero de rotacoes
    for (int i = 0; i < cont - rotacoes; i++)
    {
        atual = atual->prox;
    }
    
    *lista = atual->prox;
    (*lista)->ante = NULL;
    atual->prox = NULL;
}
int main()
{
    Lista *lista = iniciar();
    int opcao, valor, rotacoes;

    while (1)
    {
        printf("1. Criar lista\n");
        printf("2. Adicionar elemento\n");
        printf("3. Imprimir lista\n");
        printf("4. Rotacionar lista\n");
        printf("5. Liberar lista\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os elementos da lista (Ctrl+D para finalizar):\n");
            criar(&lista);
            break;
        case 2:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista, valor);
            break;
        case 3:
            imprimir(lista);
            break;
        case 4:
            printf("Digite o numero de rotacoes: ");
            scanf("%d", &rotacoes);
            rotaciona(&lista, rotacoes);
            break;
        case 5:
            liberar(&lista);
            break;
        case 6:
            liberar(&lista);
            exit(0);
        default:
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}