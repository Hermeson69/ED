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

int main()
{

    Lista *list_encadeda = iniciar();

    criar_lista(&list_encadeda);
    
    printf("\nTem %d Nos\n", printar_lista(list_encadeda)); 

    return 0;
}