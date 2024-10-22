#include <stdio.h>
#include <ctype.h>

int main()
{
    char NOME_ARQ[30];

    printf("Digite o nome do arquivo (.txt): ");
    scanf(" %[^\n]", NOME_ARQ);

    FILE *arq;
    arq = fopen(NOME_ARQ, "w");

    char frase[50];

    for (int i = 1; i <= 3; i++)
    {
        printf("Digite a %d frase:\n", i);
        scanf(" %[^\n]", frase);
        for (int j = 0; frase[j] != '\0'; j++)
        {
            frase[j] = toupper(frase[j]);
        }
        fprintf(arq, "%s\n", frase);
    }
    fclose(arq);

    arq = fopen(NOME_ARQ, "r");

    printf("\nFrases em maiusculo\n\n");

    // while (fscanf(arq, " %[^\n]", frase) == 1)
    // {
    //     printf("%s\n", frase);
    // }
    char c;
    while ((c = fgetc(arq)) != EOF){
        printf("%c", c);
    }

    

    fclose(arq);

    return 0;
}