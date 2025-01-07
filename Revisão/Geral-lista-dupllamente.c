#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lsd
{
    int num;
    struct Lsd *prox;
    struct Lsd *anter;
} Lsd;

void add(Lsd **lista, int num)
{
    Lsd *no = (Lsd *)malloc(sizeof(Lsd));
    no->num = num;
    no->anter = NULL;
    no->prox = NULL;
    if (*lista == NULL)
    {
        *lista = no;
        return;
    }
    Lsd *atual = *lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    atual->prox = no;
    no->anter = atual;
}

void criar(Lsd **lista)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        add(lista, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Lsd *lista)
{
    if (lista == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    while (lista != NULL)
    {
        printf("%d -> ", lista->num);
        lista = lista->prox;
    }
    printf("NULL\n");
}

void liberar_segundo_maior(Lsd **lista)
{
    Lsd *atual = *lista;
    if (atual == NULL)
    {
        return;
    }

    int maior = atual->num;
    int segundo = atual->num;
    atual = atual->prox;

    while (atual != NULL)
    {
        if (atual->num > maior)
        {
            segundo = maior;
            maior = atual->num;
        }
        else if (atual->num > segundo && atual->num < maior)
        {
            segundo = atual->num;
        }
        atual = atual->prox;
    }

    atual = *lista;
    while (atual != NULL)
    {
        if (atual->num == segundo)
        {
            if (atual->anter != NULL)
            {
                atual->anter->prox = atual->prox;
            }
            else
            {
                *lista = atual->prox;
            }
            if (atual->prox != NULL)
            {
                atual->prox->anter = atual->anter;
            }
            free(atual);
            printf("%d removido \n", segundo);
            return;
        }
        atual = atual->prox;
    }
}

void mesclagem(Lsd **lista1, Lsd **lista2)
{
    if (*lista1 == NULL)
    {
        *lista1 = *lista2;
        *lista2 = NULL;
        return;
    }
    if (*lista2 == NULL)
    {
        return;
    }

    Lsd *atual1 = *lista1;
    Lsd *atual2 = *lista2;
    Lsd *prox1, *prox2;

    while (atual1 != NULL && atual2 != NULL)
    {
        prox1 = atual1->prox;
        prox2 = atual2->prox;

        atual1->prox = atual2;
        atual2->anter = atual1;

        if (prox1 != NULL)
        {
            atual2->prox = prox1;
            prox1->anter = atual2;
        }
        atual1 = prox1;
        atual2 = prox2;
    }
    *lista2 = NULL;
}

void remover_buscado(Lsd **lista, int num)
{
    Lsd *atual = *lista;
    if (atual == NULL)
    {
        return;
    }

    while (atual != NULL)
    {
        if (atual->num == num)
        {
            if (atual->anter != NULL)
            {
                atual->anter->prox = atual->prox;
            }
            else
            {
                *lista = atual->prox;
            }
            if (atual->prox != NULL)
            {
                atual->prox->anter = atual->anter;
            }
            Lsd *temp = atual;
            atual = atual->prox;
            free(temp);
        }
        else
        {
            atual = atual->prox;
        }
    }
}

void remover_todos_os_repetidos(Lsd **lista)
{
    Lsd *atual = *lista;
    Lsd *comparador = NULL;
    while (atual != NULL)
    {
        comparador = atual->prox;
        while (comparador != NULL)
        {
            if (comparador->num == atual->num)
            {
                Lsd *temp = comparador;
                if (comparador->anter != NULL)
                {
                    comparador->anter->prox = comparador->prox;
                }
                if (comparador->prox != NULL)
                {
                    comparador->prox->anter = comparador->anter;
                }
                comparador = comparador->prox;
                free(temp);
            }
            else
            {
                comparador = comparador->prox;
            }
        }
        atual = atual->prox;
    }
}

void rotacionar(Lsd **lista, int n)
{
    if (*lista == NULL)
    {
        return;
    }

    Lsd *atual = *lista;
    int cont = 1;
    while (atual->prox != NULL)
    {
        cont++;
        atual = atual->prox;
    }

    atual->prox = *lista;
    (*lista)->anter = atual;
    n = n % cont;

    for (int i = 1; i < cont - n; i++)
    {
        atual = atual->prox;
    }
    *lista = atual->prox;
    (*lista)->anter = NULL;
    atual->prox = NULL;
}

int polidromia(Lsd *lista)
{
    if (lista == NULL)
    {
        return -1;
    }
    Lsd *fim = lista;
    while (fim->prox != NULL)
    {
        fim = fim->prox;
    }

    while (lista != NULL && lista != fim && lista->anter != fim)
    {
        if (lista->num != fim->num)
        {
            return 0;
        }
        lista = lista->prox;
        fim = fim->anter;
    }
    return 1;
}

void inverter_intervalo(Lsd **lista, int x, int y)
{
    if (*lista == NULL)
    {
        return;
    }
    Lsd *atual = *lista;
    Lsd *inicio = NULL;
    Lsd *fim = NULL;

    while (atual != NULL)
    {
        if (atual->num == x)
        {
            inicio = atual;
        }
        if (atual->num == y)
        {
            fim = atual;
        }

        atual = atual->prox;
    }

    if (inicio == NULL || fim == NULL || inicio == fim)
    {
        return;
    }

    Lsd *prox = inicio->anter;
    Lsd *anter = fim->prox;
    atual = inicio;
    Lsd *temp = NULL;

    while (atual != anter)
    {
        temp = atual->prox;
        atual->prox = atual->anter;
        atual->anter = temp;
        atual = temp;
    }

    if (prox != NULL)
    {
        prox->prox = fim;
    }
    else
    {
        *lista = fim;
    }
    if (anter != NULL)
    {
        anter->anter = inicio;
    }

    inicio->prox = anter;
    fim->anter = prox;
}

void remover_intervalo(Lsd **lista, int x, int y)
{
    if (*lista == NULL)
    {
        return;
    }
    Lsd *atual = *lista;
    Lsd *inicio = NULL;
    Lsd *fim = NULL;

    while (atual != NULL)
    {
        if (atual->num == x)
        {
            inicio = atual;
        }
        if (atual->num == y)
        {
            fim = atual;
        }

        atual = atual->prox;
    }

    if (inicio == NULL || fim == NULL || inicio == fim)
    {
        return;
    }

    Lsd *temp = inicio;
    while (temp != fim->prox)
    {
        Lsd *proximo = temp->prox;
        if (temp->anter != NULL)
        {
            temp->anter->prox = temp->prox;
        }
        else
        {
            *lista = temp->prox;
        }
        if (temp->prox != NULL)
        {
            temp->prox->anter = temp->anter;
        }
        free(temp);
        temp = proximo;
    }
}

int primo(int n)
{
    if (n < 2)
    {
        return 0;
    }

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

void add_depois_primos(Lsd **lista, int valor)
{
    Lsd *atual = *lista;
    while (atual != NULL)
    {
        if (primo(atual->num))
        {
            Lsd *novo_no = (Lsd *)malloc(sizeof(Lsd));
            novo_no->num = valor;
            novo_no->prox = atual->prox;
            novo_no->anter = atual;
            if (atual->prox != NULL)
            {
                atual->prox->anter = novo_no;
            }
            atual->prox = novo_no;
            atual = novo_no->prox;
        }
        else
        {
            atual = atual->prox;
        }
    }
}

void add_antes_depois_n(Lsd **lista, int n)
{
    if (*lista == NULL)
    {
        return;
    }
    Lsd *atual = *lista;
    while (atual != NULL && atual->num != n)
    {
        atual = atual->prox;
    }
    if (atual != NULL)
    {
        Lsd *novo;
        for (int i = 1; i <= n; i++)
        {
            novo = (Lsd *)malloc(sizeof(Lsd));
            novo->num = i;
            novo->prox = atual;
            novo->anter = atual->anter;
            if (atual->anter != NULL)
            {
                atual->anter->prox = novo;
            }
            else
            {
                *lista = novo;
            }
            atual->anter = novo;
        }

        for (int i = 1; i <= n; i++)
        {
            novo = (Lsd *)malloc(sizeof(Lsd));
            novo->num = i;
            novo->prox = atual->prox;
            novo->anter = atual;
            if (atual->prox != NULL)
            {
                atual->prox->anter = novo;
            }
            atual->prox = novo;
            atual = novo->prox;
        }
    }
}

int main()
{
    Lsd *lista = NULL;
    int opcao, valor, x, y;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento\n");
        printf("2. Listar elementos\n");
        printf("3. Liberar segundo maior\n");
        printf("4. Mesclar listas\n");
        printf("5. Remover elemento buscado\n");
        printf("6. Remover todos os repetidos\n");
        printf("7. Rotacionar lista\n");
        printf("8. Verificar polidromia\n");
        printf("9. Inverter intervalo\n");
        printf("10. Remover intervalo\n");
        printf("11. Adicionar depois dos primos\n");
        printf("12. Adicionar antes e depois de n\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser adicionado: ");
            scanf("%d", &valor);
            add(&lista, valor);
            break;
        case 2:
            listar(lista);
            break;
        case 3:
            liberar_segundo_maior(&lista);
            break;
        case 4:
            // Mesclar listas (necessario criar e passar outra lista)
            break;
        case 5:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            remover_buscado(&lista, valor);
            break;
        case 6:
            remover_todos_os_repetidos(&lista);
            break;
        case 7:
            printf("Digite o numero de rotacoes: ");
            scanf("%d", &valor);
            rotacionar(&lista, valor);
            break;
        case 8:
            if (polidromia(lista))
            {
                printf("A lista e um palindromo\n");
            }
            else
            {
                printf("A lista nao e um palindromo\n");
            }
            break;
        case 9:
            printf("Digite o valor inicial do intervalo: ");
            scanf("%d", &x);
            printf("Digite o valor final do intervalo: ");
            scanf("%d", &y);
            inverter_intervalo(&lista, x, y);
            break;
        case 10:
            printf("Digite o valor inicial do intervalo: ");
            scanf("%d", &x);
            printf("Digite o valor final do intervalo: ");
            scanf("%d", &y);
            remover_intervalo(&lista, x, y);
            break;
        case 11:
            printf("Digite o valor a ser adicionado depois dos primos: ");
            scanf("%d", &valor);
            add_depois_primos(&lista, valor);
            break;
        case 12:
            printf("Digite o valor de n: ");
            scanf("%d", &valor);
            add_antes_depois_n(&lista, valor);
            break;
        case 0:
            exit(0);
        default:
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}