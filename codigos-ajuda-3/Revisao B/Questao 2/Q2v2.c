#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ITENS 1000
#define TAM_DESCRICAO 30
#define NOME_ARQ "celulares2.bin"

typedef struct 
{
    int codigo;
    char descricao[TAM_DESCRICAO];
    float preco;
}Celulares;

void cadastrar();
void visualizar();
void remover_registro();
void formatar();
int busca_codigo(int codido);

int main(){
    int op;

    while (1)
    {
        printf("1-Cadastrar\n2-Visializar\n3-Remover registro\n4-Formatar\n5-Finalizar\nDigite a opcao desejada: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            visualizar();
            break;
        case 3:
            remover_registro();
            break;
        case 4:
            formatar();
            break;
        case 5:
            exit(1);
        default:
            printf("\nOpcao invalida\n");
            break;
        }
    }
    return 0;
}

void cadastrar(){
    FILE *arq = fopen(NOME_ARQ, "ab");
    if(arq == NULL){
        printf("\nErro ao abrir arquivo<!>\n");
        return;
    }

    Celulares celular;
    printf("Digite o codigo: ");
    scanf("%d", &celular.codigo);
    getchar();

    if(busca_codigo(celular.codigo) == -1){
        printf("Codigo ja existente\n\n");
        fclose(arq);
        return;
    }

    printf("Digite a descricao: ");
    fgets(celular.descricao, TAM_DESCRICAO, stdin);
    celular.descricao[strcspn(celular.descricao, "\n")] = '\0';

    printf("Digite o preco: ");
    scanf("%f", &celular.preco);
    getchar();

    fwrite(&celular, sizeof(Celulares), 1, arq);
    fclose(arq);
}

void visualizar(){
    FILE *arq = fopen(NOME_ARQ, "rb");
    Celulares celular;
    if(arq == NULL){
        printf("\nErro ao abrir arquivo<!>\n");
        return;
    }
    printf("\n");
    while (fread(&celular, sizeof(Celulares), 1, arq))
    {
        printf("%d %s %f\n", celular.codigo, celular.descricao, celular.preco);
    }
    printf("\n");
    fclose(arq);
}

void remover_registro(){
    FILE *arq = fopen(NOME_ARQ, "rb");
    if(arq == NULL){
        printf("\nErro ao abrir arquivo\n");
        return;
    }

    FILE *aux = fopen("aux.bin", "wb");
    if(arq == NULL){
        printf("\nErro ao abrir arquivo\n");
        return;
    }

    int codigo;
    printf("\nDigite o codigo a ser removido: ");
    scanf("%d", &codigo);
    getchar();

    Celulares celular;
    int encontardo = 0;

    while (fread(&celular, sizeof(Celulares), 1, arq))
    {
        if(celular.codigo == codigo){
            encontardo = 1;
        }else{
            fwrite(&celular, sizeof(Celulares), 1, aux);
        }
    }

    if(encontardo){
        printf("\nRegistro removido com sucesso\n");
    }else{
        printf("\nRegistro nao encontrado<!>\n");
    }
    
    fclose(arq);
    fclose(aux);

    remove(NOME_ARQ);
    rename("aux.bin", NOME_ARQ);
}

void formatar(){
    FILE *arq = fopen(NOME_ARQ, "wb");
    fclose(arq);
}

int busca_codigo(int codigo){
    FILE *arq = fopen(NOME_ARQ, "rb");
    if(arq == NULL){
        printf("\nErro ao abrir o arquivo <!>\n");
    }

    Celulares celular;
    int posicao = 0;

    while (fread(&celular, sizeof(Celulares), 1, arq))
    {
        if(celular.codigo == codigo){
            return -1;
            fclose(arq);
        }
        posicao++;
    }
    fclose(arq);
    return 1;
}