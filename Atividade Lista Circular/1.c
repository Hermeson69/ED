#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct Lista
{
    int posicao;
    int num;
    struct Lista *prox;
} Lista;

void *inicio()
{
    return NULL;
}

void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->num = valor;
    if (*lista == NULL)
    {
        novo_no->posicao = 0;
        *lista = novo_no;
        novo_no->prox = *lista;
    }
    else
    {
        int cont = 1;
        Lista *atual = *lista;
        while (atual->prox != *lista)
        {
            cont++;
            atual = atual->prox;
        }
        novo_no->posicao = cont;
        atual->prox = novo_no;
        novo_no->prox = *lista;
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

int printar(Lista *lista)
{

    if (lista == NULL)
    {
        printf("Lista Vazia");
        return 0;
    }
    int cont = 0;
    Lista *inicio = lista;
    do
    {
        cont++;
        printf("%d: %d -> ", lista->posicao, lista->num);
        lista = lista->prox;
    } while (lista != inicio);
    printf("INICIO\n");

    return cont;
}

void adicionar_apos(Lista **lista, int valor, int posicao)
{
    if (*lista == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    Lista *atual = *lista;
    int cont = 0;
    do
    {
        if (cont == posicao - 1)
        {
            Lista *novo_no = (Lista *)malloc(sizeof(Lista));
            novo_no->num = valor;
            novo_no->prox = atual->prox;
            atual->prox = novo_no;
            return;
        }
        atual = atual->prox;
        cont++;

    } while (atual != *lista);
}

void busca(Lista *lista, int valor)
{
    if (lista == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    Lista *busca = lista;
    int cont = 0;
    do
    {
        if (busca->num == valor)
        {
            printf("Elemento encontrado: %d, posicao: %d\n", valor, cont + 1);
            return;
        }
        busca = busca->prox;
        cont++;

    } while (busca != lista);
    printf("Elemento nao encontrado\n");
}

void remover(Lista **lista, int valor)
{
    if (*lista == NULL)
    {
        printf("Lista Vazia\n");
        return;
    }

    Lista *atual = *lista;
    Lista *anterior = NULL;
    do
    {
        if (atual->num == valor)
        {
            if (anterior == NULL)
            {

                Lista *temp = *lista;
                // Se ambos forem iguais então so tem 1 elemento
                if (atual->prox == *lista)
                {
                    *lista = NULL;
                }
                else
                {
                    // Percorrer até achar o ultimo elemento e depois remove-lo e depois fazer o novo ultimo elemento apontar para o inicio
                    Lista *ultimo = *lista;
                    while (ultimo->prox != *lista)
                    {
                        ultimo = ultimo->prox;
                    }
                    *lista = atual->prox;
                    ultimo->prox = *lista;
                }
                free(temp);
            }
            else
            {
                // Caso seja qualquer outro elemento so ampontar o anterior->prox para o atual->prox e liberar o atual
                anterior->prox = atual->prox;
                free(atual);
            }
            printf("Elemento %d removido.\n", valor);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != *lista);

    printf("Elemento %d não encontrado.\n", valor);
}

int pulo(Lista **lista, int n)
{
   if (*lista == NULL)
    {
        printf("Lista Vazia\n");
        return -1;
    }

    Lista *atual = *lista;
    Lista *anterior = NULL;

    // Encontrar o último elemento para formar a lista circular corretamente
    do
    {
        anterior = atual;
        atual = atual->prox;
    } while (atual != *lista);

    while ((*lista)->prox != *lista)
    {
        // Avança na lista `n` vezes
        for (int i = 1; i < n; i++)
        {
            anterior = atual;
            atual = atual->prox;
        }

        printf("Removendo posicao: %d\n", atual->posicao);

        
        remover(lista, atual->num);

        
        atual = anterior->prox;
    }

    
    int ultima_posicao = (*lista)->posicao;

    printf("Ultima posicao restante: %d\n", ultima_posicao);
    return ultima_posicao;
}

// void removerDuplicados(Lista **lista) {
//     if (*lista == NULL) {
//         printf("Lista vazia.\n");
//         return;
//     }

//     Lista *atual = *lista;

//     do {
//         Lista *anterior = atual; // Mantém o elemento anterior no loop interno
//         Lista *verificador = atual->prox; // Começa a verificar a partir do próximo elemento

//         while (verificador != *lista) { // Percorre até retornar ao início
//             if (verificador->num == atual->num) {
//                 // Encontrou um duplicado
//                 anterior->prox = verificador->prox; // Remove o duplicado da lista
//                 free(verificador); // Libera a memória do duplicado
//                 verificador = anterior->prox; // Continua verificando o próximo elemento
//             } else {
//                 // Avança os ponteiros
//                 anterior = verificador;
//                 verificador = verificador->prox;
//             }
//         }
//         atual = atual->prox; // Avança para o próximo elemento
//     } while (atual != *lista); // Continua enquanto não retornar ao início

//     printf("Duplicados removidos.\n");
// }

void soma_lista(Lista *lista)
{
    int soma = 0;
    Lista *atual = lista;
    float media = 0;
    int cont = 0;
    do
    {
        soma += atual->num;
        atual = atual->prox;
        cont++;
    } while (atual != lista);

    media = soma / (float)cont;
    printf("\nSoma: %d, Media: %.2f\n", soma, media);
}

void concatenar(Lista **lista1, Lista **lista2)
{
    if (*lista1 == NULL)
    {
        *lista1 = *lista2;
    }
    else if (*lista2 != NULL)
    {
        Lista *atual1 = *lista1;
        while (atual1->prox != *lista1)
        {
            atual1 = atual1->prox;
        }

        Lista *atual2 = *lista2;
        while (atual2->prox != *lista2)
        {
            atual2 = atual2->prox;
        }

        atual1->prox = *lista2;
        atual2->prox = *lista1;

        printf("\nLista concatenada: ");
        printar(*lista1);
    }
}

void liberar(Lista **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista *atual = *lista;
    Lista *prox_no;

    do
    {
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    } while (atual != *lista);

    *lista = NULL;
    printf("Lista Liberada");
}

void menu()
{
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
    // printf("10. Intersecao de listas\n");
    printf("11. Liberar lista\n");
    printf("12. Pulo\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Lista *list_encadeda = inicio();
    Lista *list_encadeda2 = inicio();
    int opcao, valor, posicao;

    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
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
            adicionar_elemento(&list_encadeda, valor);
            break;
        case 4:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            printf("Digite a posicao: ");
            scanf("%d", &posicao);
            adicionar_apos(&list_encadeda, valor, posicao);
            break;
        case 5:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            busca(list_encadeda, valor);
            break;
        case 6:
            printf("\nLista: ");
            printar(list_encadeda);
            break;
        case 7:
            soma_lista(list_encadeda);
            break;
        case 8:

            // removerDuplicados(&list_encadeda); // Implementar esta função
            break;
        case 9:
            criar_lista(&list_encadeda2);
            concatenar(&list_encadeda, &list_encadeda2);
            break;
        case 10:
            // string_intersecao(&list_encadeda, &list_encadeda2); // Implementar esta função
            break;
        case 11:
            liberar(&list_encadeda);
            list_encadeda = inicio();
            break;
        case 12:
            printf("Digite o valor de n para o pulo: ");
            scanf("%d", &valor);
            pulo(&list_encadeda, valor);
            break;
        case 0:
            liberar(&list_encadeda);
            liberar(&list_encadeda2);
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
