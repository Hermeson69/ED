#include<stdio.h>
#include<string.h>

#define NOME_ARQ "arquivo.bin"

void escrever(FILE *arq, char palavra[50]);
void printar(FILE *arq);
void formatar(FILE *arq);
void buscar(FILE *arq);

int main(){

    FILE *arq;
    arq = fopen(NOME_ARQ, "ab");
    fclose(arq);

    char palavra[50];

    while(1){
        int opcao;
        printf("\nDigite a opcao desejada:\n|1-> Escrever|\n|2-> Printar |\n|3-> Formatar|\n|4-> Buscar  |\n|5-> Fechar  |\n\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            escrever(arq, palavra);
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
            printf("Programa encerrado\n");
            return 0;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
    return 0;  
}

void escrever(FILE *arq, char palavra[50]){
    arq = fopen(NOME_ARQ, "ab");
    printf("Digite o que desejar:\n");
    scanf(" %[^\n]", palavra);
    fwrite(palavra, sizeof(char)*50, 1, arq);
    fclose(arq);
}

void printar(FILE *arq){
    char palavra[50];
    arq = fopen(NOME_ARQ, "rb");

    while(fread(palavra,sizeof(palavra), 1, arq)){
        printf("%s\n", palavra);
    }
    fclose(arq);
}

void formatar(FILE *arq){
    arq = fopen(NOME_ARQ, "wb");
    fclose(arq);
    printf("Arquivo formatado!!");
}

void buscar(FILE *arq){
    
    char pesquisa [100];
    char linha [100];
    int found = 0;

    arq = fopen(NOME_ARQ, "rb");

    printar(arq);

    printf("\nDigite sua pesquisa: ");
    scanf("%s", pesquisa);

    while(fread(linha, sizeof(char)*50, 1, arq)){
        if(strstr(linha, pesquisa) != NULL){
            printf("\nPalavra encontrada na linha:\n\n--> %s\n", linha);
            found = 1;// 1 = TRUE
        }
    }

    if(!found){
        printf("Nao encontrado\n");
    }

    fclose(arq);
}
