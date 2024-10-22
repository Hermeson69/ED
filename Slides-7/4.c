#include <stdio.h>
#include <stdlib.h>

struct Empregado
{
    char nome[50];
    float salario;
};

int Cad(struct Empregado **a)
{
    int q;
    printf("Quantos Empregados Cadastrar: \n");
    if (scanf("%d", &q) != 1)
    {
        printf("Erro ao ler o número de Empregados.\n");
        return 0;
    }
    *a = (struct Empregado *)malloc(q * sizeof(struct Empregado));
    if (*a == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 0;
    }
    for (int i = 0; i < q; i++)
    {
        printf("Nome: \n");
        if (scanf("%s", (*a)[i].nome) != 1)
        {
            printf("Erro ao ler o nome.\n");
            free(*a);
            return 0;
        }
        printf("Salario: \n");
        if (scanf("%f", &(*a)[i].salario) != 1)
        {
            printf("Erro ao ler o salario.\n");
            free(*a);
            return 0;
        }
    }
    return q;
}

void print_(struct Empregado *a, int q)
{
    for (int i = 0; i < q; i++)
    {
        printf("Nome: %s\n", a[i].nome);
        printf("Salario: %.2f\n", a[i].salario);
    }
}

void order_salario(struct Empregado *a, int q)
{
    for (int i = 0; i < q - 1; i++)
    {
        for (int j = 0; j < q - 1; j++)
        {
            if (a[j].salario > a[j + 1].salario)
            {
                struct Empregado aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
            }
        }
    }
}

int main()
{
    struct Empregado *a = NULL;
    int q = Cad(&a);
    if (q > 0)
    {
        printf("Dados: \n");
        order_salario(a, q);
        print_(a, q);
        free(a);
    }
    return 0;
}
