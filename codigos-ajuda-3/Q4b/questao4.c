#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_ARQ "arquivo.bin"
#define MAX_POSICAO 20
#define TAM_NOME 50

int escreve(FILE *arq);
void printar(FILE *arq);
void buacar(FILE *arq);
void formatar(FILE *arq);

typedef struct {
    int pocicao;
    char nome [TAM_NOME];
}Registro;


int main()
{
    FILE *arq;
    arq = fopen(NOME_ARQ, "ab");
    fclose(arq);

    int opcao, cont = 0;


    while (1)
    {

        printf("|1-> Escrever|\n|2-> Printar |\n|3-> Buscar  |\n|4-> Formatar|\n|5-> Sair    |\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            printf("Quantos cadatros deseja fazer?: ");
            scanf("%d", &cont);
            getchar();
            for(int i = 0 ; i < cont ; i++){
                escreve(arq);
            }
            break;
        case 2:
            printar(arq);
            break;
        case 3:
            buacar(arq);
            break;
        case 4:
            formatar(arq);
            break;
        case 5:
            printf("Programa Finalizado!!\n");
            return 0;
        default:
            printf("Opcao invalida<!>\n");
            break;
        }
    }

    return 0;
}

int escreve(FILE *arq)
{
    Registro reg, aux;
    arq = fopen(NOME_ARQ, "rb+");

    printf("Digite a posicao (1-20): ");
    scanf("%d", &reg.pocicao);
    getchar();



    if(reg.pocicao < 1|| reg.pocicao > MAX_POSICAO){
        printf("Posicao invalida");
        fclose(arq);
        return 1;
    }

    fseek(arq, (reg.pocicao-1) * sizeof(Registro), SEEK_SET);
    fread(&aux, sizeof(Registro), 1, arq);

    if(strlen(aux.nome)!=0){
        printf("Posicao %d ja ocupada com o nome: %s\n\n", reg.pocicao, aux.nome);
        fclose(arq);
        return 1;
    }

    printf("Digite o nome:\n");
    fgets(reg.nome, TAM_NOME, stdin);
    reg.nome[strcspn(reg.nome, "\n")] = '\0';


    fseek(arq, (reg.pocicao-1) * sizeof(Registro), SEEK_SET);
    fwrite(&reg, sizeof(Registro), 1, arq);

    fclose(arq);
    return 0;
}

void printar(FILE *arq){
    Registro reg;
    arq = fopen(NOME_ARQ, "rb");

    printf("%-8s %-30s\n", "\nChave", "Nome");
    while(fread(&reg,sizeof(Registro), 1, arq)){
        if(reg.pocicao!=0){
            printf("%-7d %-30s\n", reg.pocicao, reg.nome);
        }
    }
    printf("\n");
    fclose(arq);
}

void buacar(FILE *arq){
    Registro reg;

    arq = fopen(NOME_ARQ,"rb+");
    char busca[TAM_NOME];
    int found = 0, op, b_posicao;

    printf("Digite o tipo de busca desejada!!\n|1-> por nome   |\n|2-> por posicao|\n");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        printf("Digite a palavra que deseja buscas: ");
        scanf("%s", busca);

        while(fread(&reg.pocicao, sizeof(Registro), 1, arq)){
            if(strstr(reg.nome, busca) != NULL){
            printf("\nNome encontrado\n");
            printf("%-8s %-30s\n", "Chave", "Nome");
            printf("%-8d %-30s\n", reg.pocicao, reg.nome);
            found = 1;// 1 = TRUE
            }
        }

        if(!found){
            printf("Nome nao encontrado\n\n");
            fclose(arq);
        }
        break;
    case 2:
        printf("Digite a posicao buscada: ");
        scanf("%d", &b_posicao);

        if(b_posicao<1||b_posicao>MAX_POSICAO){
            printf("Posicao Invalida\n");
            return;
        }

        fseek(arq, (b_posicao-1) * sizeof(Registro), SEEK_SET);
        fread(&reg, sizeof(Registro), 1, arq);

        if(strlen(reg.nome)!= 0){
            printf("\nPosocao Encontrada\n");
            printf("%-8s %-30s\n", "Chave", "Nome");
            printf("%-8d %-30s\n", reg.pocicao, reg.nome);
        }else{
            printf("Posicao nao encontrada<!>\n");
            fclose(arq);
        }

        break;
    default:
        printf("Opcao Invalida\n");
        break;
    }

    fclose(arq);
}

void formatar(FILE *arq){
    arq = fopen(NOME_ARQ, "wb");
    fclose(arq);
    printf("Arquivo Formatado\n");
}