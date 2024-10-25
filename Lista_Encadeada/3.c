#include <stdio.h>
#include <stdlib.h>

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

void criar_lista(Lista **lista)
{
    Lista **atual = lista;

    for (int i = 0; i < TAM; i++)
    {
        adicionar_elemento(atual, i+1);
        atual = &(*atual)->proximo;
    }
}

void buscar_lista(Lista *lista, int valor){
    Lista *busca = lista;
    int posicao = 1;
    int encontrado = 0;

    while (busca != NULL) {
        if (busca->numero == valor) {
            printf("Elemento: %d, encontrado na posicao: %d\n", valor, posicao);
            encontrado = 1;
            break;
        }
        busca = busca->proximo;
        posicao++;
    }

    if (!encontrado) {
        printf("Elemento: %d nao encontrado na lista.\n", valor);
    }
}

int printar_lista(Lista *list){

    int cont = 0;

    while(list !=  NULL)
    {
        cont++;
        printf("%d ", list->numero);
        list = list->proximo;
    }

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

void liberar_lista(Lista **lista) {
    Lista *atual = *lista;

    while (atual != NULL) {
        atual = *lista;
        lista = &(*lista)->proximo;
        free(atual);
    }
    free(lista);
}

int main()
{
    Lista *list_encadeda = iniciar();

    criar_lista(&list_encadeda);
    
    printf("\nTem %d Nos\n", printar_lista(list_encadeda)); 

    buscar_lista(list_encadeda, 5);
    buscar_lista(list_encadeda, 15);

    soma_lista(list_encadeda, 0);

    liberar_lista(&list_encadeda);

    return 0;
}