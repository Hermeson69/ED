#include <stdio.h>
#include "arquivoes.h"

int main()
{
    Alunos turma[1000];
    char nome_do_Arquivo[50];
    int opcao, aux = 0;

    do
    {
        printf("\nSISTEMA DE BACKUP DE DADOS");
        printf("\nInforme a operacao desejada (1-> SALVAR, 2-> RESTALRAR):\n");
        scanf("%d", &opcao);
        scanf("%*c");
        switch (opcao)
        {
        case 1:
            if (aux == 0)
            {
                printf("Digite o nome do arquivo (deve ser um .txt): ");
                fgets(nome_do_Arquivo, 50, stdin);
                aux++;
            }
            salvarDados(turma, nome_do_Arquivo);
            break;
        case 2:
            printf("Digite o nome do arquivo (deve ser um .txt): ");
            fgets(nome_do_Arquivo, 50, stdin);
            restaurarDados(nome_do_Arquivo, turma);
            break;
        }
    } while (opcao != 0);
    return 0;
}