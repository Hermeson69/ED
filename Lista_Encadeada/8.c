#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM 10

typedef struct Lista
{
    char nome[50];
    struct Lista *proximo;
} Lista;

void *iniciar(){
    return NULL;
}

void adicionar_elemento(Lista **lista, const char *nome)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    strcpy(novo_no->nome, nome);
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

void organizar_nomes(Lista **lista, const char *nome){
    Lista *atual = *lista;
    Lista *anterior = NULL;
    Lista *proximo = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    proximo = atual->proximo;

    if (anterior != NULL)
    {
       anterior->proximo = proximo;
    } else {
       *lista = proximo;
    }
    atual->proximo = proximo->proximo;
    proximo->proximo = atual;
}

int printar_lista(Lista *list){

    int cont = 0;

    while(list !=  NULL)
    {
        cont++;
        printf("%s -> ", list->nome);
        list = list->proximo;
    }
    printf("NULL\n");

    return cont;
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

int main() {
    Lista *lista = NULL;

    // Adicionar nomes à lista
    adicionar_elemento(&lista, "Leonardo");
    adicionar_elemento(&lista, "Jose");
    adicionar_elemento(&lista, "Erick");
    adicionar_elemento(&lista, "Samuel");
    adicionar_elemento(&lista, "Joao");

    printf("Lista original:\n");
    printar_lista(lista);

    // Reorganizar nomes na lista
    organizar_nomes(&lista, "Erick");

    printf("Lista apos reorganizacao:\n");
    printar_lista(lista);

    liberar_lista(lista);

    return 0;
}