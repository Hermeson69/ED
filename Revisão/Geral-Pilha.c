#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha
{
    int num;
    struct Pilha *prox;
} Pilha;

typedef struct Topo
{
    Pilha *topo;
} Topo;

void add(Topo *topo, int valor)
{
    Pilha *no = (Pilha *)malloc(sizeof(Pilha));
    no->num = valor;
    no->prox = topo->topo;
    topo->topo = no;
}

void criar(Topo *topo)
{
    int num;
    while (scanf("%d", &num) == 1)
    {
        add(topo, num);
    }
    while (getchar() != '\n')
        ;
}

void listar(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }
    Pilha *atual = topo->topo;
    while (atual != NULL)
    {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("INICIO\n");
}

int pop(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return -1;
    }
    Pilha *atual = topo->topo;
    int valor = atual->num;
    topo->topo = atual->prox;
    free(atual);
    return valor;
}

void ver_tam(Topo *topo1, Topo *topo2, int *tam1, int *tam2)
{
    Pilha *atual1 = topo1->topo;
    Pilha *atual2 = topo2->topo;
    int cont1 = 0;
    int cont2 = 0;

    while (atual1 != NULL)
    {
        cont1++;
        atual1 = atual1->prox;
    }

    while (atual2 != NULL)
    {
        cont2++;
        atual2 = atual2->prox;
    }
    *tam1 = cont1;
    *tam2 = cont2;
}

int ver_se_sao_iguais(Topo *topo1, Topo *topo2)
{
    int tam1, tam2;
    ver_tam(topo1, topo2, &tam1, &tam2);
    if (tam1 != tam2)
    {
        return 0;
    }
    Pilha *atual1 = topo1->topo;
    Pilha *atual2 = topo2->topo;

    while (atual1 != NULL && atual2 != NULL)
    {
        if (atual1->num != atual2->num)
        {
            return 0;
        }
        atual1 = atual1->prox;
        atual2 = atual2->prox;
    }

    return 1;
}

void maiores_que(Topo *topo, int n)
{
    if (topo->topo == NULL)
    {
        return;
    }
    Pilha *atual = topo->topo;
    Topo maiores;
    maiores.topo = NULL;
    while (atual != NULL)
    {
        if (atual->num > n)
        {
            add(&maiores, atual->num);
        }
        atual = atual->prox;
    }
    listar(&maiores);
}

void remover_pilha1(Topo *topo1, Topo *topo2)
{
    if (topo1->topo == NULL || topo2->topo == NULL)
    {
        printf("Uma das pilhas esta vazia\n");
        return;
    }

    Topo temp;
    temp.topo = NULL;

    while (topo1->topo != NULL)
    {
        int valor = pop(topo1);

        Pilha *atual2 = topo2->topo;
        int encontrado = 0;

        while (atual2 != NULL)
        {
            if (atual2->num == valor)
            {
                encontrado = 1;
                break;
            }
            atual2 = atual2->prox;
        }

        if (!encontrado)
        {
            add(&temp, valor);
        }
    }

    while (temp.topo != NULL)
    {
        add(topo1, pop(&temp));
    }

    listar(topo1);
}

int contem(Topo *topo, int num)
{
    Pilha *atual = topo->topo;
    while (atual != NULL)
    {
        if (atual->num == num)
        {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void remover(Topo *topo)
{
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Topo aux;
    aux.topo = NULL;

    while (topo->topo != NULL)
    {
        int num = pop(topo);
        if (!contem(&aux, num))
        {
            add(&aux, num);
        }
    }

    while (aux.topo != NULL)
    {
        add(topo, pop(&aux));
    }

    listar(topo);
}

void num_mod(int n)
{
    Topo mods = {NULL};
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            add(&mods, i);
        }
    }
    listar(&mods);
    while (mods.topo != NULL)
    {
        pop(&mods);
    }
}

void positivos_negativos(Topo *topo)
{
    Topo positivos = {NULL};
    Topo negativos = {NULL};
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = topo->topo;
    while (atual != NULL)
    {
        if (atual->num > 0)
        {
            add(&positivos, atual->num);
        }
        if (atual->num < 0)
        {
            add(&negativos, atual->num);
        }
        atual = atual->prox;
    }
    listar(&positivos);
    listar(&negativos);

    while (topo->topo != NULL)
    {
        pop(topo);
    }

    while (positivos.topo != NULL)
    {
        pop(&positivos);
    }

    while (negativos.topo != NULL)
    {
        pop(&negativos);
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

void primos_nao(Topo *topo)
{
    Topo primos = {NULL};
    Topo nao_primos = {NULL};
    if (topo->topo == NULL)
    {
        printf("Pilha Vazia\n");
        return;
    }

    Pilha *atual = topo->topo;
    while (atual != NULL)
    {
        if (primo(atual->num))
        {
            add(&primos, atual->num);
        }
        else
        {
            add(&nao_primos, atual->num);
        }
        atual = atual->prox;
    }

    listar(&primos);
    listar(&nao_primos);

    while (primos.topo != NULL)
    {
        pop(&primos);
    }
    while (nao_primos.topo != NULL)
    {
        pop(&nao_primos);
    }
}

int main()
{
    Topo topo1 = {NULL};
    Topo topo2 = {NULL};
    int opcao, n;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Adicionar elemento na pilha 1\n");
        printf("2. Adicionar elemento na pilha 2\n");
        printf("3. Listar pilha 1\n");
        printf("4. Listar pilha 2\n");
        printf("5. Remover elemento do topo da pilha 1\n");
        printf("6. Remover elemento do topo da pilha 2\n");
        printf("7. Verificar se as pilhas sao iguais\n");
        printf("8. Listar elementos maiores que um valor na pilha 1\n");
        printf("9. Remover elementos da pilha 1 que estao na pilha 2\n");
        printf("10. Remover elementos repetidos da pilha 1\n");
        printf("11. Listar divisores de um numero\n");
        printf("12. Separar positivos e negativos da pilha 1\n");
        printf("13. Separar primos e nao primos da pilha 1\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um valor para adicionar na pilha 1: ");
            criar(&topo1);
            break;
        case 2:
            printf("Digite um valor para adicionar na pilha 2: ");
            criar(&topo2);
            break;
        case 3:
            printf("Pilha 1: ");
            listar(&topo1);
            break;
        case 4:
            printf("Pilha 2: ");
            listar(&topo2);
            break;
        case 5:
            pop(&topo1);
            break;
        case 6:
            pop(&topo2);
            break;
        case 7:
            if (ver_se_sao_iguais(&topo1, &topo2))
            {
                printf("As pilhas sao iguais\n");
            }
            else
            {
                printf("As pilhas nao sao iguais\n");
            }
            break;
        case 8:
            printf("Digite um valor: ");
            scanf("%d", &n);
            maiores_que(&topo1, n);
            break;
        case 9:
            remover_pilha1(&topo1, &topo2);
            break;
        case 10:
            remover(&topo1);
            break;
        case 11:
            printf("Digite um numero: ");
            scanf("%d", &n);
            num_mod(n);
            break;
        case 12:
            positivos_negativos(&topo1);
            break;
        case 13:
            primos_nao(&topo1);
            break;
        case 0:
            exit(0);
        default:
            printf("Opcao invalida\n");
        }
    }

    return 0;
}