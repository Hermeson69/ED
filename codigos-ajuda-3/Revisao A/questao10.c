#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_NOME 50
#define MAX_TELEFONE 14
#define NOME_ARQ "sala.txt"

typedef struct 
{
    char nome[MAX_NOME];
    int chave;
    char telefone [MAX_TELEFONE];
}Aluno;

void escreve(FILE *arq);
void printar(FILE *arq);
void formatar(FILE *arq);
void buscar(FILE *arq);
void alterar_registro(FILE *arq);

int main(){

    FILE *arq = fopen(NOME_ARQ, "a");
    fclose(arq);

    int opcao;

    while (1)
    {
        printf("1-Escrever\n2-Printar\n3-Formatar\n4-Buscar\n5-Alterar Registro\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            escreve(arq);
            break;
        case 2:
            printar(arq);
            break;
        case 3:
            formatar(arq);
            break;
        case 4:
            buscar(arq);
            break;
        case 5:
            alterar_registro(arq);
            break;
        default:
            break;
        }
    }
    return 0;
}

void escreve(FILE *arq){
    arq = fopen(NOME_ARQ, "a");
    Aluno escreve;
    printf("\nDigete a chave: ");
    scanf("%d", &escreve.chave);
    printf("Digite o nome: ");
    scanf(" %[^\n]", escreve.nome);
    printf("Digite o telefone: ");
    scanf(" %[^\n]", escreve.telefone);
    fprintf(arq, "%d %s %s\n", escreve.chave, escreve.nome, escreve.telefone);
    fclose(arq);
    printf("\n");
}

void printar(FILE *arq){
    arq = fopen(NOME_ARQ, "r");
    char c;

    if(fgetc(arq) == EOF){
        printf("\n\nArquivo Vazio<!>\n\n");
    }rewind(arq);
    printf("\n");
    while((c = fgetc(arq)) != EOF){
        printf("%c", c);
    }
    printf("\n\n");
    fclose(arq);
}

void formatar(FILE *arq){
    arq = fopen(NOME_ARQ, "w");
    fclose(arq);
    printf("\n\nArquivo Formatado\n\n");
}

void buscar(FILE *arq){
    arq = fopen(NOME_ARQ, "r");
    Aluno aluno;

    if(arq == NULL){
        printf("\n\nErro ao abrir arquivo <!>\n\n");
        return;
    }

    int pesquisa_chave, posicao = 0, encontardo;
    printf("Digite a chave a ser pesquisada: ");
    scanf("%d", &pesquisa_chave);

    while (fscanf(arq, "%d %49s %14s", &aluno.chave, aluno.nome, aluno.telefone) != EOF)// lembre que esta lendo duas variaveis
    {
        if(aluno.chave == pesquisa_chave){
            printf("\nChave encontarda na posicao: %d\n", posicao);
            printf("%d %s %s\n\n",aluno.chave, aluno.nome, aluno.telefone);
            encontardo = 1;
            break;//se deseja encontarar apenas a primeira ocorrencia
        }
        posicao++;
    }
    if(!encontardo){
        printf("\nChave nao encontarda\n");
    }
    fclose(arq);
}

void alterar_registro(FILE *arq){
    arq = fopen(NOME_ARQ, "r");

    if(arq == NULL){
        printf("\nErro ao abrir o arquivo <!>\n");
    }

    FILE *aux = fopen("aux.txt", "w");
    if (aux == NULL)
    {
        printf("\nErro ao abrir o arquivo <!>\n");
    }
    
    Aluno aluno;
    int chave_remover, foud = 0;
    printf("Digite a chave a ser removida:");
    scanf("%d", &chave_remover);
    while (fscanf(arq, "%d %49s %14s", &aluno.chave, aluno.nome, aluno.telefone) != EOF)
    {
        if (aluno.chave == chave_remover)
        {
            foud = 1;
        }else{
            fprintf(aux,"%d %s %s\n", aluno.chave, aluno.nome, aluno.telefone);
        }
        
    }

    if (!foud)
    {
        printf("\nChave nao encontrada <!>\n");
    }else{
        printf("\nChave removida com sucesso <!>\n");
    }

    fclose(arq);
    fclose(aux);

    remove(NOME_ARQ);
    rename("aux.txt",NOME_ARQ);
}