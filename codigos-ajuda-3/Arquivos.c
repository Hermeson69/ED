#include <stdio.h>
#include<string.h>

#define nome_arq "arquivo.txt"

int main()
{
    FILE *arquivo;

    //w, r, a, w+, r+, a+
    // w = write escreve 

    arquivo = fopen(nome_arq, "w" );

    char nome[50];

    scanf("%s", nome);

    fprintf(arquivo, "%s\n", nome);

    fclose(arquivo);

    return 0;
}