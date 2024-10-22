#include <stdio.h>

int possible_impossible(int valCompra, int valPago);

int main() {
    int valCompra, valPago;

    FILE *entrada = fopen("entrada.txt", "r");

    FILE *saida = fopen("saida.txt", "w");

    while(fscanf(entrada,"%d %d",&valCompra, &valPago) == 2){
        
        if (possible_impossible(valCompra, valPago)) {
            fprintf(saida, "possible\n");
        } else {
            fprintf(saida, "impossible\n");
        }
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}

int possible_impossible(int valCompra, int valPago) {
    int notas[] = {2, 5, 10, 20, 50, 100};
    int num_notas = 6;
    
    for (int i = 0; i < num_notas; i++) {
        for (int j = 0; j < num_notas; j++) {
            if (notas[i] + notas[j] == valPago - valCompra) {
                return 1;
            }
        }
    }
    
    return 0;
}