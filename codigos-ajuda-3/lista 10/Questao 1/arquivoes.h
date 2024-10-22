typedef struct
{
	int chave;
	char nome[30];
	char endereco[50];
	char telefone[14];
} Alunos;

int restaurarDados(char *nome_do_Arquivo, Alunos *turma);
int salvarDados(Alunos *turma, char *nome_do_Arquivo);