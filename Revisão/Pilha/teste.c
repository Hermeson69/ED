#include <stdio.h>
#include <stdlib.h>

//PILHAS
typedef struct Pilha{
    int num;
    struct Pilha* prox;
}Pilha;
void push(Pilha **pilha, int valor){
    Pilha *novo_no = (Pilha *)malloc(sizeof(Pilha));
    novo_no->num = valor;
    novo_no->prox = *pilha;
    *pilha = novo_no;
}

void criar(Pilha *pilha){
    int valor;
    for(int i = 0; i < 10; i++){
        printf("Digite o valor para o elemento %d: ", i + 1);
        scanf("%d", &valor);
        push(&pilha, valor);
    }
}

void listar(Pilha *pilha){
    if(pilha == NULL){
        printf("Pilha Vazia");
        return;
    }
    Pilha *atual = pilha;
    do{
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }while(atual != pilha);
    printf("INICIO\n");
}

void pop(Pilha **pilha){
    if(*pilha == NULL){
        printf("Pilha Vazia\n");
        return;
    }
    Pilha *atual = *pilha;
    Pilha *anterior = NULL;
    do{
        anterior = atual;
        atual = atual->prox;
    }while(atual->prox != *pilha);
    anterior->prox = *pilha;
    free(atual);
}

void menu(){
    printf("1. Criar Pilha\n");
    printf("2. Adicionar Elemento\n");
    printf("3. Printar Pilha\n");
    printf("4. Remover Elemento\n");
    printf("5. Sair\n");
}


int main(){
    Pilha *pilha = NULL;
    int opcao, valor;

    do{
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                criar(pilha);
                break;
            case 2:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                push(&pilha, valor);
                break;
            case 3:
                listar(pilha);
                break;
            case 4:
                pop(&pilha);
                break;
        }
    }while(opcao != 5);

    return 0;
}

