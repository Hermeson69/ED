#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct Lista
{
    int num;
    struct Lista *prox;

} Lista;

void *inicio()
{
    return NULL;
}
// Adicionar no Final
void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    novo_no->prox = NULL;

    if (*lista == NULL)
    {
        *lista = novo_no;
    }
    else
    {
        Lista *atual = *lista;

        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }

        atual->prox = novo_no;
    }
}
// Adicionar no Inicio
void adicionar_no_inicio(Lista **lista, int valor){
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    novo_no->prox = *lista;
    *lista = novo_no;
}
// Adicionar Depois de
void adicionar_depois_de(Lista **lista, int valor, int posicao){
    Lista *atual = *lista;
    int cont = 0;
    while (atual != NULL && cont < posicao - 1)
    {
        atual = atual->prox;
        cont++;
    }

    if (atual == NULL)
    {
        printf("Posicao nao encontrada ou invalida!\n");
    }
    else
    {
        adicionar_elemento(&(atual->prox), valor);
    }
}
// Criar Lista
void criar(Lista **lista)
{
    int valor;
    for (int i = 0; i < TAM; i++)
    {
        printf("Digite o valor da posicao %d:", i + 1);
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }
}

void remover_so_um(Lista **lista, int valor)
{
    Lista *busca = *lista;
    Lista *anterior = NULL;
    while (busca != NULL)
    {
        if (busca->num == valor)
        {
            if (anterior == NULL)
            {
                *lista = busca->prox;
            }
            else
            {
                anterior->prox = busca->prox;
            }
            free(busca);
            return;
        }
        anterior = busca;
        busca = busca->prox;
    }
}
// Buscar
void buscar_lista(Lista **lista, int valor)
{
    Lista *busca = *lista;
    int posicao = 0;
    int encontrado = 0;

    while (busca != NULL)
    {
        if (busca->num == valor)
        {
            printf("Elemento: %d, posicao: %d\n", valor, posicao + 1);
            encontrado = 1;
            break;
        }
        busca = busca->prox;
        posicao++;
    }

    if (!encontrado)
    {
        printf("Elemento: %d nao encontrado\n", valor);
    }
}
// Print
int print_lista(Lista *lista)
{
    int cont = 0;
    while (lista != NULL)
    {
        cont++;
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
    printf("NULL");
    return cont;
}
// Soma Elementos Lista
void soma_elementos_lista(Lista *lista, float soma)
{
    int cont = 0;
    while (lista != NULL)
    {
        cont++;
        soma += lista->num;
        lista = lista->prox;
    }

    printf("Lista media: %f", soma / cont);
}
// Remover repetidos
void remover_nos_repetidos(Lista **lista)
{
    Lista *atual = *lista;
    while (atual != NULL)
    {
        Lista *comparar = atual;
        while (comparar->prox != NULL)
        {
            if (atual->num == comparar->prox->num)
            {
                Lista *duplicado = comparar->prox;
                comparar->prox = comparar->prox->prox;
                free(duplicado);
            }
            else
            {
                comparar = comparar->prox;
            }
        }
        atual = atual->prox;
    }
}
// concatenar
void concatenar(Lista **lista1, Lista **lista2)
{
    if (*lista1 == NULL)
    {
        *lista1 = *lista2;
    }
    else
    {
        Lista *atual = *lista1;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = *lista2;
    }
    print_lista(*lista1);
}
// void alterar
void alterar(Lista **lista, int valor)
{
    Lista *busca = *lista;
    int novo;
    int cont = 0;
    while (busca != NULL)
    {
        if (busca->num == valor)
        {
            printf("Novo valor do no:%d ", cont + 1);
            scanf("%d", &novo);
            busca->num = novo;
        }
        cont++;
        busca = busca->prox;
    }
}
// Intersecao
void intersecao(Lista **lista1, Lista **lista2)
{
    Lista *temp1 = *lista1;
    Lista *intersecao = NULL;
    while (temp1 != NULL)
    {
        Lista *temp2 = *lista2;
        while (temp2 != NULL)
        {
            if (temp1->num == temp2->num)
            {
                adicionar_elemento(&intersecao, temp1
                                                    ->num);
                break;
            }
            temp2 = temp2->prox;
        }
        temp1 = temp1->prox;
    }

    remover_nos_repetidos(&intersecao);
    print_lista(intersecao);
}

void liberar(Lista **lista)
{
    Lista *atual = *lista;
    Lista *proximo;
    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int main()
{
    Lista *lista_encadeada = inicio();
    Lista *lista_encadeada2 = inicio();
    int opcao, valor, posicao;

    do
    {
        printf("\nMenu:\n");
        printf("1. Criar lista\n");
        printf("2. Adicionar elemento no final\n");
        printf("3. Adicionar elemento no inicio\n");
        printf("4. Adicionar elemento depois de uma posicao\n");
        printf("5. Buscar elemento\n");
        printf("6. Imprimir lista\n");
        printf("7. Somar elementos da lista\n");
        printf("8. Remover elementos repetidos\n");
        printf("9. Concatenar duas listas\n");
        printf("10. Alterar elemento\n");
        printf("11. Intersecao de duas listas\n");
        printf("12. Liberar lista\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar(&lista_encadeada);
            break;
        case 2:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_elemento(&lista_encadeada, valor);
            break;
        case 3:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            adicionar_no_inicio(&lista_encadeada, valor);
            break;
        case 4:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            printf("Digite a posicao: ");
            scanf("%d", &posicao);
            adicionar_depois_de(&lista_encadeada, valor, posicao);
            break;
        case 5:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            buscar_lista(&lista_encadeada, valor);
            break;
        case 6:
            print_lista(lista_encadeada);
            break;
        case 7:
            soma_elementos_lista(lista_encadeada, 0);
            break;
        case 8:
            remover_nos_repetidos(&lista_encadeada);
            break;
        case 9:
            printf("Criando segunda lista para concatenar:\n");
            criar(&lista_encadeada2);
            concatenar(&lista_encadeada, &lista_encadeada2);
            break;
        case 10:
            printf("Digite o valor a ser alterado: ");
            scanf("%d", &valor);
            alterar(&lista_encadeada, valor);
            break;
        case 11:
            printf("Criando segunda lista para intersecao:\n");
            criar(&lista_encadeada2);
            intersecao(&lista_encadeada, &lista_encadeada2);
            break;
        case 12:
            liberar(&lista_encadeada);
            break;
        case 0:
            liberar(&lista_encadeada);
            liberar(&lista_encadeada2);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
