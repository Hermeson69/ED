#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha {
    char caracter;
    struct Pilha *prox;
} Pilha;

void adicionar(Pilha **topo, char caracter)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));
    if (!novo)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->caracter = caracter;
    novo->prox = *topo;
    *topo = novo;
}

char remover(Pilha **topo)
{
    if (*topo != NULL)
    {
        char caractere = (*topo)->caracter;
        Pilha *novo_topo = (*topo)->prox;
        free(*topo);
        *topo = novo_topo;
        return caractere;
    }
    return '\0';
}

int igual(Pilha *topo, char caracter)
{
    while (topo != NULL)
    {
        if (topo->caracter == caracter)
        {
            return 1;
        }
        topo = topo->prox;
    }
    return 0;
}

void listar(Pilha **topo)
{
    if (*topo == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }

    Pilha *temp = NULL;
    Pilha *repetidos = NULL;

    while (*topo != NULL)
    {
        char inicio = remover(topo);
        if (!igual(repetidos, inicio))
        {
            adicionar(&repetidos, inicio);
            adicionar(&temp, inicio);
        }
    }
    while (temp != NULL)
    {
        adicionar(topo, remover(&temp));
    }

    while (*topo != NULL)
    {
        char c = remover(topo);
        printf("%c ", c);
        adicionar(&temp, c);
    }

    printf("\n");
}

int main()
{
    Pilha *topo = NULL;
    int opcao;
    char frase[100];

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar frase\n");
        printf("2. Remover frase\n");
        printf("3. Listar caracteres\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        getchar();  // Limpar o buffer de entrada após o scanf

        switch (opcao)
        {
        case 1:
            printf("Digite uma frase: ");
            fgets(frase, sizeof(frase), stdin);

            
            frase[strcspn(frase, "\n")] = '\0';

    
            for (int i = 0; i < strlen(frase); i++)
            {
                adicionar(&topo, frase[i]);
            }
            break;

        case 2:
            {
                char c = remover(&topo);
                if (c != '\0')
                {
                    printf("Caractere removido: %c\n", c);
                }
                else
                {
                    printf("Pilha vazia.\n");
                }
            }
            break;

        case 3:
            listar(&topo);
            break;

        case 4:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
