#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int busca_binaria(int vet[], int tam_vet, int valor_buscado);
void ordena_vetor(int vet[], int tam_vet);
void busca_sequencial(int vet[], int tam_vet, int valor_buscado);

int main(){

    srand(time(NULL));
    int tam_vet;

    scanf("%d", &tam_vet);

    int vet[tam_vet];

    for(int i = 0; i < tam_vet; i++){
        vet[i] = rand() % 1000;
        printf("%d ", vet[i]);
    }

    int valor_buscado;

    printf("\nDigite o valor a ser buscado: ");
    scanf("%d", &valor_buscado);
    busca_sequencial(vet, tam_vet, valor_buscado);

    ordena_vetor(vet, tam_vet);
    
    int resultado = busca_binaria(vet, tam_vet, valor_buscado);
        

    if(resultado != -1){
        printf("Valor %d encontado na posicao %d\n\n", valor_buscado, resultado);
    }else{
        printf("Valor nao encontrado\n\n");
    }

    return 0;
}

int busca_binaria(int vet[], int tam_vet, int valor_buscado){

    int inicio = 0, fim = tam_vet - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if(vet[meio] == valor_buscado){
            return meio;

        }else if(vet[meio] < valor_buscado){
            inicio = meio + 1;

        }else{
            fim = meio - 1;
        }
    }

    return -1;
}
//selection
void ordena_vetor(int vet[], int tam_vet){
    int i, j, min_idx;

    for (i = 0; i < tam_vet-1; i++) {
        min_idx = i;
        for (j = i+1; j < tam_vet; j++) {
            if (vet[j] < vet[min_idx]) {
                min_idx = j;
            }
        }

        if ((vet[i] != vet[min_idx])) {
            int temp = vet[min_idx];
            vet[min_idx] = vet[i];
            vet[i] = temp;
        }
    }
}

void busca_sequencial(int vet[], int tam_vet, int valor_buscado){

    int i = 0, encontardo = 0;

    while (i < tam_vet)
    {
        if(vet[i] == valor_buscado){
            printf("\nValor %d encontado na posicao %d\n\n", valor_buscado, i);
            encontardo = 1;
        }
        i++;
    }
    if(!encontardo){
        printf("Valor nao encontrado!!\n\n");
    }
}