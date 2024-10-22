#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 10

typedef struct Lista
{
    int numero;
    struct Lista *proximo;
} Lista;

void *iniciar(){
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->numero = valor;
    novo_no->proximo = NULL;

    if(*lista == NULL){
        *lista = novo_no;
    }
    else{
        Lista *atual = *lista;

        while(atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        
        atual->proximo = novo_no;
    }
}

void adicionar_no_inicio(Lista **lista, int valor) {
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->numero = valor;
    novo_no->proximo = *lista;
    *lista = novo_no;
}

void adicionar_depois_de(Lista **lista, int valor, int posicao) {
    Lista *atual = *lista;
    int cont = 0;

    while (atual != NULL && cont < posicao - 1) {
        atual = atual->proximo;
        cont++;
    }

    if (atual == NULL) {
        printf("Posicao invalida\n");
    } else {
        adicionar_elemento(&(atual->proximo), valor);
    }
}

void criar_lista(Lista **lista)
{
    int valor;
    for (int i = 0; i < TAM; i++)
    {
        printf("Digite o valor para o elemento %d: ", i + 1);
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }
}

void buscar_lista(Lista *lista, int valor){
    Lista *busca = lista;
    int posicao = 1;
    int encontrado = 0;

    while (busca != NULL) {
        if (busca->numero == valor) {
            printf("Elemento: %d, posicao: %d\n", valor, posicao);
            encontrado = 1;
            break;
        }
        busca = busca->proximo;
        posicao++;
    }

    if (!encontrado) {
        printf("Elemento: %d nao encontrado\n", valor);
    }
}

int printar_lista(Lista *list){

    int cont = 0;

    while(list !=  NULL)
    {
        cont++;
        printf("%d -> ", list->numero);
        list = list->proximo;
    }
    printf("NULL\n");

    return cont;
}

void soma_lista(Lista *lista, int soma){
    Lista *atual = lista;
    float media = 0;
    int cont = 0;

    while(atual != NULL){
        soma += atual->numero;
        atual = atual->proximo;

        cont++;
    }

    media = soma / cont;
    printf("\nSoma: %d\nMedia: %.2f\n", soma, media);
}

void remover_nos_repetidos(Lista **lista) {
    Lista *atual = *lista;
    while (atual != NULL && atual->proximo != NULL) {
        Lista *comparar = atual;
        while (comparar->proximo != NULL) {
            if (atual->numero == comparar->proximo->numero) {
                Lista *duplicado = comparar->proximo;
                comparar->proximo = comparar->proximo->proximo;
                free(duplicado);
            } else {
                comparar = comparar->proximo;
            }
        }
        atual = atual->proximo;
    }
}

void concatenar(Lista **lista1, Lista **lista2) {
    if (*lista1 == NULL) {
        *lista1 = *lista2;
    } else {
        Lista *atual = *lista1;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = *lista2;
    }
    printf("\nLista concatenada: ");
    printar_lista(*lista1);
}

void string_intersecao(Lista **lista1, Lista **lista2) {
    Lista *intersecao = NULL;
    Lista *temp1 = *lista1;

    while (temp1 != NULL) {
        Lista *temp2 = *lista2;
        while (temp2 != NULL) {
            if (temp1->numero == temp2->numero) {
                adicionar_elemento(&intersecao, temp1->numero);
                break;
            }
            temp2 = temp2->proximo;
        }
        temp1 = temp1->proximo;
    }

    printf("\nLista de intersecao: ");
    remover_nos_repetidos(&intersecao);
    printar_lista(intersecao);
    printf("\n");
}

void liberar_lista(Lista *lista) {
    Lista *atual = lista;
    Lista *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Criar lista\n");
    printf("2. Adicionar elemento\n");
    printf("3. Adicionar no inicio\n");
    printf("4. Adicionar depois de\n");
    printf("5. Buscar elemento\n");
    printf("6. Printar lista\n");
    printf("7. Soma e media da lista\n");
    printf("8. Remover nos repetidos\n");
    printf("9. Concatenar listas\n");
    printf("10. Intersecao de listas\n");
    printf("11. Liberar lista\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Lista *list_encadeda = iniciar();
    Lista *list_encadeda2 = iniciar();
    int opcao, valor, posicao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_lista(&list_encadeda);
                break;
            case 2:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                adicionar_elemento(&list_encadeda, valor);
                break;
            case 3:
                printf("Digite o valor a ser adicionado no inicio: ");
                scanf("%d", &valor);
                adicionar_no_inicio(&list_encadeda, valor);
                break;
            case 4:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                printf("Digite a posicao: ");
                scanf("%d", &posicao);
                adicionar_depois_de(&list_encadeda, valor, posicao);
                break;
            case 5:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                buscar_lista(list_encadeda, valor);
                break;
            case 6:
                printf("\nLista: ");
                printf("%d", printar_lista(list_encadeda));
                break;
            case 7:
                soma_lista(list_encadeda, 0);
                break;
            case 8:
                remover_nos_repetidos(&list_encadeda);
                break;
            case 9:
                criar_lista(&list_encadeda2);
                concatenar(&list_encadeda, &list_encadeda2);
                break;
            case 10:
                criar_lista(&list_encadeda2);
                string_intersecao(&list_encadeda, &list_encadeda2);
                break;
            case 11:
                liberar_lista(list_encadeda);
                list_encadeda = iniciar();
                break;
            case 0:
                liberar_lista(list_encadeda);
                liberar_lista(list_encadeda2);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}