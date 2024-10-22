#include <stdio.h>
#include <stdlib.h>

struct Aluno
{
    int matricula;
    char nome[50];
    float nota;
};

int Cad(struct Aluno **a)
{
    int q;
    printf("Quantos alunos Cadastrar: \n");
    scanf("%d", &q);
    *a = (struct Aluno *)malloc(q * sizeof(struct Aluno));
    if (*a == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 0;
    }
    for (int i = 0; i < q; i++)
    {
        printf("Matricula:\n");
        scanf("%d", &(*a)[i].matricula);
        printf("Nome: \n");
        scanf("%s", (*a)[i].nome);
        printf("Nota: \n");
        scanf("%f", &(*a)[i].nota);
    }
    return q;
}

void print_(struct Aluno *a, int q)
{
    for (int i = 0; i < q; i++)
    {
        printf("Matricula: %d\n", a[i].matricula);
        printf("Nome: %s\n", a[i].nome);
        printf("Nota: %f\n", a[i].nota);
    }
}

int main()
{
    struct Aluno *a = NULL;
    int q = Cad(&a);
    if (q > 0)
    {
        printf("Dados: \n");
        print_(a, q);
        free(a);
    }
    return 0;
}
