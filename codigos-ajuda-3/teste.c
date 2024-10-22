#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "PT_BT"); // Tente "Portuguese" ou "pt_BR.UTF-8" dependendo do seu sistema
    printf("Olá\n");
    return 0;
}
/*void bolha(Alunos v[], int n)
{
	int i, j;
	Alunos aux;
	for(i = 0; i < n-1; i++)
	{
		for(j = 1; j < n-i; j++)
		{
			if(v[j].chave < v[j-1].chave)
			{
				aux = v[j];
				v[j] = v[j-1];
				v[j-1] = aux;
			}
		}
	}
}*/