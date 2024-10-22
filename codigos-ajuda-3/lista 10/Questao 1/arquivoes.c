#include <stdio.h>
#include "arquivoes.h"

char *limpaCaractere(char *palavra);
void imprimir(Alunos *turma);
void ordenaNome(Alunos *turma);
void ordenaChave(Alunos *turma);
void cadastrarDados(Alunos *turma);

int quant = 0;
void imprimir(Alunos *turma)
{
    for (int i = 0; i < quant; i++)
    {
        printf("%d\n", turma[i].chave);
        printf("%s", turma[i].nome);
        printf("%s", turma[i].endereco);
        printf("%s\n", turma[i].telefone);
    }
}

int salvarDados(Alunos *turma, char *nomeArquivo)
{
    limpaCaractere(nomeArquivo);
    cadastrarDados(turma);

    FILE *arquivo_txt = fopen(nomeArquivo, "a");

    fprintf(arquivo_txt, "%d\n", turma[quant - 1].chave);
    fprintf(arquivo_txt, "%s", turma[quant - 1].nome);
    fprintf(arquivo_txt, "%s", turma[quant - 1].endereco);
    fprintf(arquivo_txt, "%s", turma[quant - 1].telefone);
    if (arquivo_txt)
    {
        fclose(arquivo_txt);
        printf("Operacao realizada com sucesso.\n");
        return 1;
    }
    else
    {
        printf("\nOperacao falhou <!>\n");
        return 0;
    }
}

int restaurarDados(char *nomeArquivo, Alunos *turma)
{
    limpaCaractere(nomeArquivo);
    Alunos aluno;
    FILE *arquivo_txt = fopen(nomeArquivo, "r");

    quant = 0;
    if (arquivo_txt)
    {
        while (!feof(arquivo_txt))
        {
            fscanf(arquivo_txt, "%d\n", &aluno.chave);
            fgets(aluno.nome, 30, arquivo_txt);
            fgets(aluno.endereco, 50, arquivo_txt);
            fgets(aluno.telefone, 14, arquivo_txt);
            turma[quant] = aluno;
            quant++;
        }
        quant--;
        fclose(arquivo_txt);

        int opcao;

        printf("Deseja ordenar por: |1-> chave|  |2-> nome|\n:");
        scanf("%d", &opcao);
        scanf("%*c");

        switch (opcao)
        {
        case 1:
            ordenaChave(turma);
            break;
        case 2:
            ordenaNome(turma);
            break;
        }
        printf("Operacao realizada com sucesso.\n");
        return 1;
    }
    else
    {
        printf("\nOperacao falhou <!>\n");
        return 0;
    }
}

void ordenaChave(Alunos *turma)
{
    Alunos aux;

    for (int i = 0; i < quant - 1; i++)
    {
        for (int j = 1; j < quant - i; j++)
        {
            if (turma[j].chave < turma[j - 1].chave)
            {
                aux = turma[j];
                turma[j] = turma[j - 1];
                turma[j - 1] = aux;
            }
        }
    }
    imprimir(turma);
}

void ordenaNome(Alunos *turma)
{
    Alunos aux;
    char vetor[1000][1000];
    for (int i = 0; i < quant; i++)
    {
        for (int j = 0; turma[i].nome[j] != '\0'; j++)
        {
            vetor[i][j] = turma[i].nome[j];
            if (turma[i].nome[j] >= 'a' && turma[i].nome[j] <= 'z')
            {
                vetor[i][j] -= 32;
            }
        }
    }
    for (int i = 0; i < quant - 1; i++)
    {
        for (int j = i + 1; j < quant; j++)
        {
            for (int k = 0; turma[j].nome[k] != '\0' && turma[i].nome[k] != '\0'; k++)
            {
                if (vetor[i][k] > vetor[j][k])
                {
                    aux = turma[i];
                    turma[i] = turma[j];
                    turma[j] = aux;
                    break;
                }
            }
        }
    }
    imprimir(turma);
}

void cadastrarDados(Alunos *turma)
{
    Alunos aluno;

    scanf("%d", &aluno.chave);
    scanf("%*c");
    fgets(aluno.nome, 30, stdin);
    fgets(aluno.endereco, 50, stdin);
    fgets(aluno.telefone, 14, stdin);
    turma[quant] = aluno;
    quant++;
}

char *limpaCaractere(char *palavra)
{
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        if (palavra[i] == '\n')
        {
            palavra[i] = '\0';
            break;
        }
    }
    return palavra;
}