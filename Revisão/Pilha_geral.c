#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha
{
    char nome;
    struct Pilha *prox;
} Pilha;

typedef struct Topo
{
    Pilha *topo;
} Topo;

Topo *criar_pilha(){
    Topo *topo = (Topo *)malloc(sizeof(Topo));
    topo->topo = NULL;
    return topo;
}

void add(Topo *topo, char valor)
{
    Pilha *novo = malloc(sizeof(Pilha)); // tem que manter o ponteiro do topo atualizado

    novo->nome = valor;
    novo->prox = topo->topo;
    topo->topo = novo;
}

void criar(Topo *topo)
{
    char caractere;

    while (scanf(" %c", &caractere) == 1 && caractere != '1'){
        add(topo, caractere);
    }
}

void listar(Topo *topo)
{
    Pilha *atual = topo->topo;
    if (atual == NULL)
    {
        return;
    }
    while (atual != NULL)
    {
        printf("%c -> ", atual->nome);
        atual = atual->prox;
    }
    printf("INICIO\n");
}

void remover(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("VAZIA\n");
        return;
    }

    Pilha *atual = topo->topo;
    topo->topo = atual->prox;
    free(atual);
}

void liberar(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("VAZIA\n");
        return;
    }

    while (topo->topo != NULL)
    {
        remover(topo);
    }
    topo->topo = NULL;
}

void remover_repetidos(Topo *topo)
{
    Pilha *atual = topo->topo;
    while (atual != NULL && atual->prox != NULL)
    {
        Pilha *anterior = atual;
        Pilha *comparar = atual->prox;
        while (comparar != NULL)
        {
            if (atual->nome == comparar->nome)
            {
                anterior->prox = comparar->prox;
                free(comparar);
                comparar = anterior->prox;
            }
            else
            {
                anterior = comparar;
                comparar = comparar->prox;
            }
        }
        atual = atual->prox;
    }
}

void inverter(Topo *topo)
{
    Pilha *anterior = NULL;
    Pilha *atual = topo->topo;
    Pilha *proximo = NULL;
    while (atual != NULL)
    {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }
    topo->topo = anterior;
}

void inverter_palavras(char *frase)
{
    Topo *pilha = criar_pilha();
    char *palavra = strtok(frase, " ");
    
    while (palavra != NULL)
    {
        for (int i = 0; i < strlen(palavra); i++)
        {
            add(pilha, palavra[i]);
        }
        while (pilha->topo != NULL)
        {
            printf("%c", pilha->topo->nome);
            remover(pilha);
        }
        printf(" ");
        palavra = strtok(NULL, " ");
    }
    liberar(pilha);
    free(pilha);
}

int main()
{
    Topo *minhaPilha = criar_pilha(); // Criação da pilha
    int opcao;
    char frase[100];

    do
    {
        printf("\n=== MENU ===\n");
        printf("1 - Adicionar elemento na pilha\n");
        printf("2 - Listar elementos da pilha\n");
        printf("3 - Remover elemento do topo da pilha\n");
        printf("4 - Liberar toda a pilha\n");
        printf("5 - Remover elementos repetidos\n");
        printf("6 - Inverter a pilha\n");
        printf("7 - Inverter palavras de uma frase\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um valor para adicionar à pilha: ");
            criar(minhaPilha);
            break;
        case 2:
            printf("Elementos da pilha:\n");
            listar(minhaPilha);
            break;
        case 3:
            printf("Removendo elemento do topo...\n");
            remover(minhaPilha);
            break;
        case 4:
            printf("Liberando toda a pilha...\n");
            liberar(minhaPilha);
            break;
        case 5:
            printf("Removendo elementos repetidos...\n");
            remover_repetidos(minhaPilha);
            break;
        case 6:
            printf("Invertendo a pilha...\n");
            inverter(minhaPilha);
            break;
        case 7:
            printf("Digite uma frase: ");
            getchar(); // Limpar o buffer do teclado
            fgets(frase, sizeof(frase), stdin);
            frase[strcspn(frase, "\n")] = '\0'; // Remover o caractere de nova linha
            inverter_palavras(frase);
            printf("\n");
            break;
        case 0:
            printf("Saindo...\n");
            liberar(minhaPilha); // Garantir que a pilha seja liberada antes de sair
            free(minhaPilha);    // Liberar memória do topo
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}