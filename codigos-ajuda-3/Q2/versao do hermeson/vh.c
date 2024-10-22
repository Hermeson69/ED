#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "FRASES.txt"
#define MAX_LENGTH 51 // 50 characters + 1 for null terminator

typedef struct {
    char word[MAX_LENGTH];
    char searchWord[MAX_LENGTH];
    char newWord[MAX_LENGTH];
} dados;

void writeWordToFile(dados *a) {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Digite uma palavra (ate 50 caracteres): ");
    getchar(); 
    fgets(a->word, sizeof(a->word), stdin);
    a->word[strcspn(a->word, "\n")] = '\0'; // Remove newline character

    fwrite(a->word, sizeof(char), MAX_LENGTH, file);

    fclose(file);
}

void printWordsFromFile(dados *a) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Arquivo vazio\n");
        return;
    }

    int empty = 1;

    while (fread(a->word, sizeof(char), MAX_LENGTH, file) == MAX_LENGTH) {
        printf("%s\n", a->word);
        empty = 0;
    }

    if (empty) {
        printf("Arquivo vazio\n");
    }

    fclose(file);
}

void formatFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        perror("Erro ao formatar o arquivo");
        return;
    }

    fclose(file);
    printf("Arquivo formatado com sucesso.\n");
}

void checkAndCreateFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        file = fopen(FILENAME, "wb");
        if (file == NULL) {
            perror("Erro ao criar o arquivo");
            exit(1);
        }
    }
    fclose(file);
}

void searchWordInFile(dados *a) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Arquivo vazio\n");
        return;
    }

    int found = 0;

    printf("Digite a palavra a ser buscada: ");
    getchar(); 
    fgets(a->searchWord, sizeof(a->searchWord), stdin);
    a->searchWord[strcspn(a->searchWord, "\n")] = '\0'; // Remove newline character

    while (fread(a->word, sizeof(char), MAX_LENGTH, file) == MAX_LENGTH) {
        if (strcmp(a->word, a->searchWord) == 0) {
            printf("Palavra encontrada: %s\n", a->word);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Palavra nao encontrada.\n");
    }

    fclose(file);
}

void updateWordInFile(dados *a) {
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        printf("Arquivo vazio\n");
        return;
    }

    int found = 0;
    long position;

    printf("Digite a palavra a ser alterada: ");
    getchar(); 
    fgets(a->searchWord, sizeof(a->searchWord), stdin);
    a->searchWord[strcspn(a->searchWord, "\n")] = '\0'; // Remove newline character

    while (fread(a->word, sizeof(char), MAX_LENGTH, file) == MAX_LENGTH) {
        if (strcmp(a->word, a->searchWord) == 0) {
            printf("Palavra encontrada: %s\n", a->word);
            found = 1;
            position = ftell(file) - MAX_LENGTH;

            printf("Digite a nova palavra (até 50 caracteres): ");
            fgets(a->newWord, sizeof(a->newWord), stdin);
            a->newWord[strcspn(a->newWord, "\n")] = '\0'; // Remove newline character

            fseek(file, position, SEEK_SET);
            fwrite(a->newWord, sizeof(char), MAX_LENGTH, file);
            printf("Palavra alterada com sucesso.\n");
            break;
        }
    }

    if (!found) {
        printf("Palavra nao encontrada.\n");
    }

    fclose(file);
}

int main() {
    checkAndCreateFile();
    dados a = {0};

    int option;

    do {
        printf("\nMenu:\n");
        printf("1. Ler uma palavra e colocar no arquivo\n");
        printf("2. Printar todas as palavras do arquivo\n");
        printf("3. Formatar arquivo\n");
        printf("4. Buscar palavra no arquivo\n");
        printf("5. Alterar palavra no arquivo\n");
        printf("6. Finalizar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                writeWordToFile(&a);
                break;
            case 2:
                printWordsFromFile(&a);
                break;
            case 3:
                formatFile();
                break;
            case 4:
                searchWordInFile(&a);
                break;
            case 5:
                updateWordInFile(&a);
                break;
            case 6:
                printf("Finalizando o programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (option != 6);

    return 0;
}