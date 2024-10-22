#include <stdio.h>
#include "arquivoes.h"

void busca()
{
    Aluno aluno;
    FILE *arquivo_bin;
    int chave;

    if ((arquivo_bin = fopen("dados.bin", "rb+")) == NULL)
    {
        printf("ARQUIVO NAO ENCONTRADO <!>\n");
        return;
    }
    printf("Digite a chave do aluno: ");
    scanf("%d", &chave);
    if (chave < 1 || chave > 1000)
    {
        printf("Chave invalida.\n");
    }
    else
    {
        fseek(arquivo_bin, (chave - 1) * sizeof(aluno), SEEK_SET);
        fread(&aluno, sizeof(aluno), 1, arquivo_bin);
        if (aluno.chave == 0)
        {
            printf("CHAVE INFORMADA NAO POSSUI NENHUM REGISTRO <!>\n");
        }
        else
        {
            printf("%-8s %-30s %-50s %-14s\n", "Chave", "Nome", "Endereco", "Telefone");
            printf("%-8d %-30s %-50s %-14s\n", aluno.chave, aluno.nome, aluno.endereco, aluno.telefone);
        }
    }
    fclose(arquivo_bin);
}

void escrita()
{
    Aluno aluno;
    FILE *arquivo_bin;

    if ((arquivo_bin = fopen("dados.bin", "rb+")) == NULL)
    {
        printf("ARQUIVO NAO ENCONTRADO <!>\n");
        return;
    }
    printf("Insira a chave do aluno |0-> para finalizar|: ");
    scanf("%d", &aluno.chave);

    while (aluno.chave != 0 && aluno.chave <= 1000)
    {
        printf("Digite o nome do aluno: ");
        scanf(" %[^\n]s", aluno.nome);
        printf("Digite o endereco do aluno: ");
        scanf(" %[^\n]s", aluno.endereco);
        printf("Digite o telefone do aluno: ");
        scanf(" %[^\n]s", aluno.telefone);
        fseek(arquivo_bin, (aluno.chave - 1) * sizeof(Aluno), SEEK_SET);
        fwrite(&aluno, sizeof(aluno), 1, arquivo_bin);
        printf("Insira a chave do aluno |0-> para finalizar|: ");
        scanf("%d", &aluno.chave);
    }
    fclose(arquivo_bin);
}

void formatarArquivo()
{
    Aluno aluno = {0, "", "", ""};
    FILE *arquivo_bin;
    const int tama_arquivo = 1000;

    if ((arquivo_bin = fopen("dados.bin", "rb")) != NULL)
    {
        printf("Arquivo ja existente. Gostaria de sobrescreve-lo? |1-> SIM| |0-> NAO|\n");
        int opcao;
        scanf("%d", &opcao);
        if (opcao != 1)
        {
            fclose(arquivo_bin);
            return;
        }
    }
    fclose(arquivo_bin);
    if ((arquivo_bin = fopen("dados.bin", "wb")) == NULL)
    {
        printf("ERRO AO CRIAR ARQUIVO <!>\n");
        return;
    }
    for (int i = 0; i < tama_arquivo; i++)
    {
        fwrite(&aluno, sizeof(aluno), 1, arquivo_bin);
    }
    fclose(arquivo_bin);
}

void leitura()
{
    Aluno aluno;
    FILE *arquivo_bin;
    int cont_Registros = 0;

    if ((arquivo_bin = fopen("dados.bin", "rb")) == NULL)
    {
        printf("ERRO AO ABRIR ARQUIVO <!>\n");
        return;
    }
    printf("%-8s %-30s %-50s %-14s\n", "Chave", "Nome", "Endereco", "Telefone");
    while (fread(&aluno, sizeof(Aluno), 1, arquivo_bin) == 1)
    {
        if (aluno.chave != 0)
        {
            printf("%-8d %-30s %-50s %-14s\n", aluno.chave, aluno.nome, aluno.endereco, aluno.telefone);
            cont_Registros++;
        }
    }
    if (cont_Registros == 0)
    {
        printf("NENHUM REGISTRO ENCONTRADO <!>\n");
    }
    fclose(arquivo_bin);
}
