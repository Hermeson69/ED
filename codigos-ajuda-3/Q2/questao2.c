#include<stdio.h>
#include<string.h>

#define NOME_ARQ "FRASES.txt"
#define MAX_TXT 1000

void escreve(FILE *arq, char palavra[MAX_TXT]);
void printar(FILE *arq);
void formatar(FILE *arq);
void buscar(FILE *arq);
void alterar(FILE *arq);

int main(){

    FILE *arq;
    arq = fopen(NOME_ARQ, "a");
    fclose(arq);

    char palavra[MAX_TXT];

    while(1){
        int opcao;
        printf("\nDigite a opcao desejada:\n|1-> Escrever|\n|2-> Printar |\n|3-> Formatar|\n|4-> Buscar  |\n|5-> Alterar |\n|6-> Fechar  |\n:");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            escreve(arq, palavra);
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
            alterar(arq);
            break;
        case 6:
            printf("Programa encerrado\n");
            return 0;
        default:
            printf("Opcao invalida\n\n");
            break;
        }
    }
    return 0;
}

void escreve(FILE *arq, char palavra[MAX_TXT]){

    fopen(NOME_ARQ, "a");

    printf("Digite o que desejar:\n");
    scanf(" %[^\n]", palavra);
    fprintf(arq, "%s\n", palavra);

    fclose(arq);
}

void printar(FILE *arq){

    //char palavra[50];
    char c;
    arq = fopen(NOME_ARQ, "r");

    if(fgetc(arq) == EOF){// compara se a primeira posicao é EOF(final do arquivo)
        printf("Arquivo vazio <!>\n\n");
    }
    
    rewind(arq);//retorna o ponteiro do arquivo para a posicao inicial

    /*while(fscanf(arq, " %[^\n]", palavra) == 1){
        printf("%s\n", palavra);
    }*/

    while((c = fgetc(arq)) != EOF){
        printf("%c", c);
    }

    fclose(arq);
}

void formatar(FILE *arq){
    arq = fopen(NOME_ARQ, "w");
    fclose(arq);
    printf("Arquivo formatado!!\n");
}

void buscar(FILE *arq){
    
    char pesquisa [MAX_TXT];
    char linha [MAX_TXT];
    char c;
    int found = 0;

    arq = fopen(NOME_ARQ, "r");
    //imprime o conteudo do arquivo e volta o para a possição inicial apois finalizar
    while((c = fgetc(arq)) != EOF){
        printf("%c", c);
    }rewind(arq);

    printf("\nDigite sua pesquisa: ");
    scanf("%s", pesquisa);

    while(fscanf(arq, " %[^\n]", linha) == 1){
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

void alterar(FILE *arq) {

    arq = fopen(NOME_ARQ, "r+");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char palavra_antiga[MAX_TXT];
    char palavra_nova[MAX_TXT];
    printf("Digite a palavra ou trecho a ser substituido: ");
    scanf(" %[^\n]", palavra_antiga);
    printf("Digite a nova palavra ou trecho: ");
    scanf(" %[^\n]", palavra_nova);

    FILE *temp_arq = fopen("temp.txt", "w");
    if (temp_arq == NULL) {
        printf("Erro ao criar arquivo temporario\n");
        fclose(arq);
        return;
    }

    char linha[MAX_TXT];
    while (fgets(linha, MAX_TXT, arq)) {
        char *pos = linha;
        while ((pos = strstr(pos, palavra_antiga)) != NULL) {
            // Escreve a parte antes da palavra antiga no arquivo temporário
            fwrite(linha, sizeof(char), pos - linha, temp_arq);

            // Escreve a nova palavra ou trecho no arquivo temporário
            fwrite(palavra_nova, sizeof(char), strlen(palavra_nova), temp_arq);

            // Avança pos para depois da palavra antiga na linha
            pos += strlen(palavra_antiga);

            // Atualiza a linha para o restante da string após a palavra antiga
            strcpy(linha, pos);
        }
        // Escreve o restante da linha no arquivo temporário
        fwrite(linha, sizeof(char), strlen(linha), temp_arq);
    }

    fclose(arq);
    fclose(temp_arq);

    remove(NOME_ARQ);
    rename("temp.txt", NOME_ARQ);

    printf("Palavra(s) alterada(s) com sucesso!\n");
}
