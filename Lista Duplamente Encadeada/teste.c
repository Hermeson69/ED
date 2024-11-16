#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    int num;
    struct Lista *prox;
    struct Lista *ant;
} Lista;

void *inicio(){
    return NULL;
}

void comeco(Lista **lista, int valor){
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    novo_no->prox = *lista;
    novo_no->ant = NULL;

    if (*lista != NULL){
        (*lista)->ant = novo_no;
    }
    *lista = novo_no;
}

int imprimir(Lista *lista){
    int cont = 0;
    if (lista == NULL){
        printf("Lista Vazia");
        return 0;
    }

    Lista *atual = lista;
    do{
        cont++;
        printf("%d -> ", atual->num);
        atual = atual->prox;
    } while (atual != NULL);
    printf("NULL\n");

    return cont;
}

void fim(Lista **lista, int valor){
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    novo_no->prox = NULL;

    if (*lista == NULL){
        novo_no->ant = NULL;
        *lista = novo_no;
    }else{
        Lista *atual = *lista;
        while (atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novo_no;
        novo_no->ant = atual;
    }
}

void liberar(Lista **lista){
    if (*lista == NULL){
        return;
    }

    Lista *atual = *lista;
    Lista *prox_no;

    do{
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    } while (atual != NULL);

    *lista = NULL;
 printf("Lista Liberada");
}

int main(){
    Lista *list_encadeda = inicio();

    comeco(&list_encadeda, 10);
    comeco(&list_encadeda, 5);
    fim(&list_encadeda, 20);
    fim(&list_encadeda, 30);
    comeco(&list_encadeda, 1);



    imprimir(list_encadeda);
   
    liberar(&list_encadeda);

    return 0;
}