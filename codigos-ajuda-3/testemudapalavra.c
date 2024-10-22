#include <stdio.h>
#include <string.h>

int main() {
    FILE *arquivo = fopen("seuarquivo.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char palavraAntiga[] = "antiga";
    char palavraNova[] = "nova";

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *posicao = strstr(linha, palavraAntiga);
        if (posicao) {
            fseek(arquivo, posicao - linha, SEEK_CUR);
            fprintf(arquivo, "%s", palavraNova);
        }
    }

    fclose(arquivo);
    printf("Palavra modificada com sucesso!\n");

    return 0;
}
