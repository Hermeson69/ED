#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    char cliente;
    struct No *prox;
} No;

typedef struct Fila
{
    No *frente;
    No *atras;
} Fila;

No *criar(char c)
{
    No *no = (No *)malloc(sizeof(No));
    if (!no)
    {
        printf("Erro no Malloc\n");
        exit(-1);
    }

    no->cliente = c;
    no->prox = NULL;
    return no;
}

Fila *inicializar()
{
    Fila *inicio = (Fila *)malloc(sizeof(Fila));
    if (!inicio)
    {
        printf("Erro no Malloc\n");
        exit(-1);
    }
    inicio->frente = inicio->atras = NULL;
    return inicio;
}

void adicionar(Fila *inicio, char c)
{
    No *no = criar(c);
    if (inicio->atras == NULL)
    {
        inicio->frente = inicio->atras = no;
        return;
    }
    inicio->atras->prox = no;
    inicio->atras = no;
}

int remover(Fila *inicio)
{
    if (inicio->frente == NULL)
    {
        printf("Fila vazia\n");
        return -1;
    }

    No *temp = inicio->frente;
    int temp_valor = temp->cliente;
    inicio->frente = inicio->frente->prox;
    if (inicio->frente == NULL)
    {
        inicio->atras = NULL;
    }
    free(temp);
    return temp_valor;
}

int fila_vazia(Fila *inicio)
{
    return inicio->frente == NULL;
}

void printar(Fila *inicio)
{
    No *temp = inicio->frente;
    while (temp)
    {
        printf("%c -> ", temp->cliente);
        temp = temp->prox;
    }
    printf("NULL\n");
}

int tamanho(Fila *fila)
{
    if (fila == NULL)
    {
        return 0;
    }

    int cont = 0;
    No *temp = fila->frente;
    while (temp != NULL)
    {
        temp = temp->prox;
        cont++;
    }

    return cont;
}

void liberar(Fila *inicio)
{
    while (!fila_vazia(inicio))
    {
        remover(inicio);
    }

    free(inicio);
}

int caixa_menor(Fila *fila[], int numCaixas)
{
    int menor = 0;
    for (int i = 1; i < numCaixas; i++)
    {
        if (tamanho(fila[i]) < tamanho(fila[menor]))
        {
            menor = i;
        }
    }
    return menor;
}

int main()
{
    int numCaixas = 3;
    Fila *caixas[numCaixas];

    for (int i = 0; i < numCaixas; i++)
    {
        caixas[i] = inicializar();
    }

    int opcao;
    char cliente;
    do
    {
        printf("Escolha uma opcao:\n");
        printf("1. Adicionar cliente\n");
        printf("2. Remover cliente\n");
        printf("3. Imprimir filas\n");
        printf("4. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o cliente (caractere): ");
            scanf(" %c", &cliente);
            adicionar(caixas[caixa_menor(caixas, numCaixas)], cliente);
            break;
        case 2:
            printf("Digite o numero da caixa (0 a %d): ", numCaixas - 1);
            int caixa;
            scanf("%d", &caixa);
            if (caixa >= 0 && caixa < numCaixas)
            {
                int removido = remover(caixas[caixa]);
                if (removido != -1)
                {
                    printf("Cliente %c removido da caixa %d\n", removido, caixa);
                }
            }
            else
            {
                printf("Caixa invalida\n");
            }
            break;
        case 3:
            for (int i = 0; i < numCaixas; i++)
            {
                printf("Caixa %d: ", i);
                printar(caixas[i]);
            }
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida\n");
        }
    } while (opcao != 4);

    for (int i = 0; i < numCaixas; i++)
    {
        liberar(caixas[i]);
    }

    return 0;
}