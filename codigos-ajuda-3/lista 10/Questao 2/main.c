#include <stdio.h>
#include "arquivoes.h"

int main()
{
    int operacao;
    do
    {
        printf("\nSISTEMA PARA PROCESSAMENTO DE DADOS DE ALUNOS\n");
        printf("Informe a operacao desejada |1-> formatar| |2-> escrever| |3-> ler| |4-> buscar| |0-> finalizar|:\n");
        scanf("%d", &operacao);
        switch (operacao)
        {
        case 1:
            formatarArquivo();
            break;
        case 2:
            escrita();
            break;
        case 3:
            leitura();
            break;
        case 4:
            busca();
            break;
        case 0:
            break;
        default:
            printf("OPERACAO INVALIDA <!>\n");
        }
    } while (operacao != 0);
    return 0;
}