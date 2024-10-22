#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 1000
#define TAM_DESC 30
#define ARQ_CELULARES "celulares.bin"

typedef struct {
    int codigo;
    char descricao[TAM_DESC];
    float preco;
} Celular;

void cadastrar();
void visualizar();
void remover();
int buscar_codigo(int codigo);
void informar_modulo();

int main() {
    int opcao;

    while (1) {
        informar_modulo();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                visualizar();
                break;
            case 3:
                remover();
                break;
            case 4:
                return 0;
            default:
                printf("Opcoo invalida!\n");
        }
    }

    return 0;
}

void informar_modulo() {
    printf("1-Cadastrar\n2-Vizualizar\n3-Remover registro\n4-Finalizar");
    printf("\nInforme o modulo desejado: ");
}

void cadastrar() {
    FILE *file = fopen(ARQ_CELULARES, "ab+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Celular celular;
    printf("Digite o codigo: ");
    scanf("%d", &celular.codigo);
    getchar();

    if (buscar_codigo(celular.codigo) != -1) {
        printf("Codigo ja foi cadastrado!\n");
        fclose(file);
        return;
    }

    printf("Digite a descricao: ");
    fgets(celular.descricao, TAM_DESC, stdin);
    celular.descricao[strcspn(celular.descricao, "\n")] = '\0'; 

    printf("Digite o preco: ");
    scanf("%f", &celular.preco);
    getchar(); 

    fwrite(&celular, sizeof(Celular), 1, file);
    fclose(file);
}

void visualizar() {
    FILE *file = fopen(ARQ_CELULARES, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Celular celular;
    while (fread(&celular, sizeof(Celular), 1, file)) {
        printf("%d, %s, %.2f\n", celular.codigo, celular.descricao, celular.preco);
    }

    fclose(file);
}

void remover() {
    int codigo;
    printf("Digite o codigo do celular a ser removido: ");
    scanf("%d", &codigo);
    getchar();  

    FILE *file = fopen(ARQ_CELULARES, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        perror("Erro ao abrir o arquivo temporario");
        fclose(file);
        return;
    }

    Celular celular;
    int encontrado = 0;
    while (fread(&celular, sizeof(Celular), 1, file)) {
        if (celular.codigo == codigo) {
            encontrado = 1;
        } else {
            fwrite(&celular, sizeof(Celular), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(ARQ_CELULARES);
    rename("temp.bin", ARQ_CELULARES);

    if (encontrado) {
        printf("Celular removido com sucesso!\n");
    } else {
        printf("Codigo nao encontrado!\n");
    }
}

int buscar_codigo(int codigo) {
    FILE *file = fopen(ARQ_CELULARES, "rb");
    if (file == NULL) {
        return -1;
    }

    Celular celular;
    int posicao = 0;
    while (fread(&celular, sizeof(Celular), 1, file)) {
        if (celular.codigo == codigo) {
            fclose(file);
            return posicao;
        }
        posicao++;
    }

    fclose(file);
    return -1;
}
